#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "PluginChartboost/PluginChartboost.h"
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application, public sdkbox::ChartboostListener
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    
    
    void initAppInfo();
    void saveBucket();
    
    
    void onChartboostCached(const std::string& name);
    bool onChartboostShouldDisplay(const std::string& name);
    void onChartboostDisplay(const std::string& name);
    void onChartboostDismiss(const std::string& name);
    void onChartboostClose(const std::string& name);
    void onChartboostClick(const std::string& name);
    void onChartboostReward(const std::string& name, int reward);
    void onChartboostFailedToLoad(const std::string& name, sdkbox::CB_LoadError e);
    void onChartboostFailToRecordClick(const std::string& name, sdkbox::CB_ClickError e);
    void onChartboostConfirmation();
    void onChartboostCompleteStore();
};

#endif // _APP_DELEGATE_H_

