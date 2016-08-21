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
import android.widget.Toast;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.List;

public class AppActivity extends Cocos2dxActivity {
    private static AppActivity me = null;

    private final static String APP_PNAME = "com.eckert.kernelking";// Package Name
    protected void onCreate(Bundle savedInstanceState){
        me = this;
        super.onCreate(savedInstanceState);

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
}
