


#include "AppDelegate.h"
#include "GameScene.hpp"
#include "TutorialScene.hpp"
#include "VideoScene.hpp"
#include "InvestmentLayer.hpp"
#include "CashManager.hpp"

USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Popcorn", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Popcorn");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
//    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
//    Size frameSize = glview->getFrameSize();
//    // if the frame's height is larger than the height of medium size.
//    if (frameSize.height > mediumResolutionSize.height)
//    {        
//        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is larger than the height of small size.
//    else if (frameSize.height > smallResolutionSize.height)
//    {        
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is smaller than the height of medium size.
//    else
//    {        
//        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
//    }

    register_all_packages();
    
    FileUtils *sharedFileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    searchPaths.push_back("background");
    searchPaths.push_back("engineimages");
    searchPaths.push_back("engineimages/skewed");
    searchPaths.push_back("engineimages/unlockables");
    searchPaths.push_back("engineimages/invest");
    searchPaths.push_back("engineimages/business");
    searchPaths.push_back("engineimages/political");
    searchPaths.push_back("sounds");
    searchPaths.push_back("fonts");
    sharedFileUtils->setSearchPaths(searchPaths);
    
    initAppInfo();

    // create a scene. it's an autorelease object
    
    Scene *scene;
    if(!UserDefault::getInstance()->getBoolForKey("tutorial", false))
    {
        scene = TutorialScene::createScene();
    }else
    {
        scene = GameScene::createScene();
//        scene = InvestmentLayer::createScene();
    }
    
    // run
    director->runWithScene(scene);

    return true;
}

