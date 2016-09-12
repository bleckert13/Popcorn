/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.content.ComponentName;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.eckert.kernelking.R;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.leaderboard.Leaderboards;
import com.google.example.games.basegameutils.BaseGameUtils;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.List;

public class AppActivity extends Cocos2dxActivity implements GoogleApiClient.ConnectionCallbacks, GoogleApiClient.OnConnectionFailedListener{
    private static AppActivity me = null;

    public static final String TAG = "cocos2d-x debug info";
    private static int RC_SIGN_IN = 9001;
    private static int REQUEST_LEADERBOARD = 1000;
    private boolean mResolvingConnectionFailure = false;
    private boolean mAutoStartSignInflow = true;
    private boolean mSignInClicked = false;
    public GoogleApiClient mGoogleApiClient;

    private final static String APP_PNAME = "com.eckert.kernelking";// Package Name
    protected void onCreate(Bundle savedInstanceState){
        me = this;
        super.onCreate(savedInstanceState);
        // Create the Google Api Client with access to the Play Games services
        mGoogleApiClient = new GoogleApiClient.Builder(this)
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .addApi(Games.API).addScope(Games.SCOPE_GAMES)
                // add other APIs and scopes here as needed
                .build();
    }

    public static void openAppRate(String url) {
        me.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + APP_PNAME)));
    }

    public static void sendemail(String mailbody)
    {

        Intent shareIntent = new Intent(android.content.Intent.ACTION_SEND);
        shareIntent.setType("text/plain");
        shareIntent.putExtra(android.content.Intent.EXTRA_EMAIL, new String[]{"kernelkingapp@gmail.com"});
        shareIntent.putExtra(android.content.Intent.EXTRA_SUBJECT, "Tell us how we can improve Kernel King"); // subject
        shareIntent.putExtra(android.content.Intent.EXTRA_TEXT, mailbody); // Text

        try
        {
            me.getContext().startActivity(Intent.createChooser(shareIntent, "Send email..."));
        }
        catch (android.content.ActivityNotFoundException ex)
        {
            me.runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(me, "There are no email clients installed.", Toast.LENGTH_SHORT);
                }
            });
        }
    }

    public static void shareFacebook(String text)
    {
        Intent shareIntent = new Intent(android.content.Intent.ACTION_SEND);
        shareIntent.setType("text/plain");
        PackageManager pm = me.getPackageManager();
        List<ResolveInfo> activityList = pm.queryIntentActivities(shareIntent, 0);
        boolean show = false;
        for (final ResolveInfo app : activityList)
        {
            if ((app.activityInfo.name).contains("facebook"))
            {
                final ActivityInfo actvity = app.activityInfo;
                final ComponentName name = new ComponentName(actvity.applicationInfo.packageName, actvity.name);
                shareIntent.addCategory(Intent.CATEGORY_LAUNCHER);
                shareIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK|Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
                shareIntent.setComponent(name);
                shareIntent.putExtra(android.content.Intent.EXTRA_TEXT, text);
                me.startActivity(shareIntent);
                show = true;
                break;
            }
        }

        if (!show)
        {
            me.runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(me, "Facebook Share Failed.", Toast.LENGTH_SHORT);
                }
            });
        }
    }
    public static void shareTwitter(String text)
    {
        Intent shareIntent = new Intent(android.content.Intent.ACTION_SEND);
        shareIntent.setType("text/plain");
        PackageManager pm = me.getPackageManager();
        List<ResolveInfo> activityList = pm.queryIntentActivities(shareIntent, 0);
        boolean show = false;
        for (final ResolveInfo app : activityList)
        {
            if ((app.activityInfo.name).contains("twitter"))
            {
                final ActivityInfo actvity = app.activityInfo;
                final ComponentName name = new ComponentName(actvity.applicationInfo.packageName, actvity.name);
                shareIntent.addCategory(Intent.CATEGORY_LAUNCHER);
                shareIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK|Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
                shareIntent.setComponent(name);
                shareIntent.putExtra(android.content.Intent.EXTRA_TEXT, text);
                me.startActivity(shareIntent);
                show = true;
                break;
            }
        }

        if (!show)
        {
            me.runOnUiThread(new Runnable() {
                public void run() {
                    Toast.makeText(me, "Twitter Share Failed.", Toast.LENGTH_SHORT);
                }
            });
        }
    }

    public static void reportScore(int index, float score)
    {
        if (me.mGoogleApiClient != null && me.mGoogleApiClient.isConnected()) {
            Log.d(TAG,  String.format("--------- Report Player Score : %f --------", score));
            switch (index)
            {
                case 1:
                    Games.Leaderboards.submitScoreImmediate(me.mGoogleApiClient, me.getString(R.string.leaderboard_id_kernel), (long)(score * 100)).setResultCallback(new MyLeaderBoardSubmitScoreCallback());
                    break;
                case 2:
                    Games.Leaderboards.submitScoreImmediate(me.mGoogleApiClient, me.getString(R.string.leaderboard_id_second), (long)(score * 100)).setResultCallback(new MyLeaderBoardSubmitScoreCallback());
                    break;
                case 3:
                    Games.Leaderboards.submitScoreImmediate(me.mGoogleApiClient, me.getString(R.string.leaderboard_id_click), (long)(score * 100)).setResultCallback(new MyLeaderBoardSubmitScoreCallback());
                    break;
                case 4:
                    Games.Leaderboards.submitScoreImmediate(me.mGoogleApiClient, me.getString(R.string.leaderboard_id_level), (long)score).setResultCallback(new MyLeaderBoardSubmitScoreCallback());
                    break;
                default:
                    break;
            }
            Log.d(TAG, "--------- Sent Player Score --------");
        }
    }

    public static void showLeaderboard()
    {
        if (me.mGoogleApiClient != null && me.mGoogleApiClient.isConnected()) {
            Log.d(TAG, "--------- Show Leaderboard --------");
            me.startActivityForResult(Games.Leaderboards.getAllLeaderboardsIntent(me.mGoogleApiClient), REQUEST_LEADERBOARD);
        }
    }

    @Override
    protected void onStart() {
        super.onStart();
        mGoogleApiClient.connect();
        Log.d(TAG,"---------- Google Play Game Connecting -----------");
    }

    @Override
    protected void onStop() {
        super.onStop();
        mGoogleApiClient.disconnect();
        Log.d(TAG,"---------- Google Play Game Stop -----------");
    }

    @Override
    public void onConnected(Bundle arg0) {
        // TODO Auto-generated method stub
        Log.d(TAG,"---------- Google Play Game Connected -----------");
    }

    @Override
    public void onConnectionSuspended(int arg0) {
        // TODO Auto-generated method stub
        // Attempt to reconnect
        mGoogleApiClient.connect();
        Log.d(TAG,"---------- Google Play Game ConnectionSuspended -----------");
    }

    @Override
    public void onConnectionFailed(ConnectionResult connectionResult) {
        // TODO Auto-generated method stub
        Log.d(TAG,"---------- Google Play Game ConnectionFailed -----------");
        if (mResolvingConnectionFailure) {
            // Already resolving
            return;
        }

        // If the sign in button was clicked or if auto sign-in is enabled,
        // launch the sign-in flow
        if (mSignInClicked || mAutoStartSignInflow) {
            mAutoStartSignInflow = false;
            mSignInClicked = false;
            mResolvingConnectionFailure = true;

            // Attempt to resolve the connection failure using BaseGameUtils.
            // The R.string.signin_other_error value should reference a generic
            // error string in your strings.xml file, such as "There was
            // an issue with sign in, please try again later."
            if (!BaseGameUtils.resolveConnectionFailure(this, mGoogleApiClient, connectionResult, RC_SIGN_IN, getString(R.string.signin_other_error))) {
                mResolvingConnectionFailure = false;
            }
        }

        // Put code here to display the sign-in button
    }
}

class MyLeaderBoardSubmitScoreCallback implements ResultCallback<Leaderboards.SubmitScoreResult> {
    @Override
    public void onResult(Leaderboards.SubmitScoreResult res) {
        int code = res.getStatus().getStatusCode();
        Log.d("cocos2d-x debug info", "--------- Submit Score Status  --------" + Integer.toString(code) + "-------");
        if (res.getStatus().getStatusCode() == 0) {
            // data sent successfully to server.
            // display toast.
            Log.d("cocos2d-x debug info", "--------- Reported Player Score --------");
        }
    }
}