void AppDelegate::initAppInfo()
{
    UserDefault* userdefault = UserDefault::getInstance();
    if (!userdefault->getBoolForKey("IsAppRunningFirstTime", false)) {
        userdefault->setBoolForKey("IsAppRunningFirstTime", true);
        
        userdefault->setIntegerForKey("piggybank_count", 0);
        userdefault->setIntegerForKey("mattress_count", 0);
        userdefault->setIntegerForKey("comicbook_count", 0);
        userdefault->setIntegerForKey("savingaccount_count", 0);
        userdefault->setIntegerForKey("bitcoinaccount_count", 0);
        userdefault->setIntegerForKey("stockes_count", 0);
        userdefault->setIntegerForKey("bookie_count", 0);
        userdefault->setIntegerForKey("loanshark_count", 0);
        userdefault->setIntegerForKey("angelinvestment_count", 0);
        userdefault->setIntegerForKey("vanturecapital_count", 0);
        userdefault->setIntegerForKey("porkbelly_count", 0);
        userdefault->setIntegerForKey("hedgefund_count", 0);
        userdefault->setIntegerForKey("investmentbank_count", 0);
        userdefault->setIntegerForKey("insidertrading_count", 0);
        userdefault->setIntegerForKey("mortgage_count", 0);
        userdefault->setIntegerForKey("pyramid_count", 0);
        userdefault->setIntegerForKey("hypercube_count", 0);
        userdefault->setIntegerForKey("unholy_count", 0);
        userdefault->setIntegerForKey("honey_count", 0);
        
        userdefault->setFloatForKey("piggybank_price",      80*1.7);
        userdefault->setFloatForKey("mattress_price",       400*1.7);
        userdefault->setFloatForKey("comicbook_price",      1600*1.7);
        userdefault->setFloatForKey("savingaccount_price",  8000*1.7);
        userdefault->setFloatForKey("bitcoinaccount_price", 39000*1.7);
        userdefault->setFloatForKey("stockes_price",        156000*1.7);
        userdefault->setFloatForKey("bookie_price",         650000*1.7);
        userdefault->setFloatForKey("loanshark_price",      1620000*1.7);
        userdefault->setFloatForKey("angelinvestment_price", 3250000*1.7);
        userdefault->setFloatForKey("vanturecapital_price", 5200000*1.7);
        userdefault->setFloatForKey("porkbelly_price",      48750000*1.7);
        userdefault->setFloatForKey("hedgefund_price",      520000000*1.7);
        userdefault->setFloatForKey("investmentbank_price", 7800000000*1.7);
        userdefault->setFloatForKey("insidertrading_price", 650000000000*1.7);
        userdefault->setFloatForKey("mortgage_price",       22000000000000*1.7);
        userdefault->setFloatForKey("pyramid_price",        96500000000000*1.7);
        userdefault->setFloatForKey("hypercube_price",      1200000000000000*1.7);
        userdefault->setFloatForKey("unholy_price",         26000000000000000*1.7);
        userdefault->setFloatForKey("honey_price",          390000000000000000*1.7);
        
        
        userdefault->setIntegerForKey("paperroute_count", 0);
        userdefault->setIntegerForKey("lemon_count", 0);
        userdefault->setIntegerForKey("flower_count", 0);
        userdefault->setIntegerForKey("coffee_count", 0);
        userdefault->setIntegerForKey("fastfood_count", 0);
        userdefault->setIntegerForKey("casino_count", 0);
        userdefault->setIntegerForKey("cigrate_count", 0);
        userdefault->setIntegerForKey("soda_count", 0);
        userdefault->setIntegerForKey("railroad_count", 0);
        userdefault->setIntegerForKey("strip_count", 0);
        userdefault->setIntegerForKey("arctic_count", 0);
        userdefault->setIntegerForKey("candytheft_count", 0);
        userdefault->setIntegerForKey("oldlady_count", 0);
        userdefault->setIntegerForKey("clown_count", 0);
        userdefault->setIntegerForKey("nsa_count", 0);
        userdefault->setIntegerForKey("dog_count", 0);
        userdefault->setIntegerForKey("cat_count", 0);
        userdefault->setIntegerForKey("cryogenic_count", 0);
        userdefault->setIntegerForKey("banana_count", 0);
        
////////
        userdefault->setFloatForKey("paperroute_price", 240);
        userdefault->setFloatForKey("lemon_price",      2187.5);
        userdefault->setFloatForKey("flower_price",     15000);
        userdefault->setFloatForKey("coffee_price",     105000);
        userdefault->setFloatForKey("fastfood_price",   700000);
        userdefault->setFloatForKey("casino_price",     4151250);
        userdefault->setFloatForKey("cigrate_price",    24900000);
        userdefault->setFloatForKey("soda_price",       210000000);
        userdefault->setFloatForKey("railroad_price",   1210000000);
        userdefault->setFloatForKey("strip_price",      7320000000);
        userdefault->setFloatForKey("arctic_price",     42840000000);
        userdefault->setFloatForKey("candytheft_price", 246400000000);
        userdefault->setFloatForKey("oldlady_price",    1880000000000);
        userdefault->setFloatForKey("clown_price",      11068750000000);
        userdefault->setFloatForKey("nsa_price",        64400000000000);
        userdefault->setFloatForKey("dog_price",        377865000000000);
        userdefault->setFloatForKey("cat_price",        2203200000000000);
        userdefault->setFloatForKey("cryogenic_price",  13000000000000000);
        userdefault->setFloatForKey("banana_price",     92500000000000000);
        
        
        userdefault->setIntegerForKey("0_count", 0);
        userdefault->setIntegerForKey("1_count", 0);
        userdefault->setIntegerForKey("2_count", 0);
        userdefault->setIntegerForKey("3_count", 0);
        userdefault->setIntegerForKey("4_count", 0);
        userdefault->setIntegerForKey("5_count", 0);
        userdefault->setIntegerForKey("6_count", 0);
        userdefault->setIntegerForKey("7_count", 0);
        userdefault->setIntegerForKey("8_count", 0);
        userdefault->setIntegerForKey("9_count", 0);
        userdefault->setIntegerForKey("10_count", 0);
        userdefault->setIntegerForKey("11_count", 0);
        userdefault->setIntegerForKey("12_count", 0);
        userdefault->setIntegerForKey("13_count", 0);
        userdefault->setIntegerForKey("14_count", 0);
        userdefault->setIntegerForKey("15_count", 0);
        
        userdefault->setFloatForKey("0_price", 200);
        userdefault->setFloatForKey("1_price", 1000);
        userdefault->setFloatForKey("2_price", 3000);
        userdefault->setFloatForKey("3_price", 9800);
        userdefault->setFloatForKey("4_price", 15000);
        userdefault->setFloatForKey("5_price", 60000);
        userdefault->setFloatForKey("6_price", 700000);
        userdefault->setFloatForKey("7_price", 8900000);
        userdefault->setFloatForKey("8_price", 45000000);
        userdefault->setFloatForKey("9_price", 700000000);
        userdefault->setFloatForKey("10_price", 10000000000);
        userdefault->setFloatForKey("11_price", 777000000000);
        userdefault->setFloatForKey("12_price", 105000000000000);
        userdefault->setFloatForKey("13_price", 882500000000000);
        userdefault->setFloatForKey("14_price", 6870000000000000);
        userdefault->setFloatForKey("15_price", 70000000000000000);
        
        userdefault->setFloatForKey("currentcash", 0);
        userdefault->setFloatForKey("currentshakers", 0);
        userdefault->setFloatForKey("currentbucket", 0);
        userdefault->setIntegerForKey("currentdate", 0);
        
        userdefault->setBoolForKey("classicbox", false);
        userdefault->setBoolForKey("chefhat", false);
        userdefault->setBoolForKey("Upiggbank", false);
        userdefault->setBoolForKey("moon", false);
        userdefault->setBoolForKey("earth", false);
        userdefault->setBoolForKey("spaceship", false);
        userdefault->setBoolForKey("ufo", false);
        userdefault->setBoolForKey("dinnerplate", false);
        userdefault->setBoolForKey("trophycup", false);
        userdefault->setBoolForKey("car", false);
        userdefault->setBoolForKey("umbrella", false);
        userdefault->setBoolForKey("diamond", false);
        
        
        userdefault->setBoolForKey("facebook", false);
        userdefault->setBoolForKey("twitter", false);
        userdefault->setIntegerForKey("share_count", 0);
        userdefault->setBoolForKey("Video", false);
        userdefault->setBoolForKey("20XVideo", false);
        userdefault->setBoolForKey("DBLVideo", false);
        userdefault->setBoolForKey("ABC", false);
        userdefault->setBoolForKey("DEF", false);
        userdefault->setBoolForKey("ShakerBonus", false);
        userdefault->setBoolForKey("PlayedShaker", false);
        userdefault->setBoolForKey("GoldBonus", false);
        userdefault->setBoolForKey("PlayedGold", false);
        userdefault->setBoolForKey("2xBonus", false);
        userdefault->setBoolForKey("Played2x", false);
        userdefault->setBoolForKey("20xBonus", false);
        userdefault->setBoolForKey("Played20x", false);
        userdefault->setBoolForKey("RemoveAds", false);
        userdefault->setBoolForKey("Forever20", false);
        userdefault->setBoolForKey("KernelSale", false);
        userdefault->setBoolForKey("KingKernel", false);
        userdefault->setBoolForKey("KingKernelPurchased", false);
        userdefault->setBoolForKey("Treadmill", false);
        userdefault->setBoolForKey("TreadmillPurchased", false);
        userdefault->setBoolForKey("RibbonShown", false);
        userdefault->setBoolForKey("tutorial", true);
        
        userdefault->setFloatForKey("chefhat_price",    50000);
        userdefault->setFloatForKey("Upiggybank_price", 10000000);
        userdefault->setFloatForKey("moon_price",       500000000);
        userdefault->setFloatForKey("earth_price",      10000000000);
        userdefault->setFloatForKey("spaceship_price",  500000000000);
        userdefault->setFloatForKey("ufo_price",        10000000000000);
        userdefault->setFloatForKey("dinnerplate_price", 500000000000000);
        userdefault->setFloatForKey("trophycup_price",  500000000000000);
        userdefault->setFloatForKey("car_price",        500000000000000);
        userdefault->setFloatForKey("umbrella_price",   10000000000000000);
        userdefault->setFloatForKey("diamond_price",    100000000000000000);
        userdefault->setFloatForKey("prestige_price",   500000000000000000);
        
        userdefault->setBoolForKey("Reviewed", false);
        userdefault->setBoolForKey("ShowReview", false);
        userdefault->setBoolForKey("NewCustomBG", false);
        
        userdefault->setIntegerForKey("reviewPopup", 0);
        userdefault->setIntegerForKey("CustomPopcorn", 0);
        userdefault->setIntegerForKey("CustomBG", 0);
        
        userdefault->setFloatForKey("p1_price", 5);
        userdefault->setFloatForKey("p2_price", 5);
        userdefault->setFloatForKey("p3_price", 5);
        userdefault->setFloatForKey("p4_price", 5);
        userdefault->setFloatForKey("p5_price", 5);
        userdefault->setFloatForKey("p6_price", 5);
        userdefault->setFloatForKey("p7_price", 5);
        userdefault->setFloatForKey("p8_price", 5);
        userdefault->setFloatForKey("p9_price", 5);
        userdefault->setFloatForKey("p10_price", 5);
        userdefault->setFloatForKey("p11_price", 10);
        userdefault->setFloatForKey("p12_price", 10);
        userdefault->setFloatForKey("p13_price", 10);
        userdefault->setFloatForKey("p14_price", 10);
        userdefault->setFloatForKey("p15_price", 10);
        userdefault->setFloatForKey("p16_price", 10);
        userdefault->setFloatForKey("p17_price", 10);
        userdefault->setFloatForKey("p18_price", 10);
        userdefault->setFloatForKey("p19_price", 10);
        userdefault->setFloatForKey("p20_price", 10);
        userdefault->setFloatForKey("p21_price", 15);
        userdefault->setFloatForKey("p22_price", 15);
        userdefault->setFloatForKey("p23_price", 15);
        userdefault->setFloatForKey("p24_price", 15);
        userdefault->setFloatForKey("p25_price", 15);
        userdefault->setFloatForKey("p26_price", 15);
        userdefault->setFloatForKey("p27_price", 15);
        
        userdefault->setBoolForKey("p1", false);
        userdefault->setBoolForKey("p2", false);
        userdefault->setBoolForKey("p3", false);
        userdefault->setBoolForKey("p4", false);
        userdefault->setBoolForKey("p5", false);
        userdefault->setBoolForKey("p6", false);
        userdefault->setBoolForKey("p7", false);
        userdefault->setBoolForKey("p8", false);
        userdefault->setBoolForKey("p9", false);
        userdefault->setBoolForKey("p10", false);
        userdefault->setBoolForKey("p11", false);
        userdefault->setBoolForKey("p12", false);
        userdefault->setBoolForKey("p13", false);
        userdefault->setBoolForKey("p14", false);
        userdefault->setBoolForKey("p15", false);
        userdefault->setBoolForKey("p16", false);
        userdefault->setBoolForKey("p17", false);
        userdefault->setBoolForKey("p18", false);
        userdefault->setBoolForKey("p19", false);
        userdefault->setBoolForKey("p20", false);
        userdefault->setBoolForKey("p21", false);
        userdefault->setBoolForKey("p22", false);
        userdefault->setBoolForKey("p23", false);
        userdefault->setBoolForKey("p24", false);
        userdefault->setBoolForKey("p25", false);
        userdefault->setBoolForKey("p26", false);
        
        userdefault->setFloatForKey("ocean_price",      1);
        userdefault->setFloatForKey("city_price",       2);
        userdefault->setFloatForKey("sky_price",        3);
        userdefault->setFloatForKey("universe_price",   4);
        userdefault->setFloatForKey("jungle_price",     5);
        userdefault->setFloatForKey("desert_price",     6);
        userdefault->setFloatForKey("beach_price",      7);
    }
}

void AppDelegate::saveBucket()
{
    CashManager *cashmanager = CashManager::getInstance();
    UserDefault::getInstance()->setFloatForKey("currentbucket", cashmanager->getCurrentBucket());
    float bucketRemaining = cashmanager->getBucketSize() - cashmanager->getCurrentBucket();
    float secTofull = bucketRemaining / (cashmanager->getCashPerHour()  / 3600);
    
    time_t seconds;
    
    seconds = time (NULL);
    printf ("%d seconds since January 1, 1970", (int)seconds);
    UserDefault::getInstance()->setIntegerForKey("currentdate", (int)seconds);

    
//    NSDate *date=[NSDate date];
//    [[NSUserDefaults standardUserDefaults] setObject:date forKey:@"currentdate"];
//    NSDate *fireDate=[NSDate dateWithTimeIntervalSinceNow:secTofull];
//    
//    UILocalNotification *localNotification = [[UILocalNotification alloc] init];
//    localNotification.fireDate = fireDate;
//    localNotification.repeatInterval = NSWeekdayCalendarUnit;
//    localNotification.timeZone = [NSTimeZone systemTimeZone];
//    
//    localNotification.alertBody = @"Your bucket is full!";
//    localNotification.alertAction = @"You're wasting Kernels! Don't forget to empty your bucket.";
//    localNotification.soundName = UILocalNotificationDefaultSoundName;
//    
//    // Schedule it with the app
//    [[UIApplication sharedApplication] scheduleLocalNotification:localNotification];
//    [localNotification release];
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    saveBucket();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    CashManager *cashmanager = CashManager::getInstance();
    cashmanager->reloadCashPerSecondAndCashPerSwap();
    UserDefault *userdefault = UserDefault::getInstance();
    if (cashmanager->getCashPerHour() != 0) {
        time_t cur_seconds;
        cur_seconds = time (NULL);
        int old_second = userdefault->getIntegerForKey("currentdate");
        int sec = (int)cur_seconds - old_second;
        if (sec < 0) {
            sec = -sec;
        }else if (userdefault->getIntegerForKey("reviewPopup") == 1) {
            userdefault->setIntegerForKey("reviewPopup", 2);
        } else if (userdefault->getIntegerForKey("reviewPopup") == 2) {
            userdefault->setIntegerForKey("reviewPopup", 3);
        } else if (userdefault->getIntegerForKey("reviewPopup") == 3) {
            userdefault->setIntegerForKey("reviewPopup", 4);
        } else if (userdefault->getIntegerForKey("reviewPopup") == 4) {
            userdefault->setIntegerForKey("reviewPopup", 5);
        } else if (userdefault->getIntegerForKey("reviewPopup") == 5) {
            userdefault->setIntegerForKey("reviewPopup", 6);
        } else if (userdefault->getIntegerForKey("reviewPopup") == 6) {
            userdefault->setBoolForKey("ShowReview", true);
        }
        
        cashmanager->setCurrentBucket(userdefault->getFloatForKey("currentbucket"));
        cashmanager->setCurrentBucket(cashmanager->getCurrentBucket() + cashmanager->getCashPerHour() / 3600 * sec);
        if (cashmanager->getCurrentBucket() > cashmanager->getBucketSize()) {
            cashmanager->setCurrentBucket(cashmanager->getBucketSize());
        }
    }
    
}
