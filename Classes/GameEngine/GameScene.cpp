//
//  GameScene.cpp
//  Popcorn
//
//  Created by Hans on 7/27/16.
//
//

#include "GameScene.hpp"
#include "CashManager.hpp"
#include "Constants.h"

#include "InvestmentLayer.hpp"
#include "BusinessLayer.hpp"
#include "PoliticalLayer.hpp"
#include "InAppPurchaseLayer.hpp"
#include "PopcornShopLayer.hpp"

#include "ReviewScene.hpp"
#include "VideoScene.hpp"
#include "BucketScene.hpp"

#include "PluginChartboost/PluginChartboost.h"

using namespace sdkbox;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    touchListener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    CashManager::getInstance()->reloadCashPerSecondAndCashPerSwap();
    this->schedule(schedule_selector(GameScene::tick), 5.0f);
    m_userdefault = UserDefault::getInstance();
    
    PluginChartboost::cache("Rewarded Video");
    
    int backgroundID = m_userdefault->getIntegerForKey("CustomBG", 0);
    
    switch (backgroundID) {
        case 0:
            background1 = Sprite::create("bluebackground.png");
            background2 = Sprite::create("bluebackground.png");
            break;
        case 1:
            background1 = Sprite::create("ocean.png");
            background2 = Sprite::create("oceanBack.png");
            break;
        case 2:
            background1 = Sprite::create("city.png");
            background2 = Sprite::create("city.png");
            break;
        case 3:
            background1 = Sprite::create("sky.png");
            background2 = Sprite::create("skyBack.png");
            break;
        case 4:
            background1 = Sprite::create("universe.png");
            background2 = Sprite::create("universe.png");
            break;
        case 5:
            background1 = Sprite::create("jungle.png") ;
            background2 = Sprite::create("jungleBack.png");
            break;
        case 6:
            background1 = Sprite::create("desert.png");
            background2 = Sprite::create("desertBack.png");
            break;
        case 7:
            background1 = Sprite::create("beach.png");
            background2 = Sprite::create("beachBack.png");
            break;
        default:
            background1 = Sprite::create("bluebackground.png");
            background2 = Sprite::create("bluebackground.png");
            break;
    }
    //add schedule to move backgrounds
    
    background1->setAnchorPoint(Vec2(0.0f, 0.0f));
    background2->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    background1->setScale(G_SCALEM);
    background2->setScale(G_SCALEM);
    background1->setPosition(Vec2(0, 0));
    background2->setPosition(Vec2(background1->getBoundingBox().size.width - 1, 0));
    
    this->addChild(background1);
    this->addChild(background2);
    
    if (m_userdefault->getBoolForKey("Treadmill", false) == false) {
        this->schedule(schedule_selector(GameScene::scroll), 0.005f);
    }
    
    // Submit Score to leaderboard.
    float currentCash = CashManager::getInstance()->getCurrentCash();
    float prestige = UserDefault::getInstance()->getIntegerForKey("prestige_count");
    
    log("Game Scene : CurrentCash = %f", currentCash);
    log("Game Scene : Prestige = %f", prestige);
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    
#else
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                      ,  "org/cocos2dx/cpp/AppActivity"
                                      ,  "reportScore"
                                      ,  "(IF;)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, 1, currentCash);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, 4, prestige);
    }
#endif
    
    classicbox = true;
    chefhat = true;
    piggybank = true;
    moon = true;
    earth = true;
    spaceship = true;
    ufo = true;
    dinnerplate = true;
    trophy = true;
    car = true;
    umbrella = true;
    diamond = true;
    ribbonshown = true;
    facebook = true;
    twitter = true;
    m_b_TwentyReward = true;
    kingkernel = true;
    
    bottomClickbar = Sprite::create("BottomClick_Bar.png");
    bottomClickbar->setPosition(Vec2(0, 0));
    bottomClickbar->setAnchorPoint(Vec2(1.0, 1.0));
    bottomClickbar->setScale(G_SCALEM);
    this->addChild(bottomClickbar, 2000);
    
    topClickbar = Sprite::create("TopClick_Bar.png");
    topClickbar->setPosition(Vec2(0, G_SHEIGHT));
    topClickbar->setAnchorPoint(Vec2(1.0, 1.0));
    topClickbar->setScale(G_SCALEM);
    this->addChild(topClickbar, 2000);
    this->topMove();
    
    m_spt_Bucket = Sprite::create("flatpopcornbox.png");
    m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
    m_spt_Bucket->setAnchorPoint(Vec2(0.5, 0.5));
    m_spt_Bucket->setScale(G_SCALEM);
    this->addChild(m_spt_Bucket, 100);
    
    digitSprite = Sprite::create("score_label.png");
    digitSprite->setScale(G_SCALEM);
    digitSprite->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT - topClickbar->getBoundingBox().size.height - digitSprite->getBoundingBox().size.height / 2 - 20 * G_SCALEM));
    this->addChild(digitSprite, 1001);
    
    perSecondRibbon = Sprite::create("PerSecondLabel.png");
    perSecondRibbon->setScale(G_SCALEM);
    perSecondRibbon->setPosition(Vec2(G_SWIDTH / 2, digitSprite->getPositionY() - digitSprite->getBoundingBox().size.height - 20 * G_SCALEM));
    this->addChild(perSecondRibbon, 999);
    
    m_ttfconf_score.fontFilePath = "AmericanTypewriter.ttf";
    m_ttfconf_score.fontSize = G_SWIDTH / 15;
    
    m_lbl_Score = Label::createWithTTF(m_ttfconf_score, StringUtils::format("%s Kernels", CashManager::getInstance()->convertAmountToShortString(CashManager::getInstance()->getCurrentCash()).c_str()));
    m_lbl_Score->setWidth(digitSprite->getBoundingBox().size.width);
    m_lbl_Score->setHorizontalAlignment(TextHAlignment::CENTER);
    m_lbl_Score->setVerticalAlignment(TextVAlignment::CENTER);
    m_lbl_Score->setColor(Color3B(1, 50, 20));
    m_lbl_Score->setPosition(Vec2(digitSprite->getPositionX(),digitSprite->getPositionY()));
    this->addChild(m_lbl_Score, 1001);
    
    MenuItemImage *investButton = MenuItemImage::create("button1.png",
                                                        "button1.png",
                                                        [&](Ref *sender)
                                                        {
                                                            log("Invest Button Clicked");
                                                            // Cache ChartboostReward Video.
                                                            
                                                            this->setButtonEnable(false);
                                                            adCount++;
                                                            if (adCount >= 12 && !m_userdefault->getBoolForKey("RemoveAds", false)) {
                                                                // show Ads.
                                                                PluginChartboost::show("Default");
                                                                adCount = 0;
                                                            }
                                                            SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                            
                                                            // Show InvestmentTableViewController
                                                            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                            InvestmentLayer *layer = InvestmentLayer::create();
                                                            layer->setContentSize(Size(G_SWIDTH, G_SHEIGHT * 0.75));
                                                            layer->showContent();
                                                            this->addChild(layer, 7000);
                                                        });
    
    MenuItemImage *businessButton = MenuItemImage::create("button2.png",
                                                          "button2.png",
                                                          [&](Ref *sender)
                                                          {
                                                              log("Business Button Clicked");
                                                              // Cache ChartboostReward Video.
                                                              this->setButtonEnable(false);
                                                              adCount++;
                                                              if (adCount >= 12 && !m_userdefault->getBoolForKey("RemoveAds", false)) {
                                                                  // show Ads.
                                                                  PluginChartboost::show("Default");
                                                                  adCount = 0;
                                                              }
                                                              SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                              
                                                              // Show InvestmentTableViewController
                                                              Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                              BusinessLayer *layer = BusinessLayer::create();
                                                              layer->setContentSize(Size(G_SWIDTH, G_SHEIGHT * 0.75));
                                                              layer->showContent();
                                                              this->addChild(layer, 7000);
                                                          });
    
    MenuItemImage *politicalButton = MenuItemImage::create("button3.png",
                                                           "button3.png",
                                                           [&](Ref *sender)
                                                           {
                                                               log("Political Button Clicked");
                                                               // Cache ChartboostReward Video.
                                                               this->setButtonEnable(false);
                                                               adCount++;
                                                               if (adCount >= 12 && !m_userdefault->getBoolForKey("RemoveAds", false)) {
                                                                   // show Ads.
                                                                   PluginChartboost::show("Default");
                                                                   adCount = 0;
                                                               }
                                                               SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                               // Show PoliticalViewController
                                                               Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                               PoliticalLayer *layer = PoliticalLayer::create();
                                                               layer->setContentSize(Size(G_SWIDTH, G_SHEIGHT * 0.75));
                                                               layer->showContent();
                                                               this->addChild(layer, 7000);
                                                           });
    
    MenuItemImage *inappButton = MenuItemImage::create("upgradebutton.png",
                                                       "upgradebutton.png",
                                                       [&](Ref *sender)
                                                       {
                                                           log("InApp Button Clicked");
                                                           // Cache ChartboostReward Video.
                                                           this->setButtonEnable(false);
                                                           adCount++;
                                                           if (adCount >= 12 && !m_userdefault->getBoolForKey("RemoveAds", false)) {
                                                               // show Ads.
                                                               PluginChartboost::show("Default");
                                                               adCount = 0;
                                                           }
                                                           SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                           // Show InAppViewController
                                                           Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                           InAppPurchaseLayer *layer = InAppPurchaseLayer::create();
                                                           layer->setContentSize(Size(G_SWIDTH, G_SHEIGHT * 0.75));
                                                           layer->showContent();
                                                           this->addChild(layer, 7000);
                                                       });
    
    MenuItemImage *popcornButton = MenuItemImage::create("new bag.png",
                                                         "new bag.png",
                                                         [&](Ref *sendder)
                                                         {
                                                             log("Popcorn Button Clicked");
                                                             // Cache RewardVideo
                                                             this->setButtonEnable(false);
                                                             adCount++;
                                                             if (adCount >= 8 && !m_userdefault->getBoolForKey("RemoveAds", false)) {
                                                                 // show Chartboost Interstitial
                                                                 PluginChartboost::show("Default");
                                                                 adCount = 0;
                                                             }
                                                             SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                             // Show Popcorn viewcontroller
                                                             Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                             PopcornShopLayer *layer = PopcornShopLayer::create();
                                                             layer->setContentSize(Size(G_SWIDTH, G_SHEIGHT * 0.75));
                                                             layer->showContent();
                                                             this->addChild(layer, 7000);
                                                         });
    
    investButton->setPosition(G_SWIDTH / 14, 10 * G_SCALEM);
    businessButton->setPosition(investButton->getPositionX() + G_SWIDTH / 5, 10 * G_SCALEM);
    politicalButton->setPosition(businessButton->getPositionX() + G_SWIDTH / 5, 10 * G_SCALEM);
    inappButton->setPosition(politicalButton->getPositionX() + G_SWIDTH / 5, 10 * G_SCALEM);
    popcornButton->setPosition(inappButton->getPositionX() + G_SWIDTH / 5, 10 * G_SCALEM);
    
    investButton->setAnchorPoint(Vec2(0, 0));
    businessButton->setAnchorPoint(Vec2(0, 0));
    politicalButton->setAnchorPoint(Vec2(0, 0));
    inappButton->setAnchorPoint(Vec2(0.2f, 0));
    popcornButton->setAnchorPoint(Vec2(0, 0));
    
    investButton->setScale(0.2f * G_SCALEM);
    businessButton->setScale(0.4f * G_SCALEM);
    inappButton->setScale(0.15f * G_SCALEM);
    politicalButton->setScale(0.25f * G_SCALEM);
    popcornButton->setScale(0.2f * G_SCALEM);
    
    bucketButton = MenuItemImage::create("emptybox.png",
                                         "emptybox.png",
                                         [&](Ref *sender){
                                                            // Cache ChartboostReward Video.
                                                            PluginChartboost::cache("Rewarded Video");
                                                            this->setButtonEnable(false);
                                                            // Show Ads View
                                                            this->showBucket();
                                                            log("Bucket Button Clicked");
                                         });
    bucketButton->setPosition(Vec2(G_SWIDTH / 25, G_SHEIGHT / 10));
    bucketButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    bucketButton->setVisible(false);
    bucketButton->setScale(G_SCALEM);
    
    gamecenterButton = MenuItemImage::create("leaderboard.png",
                                             "leaderboard.png",
                                             [&](Ref *sender){
                                                                SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                                // Game Center Login
                                                                // Show Leaderboard
                                                                // SubmitScore
                                                 float currentCash = CashManager::getInstance()->getCurrentCash();
                                                 float cashPerSecond = CashManager::getInstance()->getCashPerSecond();
                                                 float cashPerSwap = CashManager::getInstance()->getCashPerSwap();
                                                 float prestige = UserDefault::getInstance()->getIntegerForKey("prestige_count");
                                                 
                                                 log("Game Scene : CurrentCash = %f", currentCash);
                                                 log("Game Scene : cashPerSecond = %f", cashPerSecond);
                                                 log("Game Scene : cashPerSwap = %f", cashPerSwap);
                                                 log("Game Scene : Prestige = %f", prestige);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                                                 
#else
                                                 JniMethodInfo t;
                                                 if (JniHelper::getStaticMethodInfo(t
                                                                                   ,  "org/cocos2dx/cpp/AppActivity"
                                                                                   ,  "showLeaderboard"
                                                                                   ,  "()V"))
                                                 {
                                                     t.env->CallStaticVoidMethod(t.classID, t.methodID);
                                                 }
                                                 if (JniHelper::getStaticMethodInfo(t
                                                                                   ,  "org/cocos2dx/cpp/AppActivity"
                                                                                   ,  "reportScore"
                                                                                   ,  "(IF)V"))
                                                 {
                                                     t.env->CallStaticVoidMethod(t.classID, t.methodID, 1, currentCash);
                                                     t.env->CallStaticVoidMethod(t.classID, t.methodID, 2, cashPerSecond);
                                                     t.env->CallStaticVoidMethod(t.classID, t.methodID, 3, cashPerSwap);
                                                     t.env->CallStaticVoidMethod(t.classID, t.methodID, 4, prestige);
                                                 }
#endif
                                                                log("GameCenter Button Clicked");
                                             });
    gamecenterButton->setPosition(Vec2(G_SWIDTH / 12, perSecondRibbon->getPositionY() - perSecondRibbon->getContentSize().height / 2 - G_SHEIGHT / 10));
    gamecenterButton->setScale(0.15f * G_SCALEM);
    
    reviewbutton = MenuItemImage::create("whitestar.png",
                                         "whitestar.png",
                                         [&](Ref *sender){
                                                                SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                                this->setButtonEnable(false);
                                                                // Show ReviewViewController
                                                                Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                                ReviewScene *layer = ReviewScene::create();
                                                                this->addChild(layer, 7000);
                                                                log("Review Button Clicked");
                                         });
    reviewbutton->setPosition(Vec2(G_SWIDTH * 11 / 12, perSecondRibbon->getPositionY() - perSecondRibbon->getContentSize().height / 2 - G_SHEIGHT / 10));
    reviewbutton->setVisible(false);
    reviewbutton->setScale(0.1f * G_SCALEM);
    
    videobutton = MenuItemImage::create("tvPlayCrop.png",
                                        "tvPlayCrop.png",
                                        [&](Ref *sender){
                                                            SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                            this->setButtonEnable(false);
                                                            // Show Video ViewController
                                                            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                            VideoScene *layer = VideoScene::create();
                                                            this->addChild(layer, 7000);
                                                            m_userdefault->setBoolForKey("RDMNUMB", true);
                                                            log("Video Button Clicked");
                                        });
    videobutton->setPosition(Vec2(gamecenterButton->getPositionX() - gamecenterButton->getBoundingBox().size.width / 2, gamecenterButton->getPositionY() - gamecenterButton->getBoundingBox().size.height / 2 - videobutton->getBoundingBox().size.height));
    videobutton->setAnchorPoint(Vec2(0.0f, 0.5f));
    videobutton->setVisible(false);
    videobutton->setScale(G_SCALEM * 0.9);
    
    m_btnmenu = Menu::create(investButton, businessButton, politicalButton, inappButton, popcornButton, bucketButton, gamecenterButton, videobutton, /*reviewbutton,*/ NULL);
    m_btnmenu->setPosition(Vec2(0, 0));
    this->addChild(m_btnmenu, 1100);
        
    Sprite *belowBorder = Sprite::create("bar.png");
    belowBorder->setAnchorPoint(Vec2(0, 0));
    belowBorder->setPosition(Vec2(0, 0));
    belowBorder->setScale(1.2f * G_SCALEM);
    this->addChild(belowBorder, 1000);
    
    m_spt_Cover = Sprite::create("flat ribbon.png");
    m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
    m_spt_Cover->setScale(G_SCALEM);
    this->addChild(m_spt_Cover, 1000);
    
    m_lbl_MoneyPerSwap=Label::createWithTTF(StringUtils::format("%.0f Kernels",CashManager::getInstance()->getCashPerSwap()), "AmericanTypewriter.ttf", G_SWIDTH / 15);
    m_lbl_MoneyPerSwap->setColor(Color3B(1, 50, 20));
    m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
    m_lbl_MoneyPerSwap->setDimensions(m_spt_Cover->getBoundingBox().size.width, m_spt_Cover->getBoundingBox().size.height);
    m_lbl_MoneyPerSwap->setHorizontalAlignment(TextHAlignment::CENTER);
    m_lbl_MoneyPerSwap->setVerticalAlignment(TextVAlignment::CENTER);
    this->addChild(m_lbl_MoneyPerSwap, 1000);
    
    m_lbl_MoneyPerSecond=Label::createWithTTF(StringUtils::format("%.2f Kernels/Sec",CashManager::getInstance()->getCashPerSecond()), "AmericanTypewriter.ttf", G_SWIDTH / 15);
    m_lbl_MoneyPerSecond->setColor(Color3B(255, 255, 255));
    m_lbl_MoneyPerSecond->setPosition(perSecondRibbon->getPosition());
    m_lbl_MoneyPerSecond->setDimensions(perSecondRibbon->getBoundingBox().size.width, perSecondRibbon->getBoundingBox().size.height);
    m_lbl_MoneyPerSecond->setHorizontalAlignment(TextHAlignment::CENTER);
    m_lbl_MoneyPerSecond->setVerticalAlignment(TextVAlignment::CENTER);
    this->addChild(m_lbl_MoneyPerSecond, 1000);
    
    swapsCount = 0;
    
    this->schedule(schedule_selector(GameScene::addPerSecond), 1.0f);
    this->schedule(schedule_selector(GameScene::rollDollar), 0.2f);
    this->schedule(schedule_selector(GameScene::persecondLabel), 0.1f);
    this->checkUnlockables();
    
    this->schedule(schedule_selector(GameScene::unlockables), 0.5f);
    this->schedule(schedule_selector(GameScene::setBackground), 0.5f);
    this->schedule(schedule_selector(GameScene::checkVideo), 5.0f);
    this->schedule(schedule_selector(GameScene::checkPlayedVideo), 1.0f);
    this->schedule(schedule_selector(GameScene::checkReward), 1.0f);
    
    return true;
}

void GameScene::setButtonEnable(bool value)
{
    m_btnmenu->setEnabled(value);
}

void GameScene::scroll(float dt) {
    if (m_userdefault->getIntegerForKey("CustomBG") > 0) {
        
        background1->setPosition(Vec2( background1->getPositionX() - 2, background1->getPositionY()));
        background2->setPosition(Vec2( background2->getPositionX() - 2, background2->getPositionY()));
        
        //reset position when they are off from view.
        if (background1->getPositionX() < - background1->getBoundingBox().size.width ) {
            background1->setPosition(Vec2(background2->getPositionX() + background2->getBoundingBox().size.width, 0));
        }
        if (background2->getPositionX() < - background2->getBoundingBox().size.width ) {
            background2->setPosition(Vec2(background1->getPositionX() + background1->getBoundingBox().size.width, 0));
        }
    }
}
void GameScene::move() {
    if (m_userdefault->getIntegerForKey("CustomBG") > 0) {
        background1->setPosition(Vec2( background1->getPositionX() - 20, background1->getPositionY()));
        background2->setPosition(Vec2( background2->getPositionX() - 20, background2->getPositionY()));
        
        //reset position when they are off from view.
        if (background1->getPositionX() < - background1->getBoundingBox().size.width ) {
            background1->setPosition(Vec2(background2->getPositionX() + background2->getBoundingBox().size.width, 0));
        }
        if (background2->getPositionX() < - background2->getBoundingBox().size.width ) {
            background2->setPosition(Vec2(background1->getPositionX() + background1->getBoundingBox().size.width, 0));
        }
    }
}

void GameScene::checkPrestige(){
    if (m_userdefault->getIntegerForKey("prestige_count")) {
        m_spt_PrestigeRibbon = Sprite::create("prestige ribbon");
        m_spt_PrestigeRibbon->setPosition(Vec2(G_SWIDTH - G_SWIDTH / 25, G_SHEIGHT / 8));
        this->addChild(m_spt_PrestigeRibbon);
    }
}

void GameScene::checkPlayedVideo(float dt){
    if (m_userdefault->getBoolForKey("Video") == true) {
        videobutton->setVisible(false);
        m_userdefault->setBoolForKey("Video", false);
    }
}
void GameScene::checkReward(float dt){
    
    CashManager *cashmanager = CashManager::getInstance();
    
    if (m_userdefault->getBoolForKey("ShowReview") == true) {
        m_userdefault->setIntegerForKey("reviewPopup", 1);
        m_userdefault->setBoolForKey("ShowReview", false);
        
//        ReviewScene *layer = ReviewScene::create();
//        this->addChild(layer, 7000);
    }
    
    if (m_userdefault->getBoolForKey("CollectDBL") == true) {
        m_userdefault->setBoolForKey("CollectDBL", false);
        cashmanager->setCurrentCash(cashmanager->getCurrentCash() + cashmanager->getCurrentBucket() *  2);
        cashmanager->setCurrentBucket(0);
        cashmanager->setisBucketShown(false);
    }
    
    if (m_userdefault->getBoolForKey("20XVideo") == true) {
        cashmanager->setCurrentCash(cashmanager->getCurrentCash() * 1.1f);
        m_userdefault->setBoolForKey("20XVideo", false);
    }
    if (m_userdefault->getBoolForKey("PlayedShaker") == true) {
        cashmanager->setCurrentShaker(cashmanager->getCurrentShaker() + 2);
        m_userdefault->setBoolForKey("PlayedShaker", false);
    }
    if (m_userdefault->getBoolForKey("PlayedGold") == true) {
        this->bigPopcorn();
        m_userdefault->setBoolForKey("PlayedGold", false);
    }
    if (m_userdefault->getBoolForKey("Played2x") == true) {
        doublethirty = true;
        m_userdefault->setBoolForKey("Played2x", false);
    }
    if (m_userdefault->getBoolForKey("Played20x") == true) {
        twentyten = true;
        m_userdefault->setBoolForKey("Played20x", false);
    }
}

void GameScene::checkVideo(float dt){
    
    if(!PluginChartboost::isAvailable("Rewarded Video")) {
        videobutton->setVisible(false);
        PluginChartboost::cache("Rewarded Video");
    } else
        
        if (m_bool_Lmoving == false) {
            if (videoClicks >800) {
                
                
                if(PluginChartboost::isAvailable("Rewarded Video")) {
                    
                    m_int_LoadedVideo ++;
                    
                    if (m_userdefault->getBoolForKey("DEF") == false) {
                        m_userdefault->setBoolForKey("ABC", true);
                        m_userdefault->setBoolForKey("DEF", true);
                    }
                    if (m_int_LoadedVideo == 4) {
                        videoClicks = 0;
                        m_int_LoadedVideo = 0;
                        videobutton->setVisible(false);
                        m_userdefault->setBoolForKey("DEF", false);
                    } else {
                        videobutton->setVisible(true);
                    }
                }
                else {
                    videobutton->setVisible(false);
                    PluginChartboost::cache("Rewarded Video");
                }
            }
        }
        if (review >= 5){
            review = 0;
            reviewbutton->setVisible(false);
        }
}
void GameScene::checkUnlockables(){
    
    if (m_userdefault->getBoolForKey("classicbox") == true) {
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("flatpopcornbox.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        
        classicbox = false;
    }  else if (m_userdefault->getBoolForKey("chefhat") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("hat.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        chefhat = false;
    }
    else if (m_userdefault->getBoolForKey("Upiggbank") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("goldpiggy_bank.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 1.8, G_SHEIGHT / 2));
        
        piggybank = false;
        
    } else if (m_userdefault->getBoolForKey("moon") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("moon.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2.5));
        
        moon = false;
        
    } else if (m_userdefault->getBoolForKey("earth") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("earth.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        earth = false;
        
    } else if (m_userdefault->getBoolForKey("spaceship") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("popcorn_spaceship.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2.5));
        
        spaceship = false;
        
    } else if (m_userdefault->getBoolForKey("ufo") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("popcorn_ufo.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        ufo = false;
        
    } else if (m_userdefault->getBoolForKey("dinnerplate") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("tray.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        dinnerplate = false;
        
    } else if (m_userdefault->getBoolForKey("trophycup") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("popcorntrophy.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        trophy = false;
        
    } else if (m_userdefault->getBoolForKey("car") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("car.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        car = false;
        
    } else if (m_userdefault->getBoolForKey("umbrella") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("umbrella.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/1.75));
        
        umbrella = false;
        
    } else if (m_userdefault->getBoolForKey("diamond") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("diamond.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        
        diamond = false;
        
    }
    else if (m_userdefault->getBoolForKey("KingKernel") == true){
        
        m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
        m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
        m_spt_Bucket->setTexture("King Kernel.png");
        m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
        
        kingkernel = false;
        
    }
    
    if (m_userdefault->getBoolForKey("Forever20") == true) {
        m_spt_ForeverTwenty = Sprite::create("20x.png");
        m_spt_ForeverTwenty->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width * 0.5, m_spt_Cover->getPositionY()));
        m_spt_ForeverTwenty->setScale( 0.4 * G_SCALEM);
        m_spt_ForeverTwenty->setAnchorPoint(Vec2(0.4, 0.4));
        this->addChild(m_spt_ForeverTwenty, 1000);
    }
    
    if (m_userdefault->getIntegerForKey("prestige_count") > 0) {
        int prestigenumber = m_userdefault->getIntegerForKey("prestige_count");
        m_spt_PrestigeRibbon = Sprite::create("prestige ribbon.png");
        m_spt_PrestigeRibbon->setPosition(Vec2(G_SWIDTH * 11 / 12, G_SHEIGHT / 7));
        this->addChild(m_spt_PrestigeRibbon, 5000);
        m_lbl_Prestige = Label::createWithTTF(StringUtils::format("%.0d",prestigenumber), "AmericanTypewriter.ttf", G_SWIDTH / 25);
        m_lbl_Prestige->setPosition(Vec2(m_spt_PrestigeRibbon->getPositionX(), m_spt_PrestigeRibbon->getPositionY() + 8));
        this->addChild(m_lbl_Prestige, 5001);
    }
    
    m_spt_Bucket->setScale(G_SCALEM);
}
void GameScene::rollDollar(float dt){
    
    if (CashManager::getInstance()->getCashPerSecond() == 0) {
        return;
    }
    Sprite *sprite = Sprite::create("flat popcorn1.png");
    sprite->setOpacity(196);
    sprite->setScale(G_SCALEM);
    int number=G_SWIDTH;
    sprite->setPosition(Vec2(arc4random()%number+10, G_SHEIGHT + 300 * G_SCALEY));
    this->addChild(sprite, 0);
    Spawn *action = Spawn::create(MoveTo::create(1, Vec2(sprite->getPositionX(), 0)),
                                  RotateBy::create(1, arc4random() % 720),
                                  NULL);
    Sequence *seq=Sequence::create(action, RemoveSelf::create(), NULL);
    sprite->runAction(seq);
}
void GameScene::persecondLabel(float dt){
    
    double cash = CashManager::getInstance()->getCurrentCash();
    m_lbl_Score->setString(StringUtils::format("%s Kernels", CashManager::getInstance()->convertAmountToShortString(cash).c_str()));
    
    if (cash > 999999999999999999) {
        m_ttfconf_score.fontSize = G_SWIDTH / 20;
        m_lbl_Score->setTTFConfig(m_ttfconf_score);
    }

    if (cash > 500000 && m_userdefault->getIntegerForKey("share_count") == 0) {
        m_userdefault->setBoolForKey("facebook", false);
        m_userdefault->setBoolForKey("twitter", false);
        m_userdefault->setIntegerForKey("share_count", 1);
    }
    else if (cash > 500000000 && m_userdefault->getIntegerForKey("share_count") == 1) {
        m_userdefault->setBoolForKey("facebook", false);
        m_userdefault->setBoolForKey("twitter", false);
        m_userdefault->setIntegerForKey("share_count", 2);
    }
    else  if (cash > 500000000000 && m_userdefault->getIntegerForKey("share_count") == 2) {
        m_userdefault->setBoolForKey("facebook", false);
        m_userdefault->setBoolForKey("twitter", false);
        m_userdefault->setIntegerForKey("share_count", 3);
    }
    else if (cash > 500000000000000 && m_userdefault->getIntegerForKey("share_count") == 3) {
        m_userdefault->setBoolForKey("facebook", false);
        m_userdefault->setBoolForKey("twitter", false);
        m_userdefault->setIntegerForKey("share_count", 4);
    }
    else if (cash > 500000000000000000 && m_userdefault->getIntegerForKey("share_count") == 4) {
        m_userdefault->setBoolForKey("facebook", false);
        m_userdefault->setBoolForKey("twitter", false);
        m_userdefault->setIntegerForKey("share_count", 5);
    }
}

void GameScene::addPerSecond(float dt){
    
    if (messageshown == true && idle == 0) {
        
        this->removeChild(m_lbl_Tutorial);
        messageshown = false;
    }
    
    bucketButton->setVisible(true);
    
    float cashpersec = CashManager::getInstance()->getCashPerSecond()+(CashManager::getInstance()->getCashPerSwap() * swapsCount);
    
    if (idle >= 1) {
        
        if (idleshown == false) {
            m_lbl_Tutorial=Label::createWithTTF(StringUtils::format("Tap The Box To Pop Popcorn!"), "AmericanTypewriter.ttf", G_SWIDTH / 20);
            m_lbl_Tutorial->setDimensions(digitSprite->getBoundingBox().size.width, digitSprite->getBoundingBox().size.height);
            m_lbl_Tutorial->setHorizontalAlignment(TextHAlignment::CENTER);
            m_lbl_Tutorial->setVerticalAlignment(TextVAlignment::CENTER);
            
            m_lbl_Tutorial->setColor(Color3B(255, 255, 255));
            
            m_lbl_Tutorial->setPosition(Vec2(G_SWIDTH / 2,G_SHEIGHT *2/ 3.2));
            this->addChild(m_lbl_Tutorial, 1001);
            messageshown = true;
            
        }
        
        idleshown = true;
        
        return;
        
    } else {
        
        m_lbl_MoneyPerSecond->setString(StringUtils::format("%s Kernels/Sec",CashManager::getInstance()->convertAmountToShortString(cashpersec).c_str()));
    }
    
    m_lbl_MoneyPerSecond->setString(StringUtils::format("%s Kernels/Sec", CashManager::getInstance()->convertAmountToShortString(cashpersec).c_str()));
    
    swapsCount=0;
    CashManager *cashmanager = CashManager::getInstance();
    float perswap = cashmanager->getCashPerSwap();
    m_lbl_MoneyPerSwap->setString(StringUtils::format("%s Kernels", cashmanager->convertAmountToShortString(perswap).c_str()));
    cashmanager->setCurrentCash(cashmanager->getCurrentCash() + cashmanager->getCashPerSecond());
    if (cashmanager->getCurrentBucket() < cashmanager->getBucketSize()) {
        cashmanager->setCurrentBucket(cashmanager->getCurrentBucket() +(cashmanager->getCashPerHour() / 3600));
    }
    else{
        cashmanager->setCurrentBucket(cashmanager->getBucketSize());
        if (cashmanager->getBucketSize() != 0 ){
            if (!cashmanager->getisBucketShown()){
                cashmanager->setisBucketShown(true);
                this->showBucket();
            }
        }
        else{
            bucketButton->setVisible(false);
        }
    }
}
void GameScene::showBucket(){
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
    BucketScene *bucketLayer = BucketScene::create();
    this->addChild(bucketLayer, 7000);
}

void GameScene::addCashPerSwap(){
    
    if (m_userdefault->getIntegerForKey("prestige_count") ==0) {
        if (m_userdefault->getBoolForKey("Forever20") == true) {
            swapsCount = 20;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  20 * CashManager::getInstance()->getCashPerSwap());
        }
        
        else {
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  CashManager::getInstance()->getCashPerSwap());
        }
    }
    
    if (m_userdefault->getIntegerForKey("prestige_count")>0) {
        
        
        
        if (m_userdefault->getBoolForKey("Forever20") == true) {
            int plus = m_userdefault->getIntegerForKey("prestige_count");
            swapsCount = 21 + plus;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  swapsCount * CashManager::getInstance()->getCashPerSwap());
        }
        
        else {
            int plus = m_userdefault->getIntegerForKey("prestige_count");
            swapsCount=1 + plus;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  swapsCount * CashManager::getInstance()->getCashPerSwap());
        }
        
    }
}

void GameScene::addSkwedSprite(){
    int r = CCRANDOM_0_1() * m_spt_Bucket->getBoundingBox().size.width * 0.9;
    int group_index = CCRANDOM_0_1() * 2 + 1;
    
    int popcorn_index = m_userdefault->getIntegerForKey("CustomPopcorn") + 1;
    string popcorn_filename = StringUtils::format("popcorn%d-%d.png", group_index, popcorn_index);
    if (group_index == 0 && m_int_RDMShaker >= 1800) {
        CashManager::getInstance()->setCurrentShaker(CashManager::getInstance()->getCurrentShaker() +1);
        Sprite *skewd = Sprite::create("clickshaker.png");
        skewd->setPosition(Vec2(m_spt_Bucket->getPositionX() - m_spt_Bucket->getBoundingBox().size.width / 2 + r + m_spt_Bucket->getBoundingBox().size.width * 0.05, G_SHEIGHT / 2));
        skewd->setAnchorPoint(Vec2(0.5, 0.25));
        skewd->setScale(G_SCALEM);
        this->addChild(skewd, 101);
        currentSkewed = skewd;
        skewdArray.pushBack(skewd);
        m_int_RDMShaker =0;
    }else
    {
        Sprite *skewd = Sprite::create(popcorn_filename);
        skewd->setPosition(Vec2(m_spt_Bucket->getPositionX() - m_spt_Bucket->getBoundingBox().size.width / 2 + r + m_spt_Bucket->getBoundingBox().size.width * 0.05, G_SHEIGHT / 2));
        skewd->setAnchorPoint(Vec2(0.5, 0.25));
        skewd->setScale(G_SCALEM);
        this->addChild(skewd, 101);
        currentSkewed = skewd;
        skewdArray.pushBack(skewd);
    }
}

void GameScene::addBonus(){
    m_b_KingBonus = false;
    CashManager *cashmanager = CashManager::getInstance();
    if (m_int_BonusNumber <= 30) {
        cashmanager->setCurrentCash( cashmanager->getCurrentCash() + .005 * cashmanager->getCurrentCash());
    }
    if (m_int_BonusNumber > 30 && m_int_BonusNumber <= 35) {
        cashmanager->setCurrentCash( cashmanager->getCurrentCash() + .01 * cashmanager->getCurrentCash());
    }
    if (m_int_BonusNumber > 35 && m_int_BonusNumber <= 40) {
        cashmanager->setCurrentCash( cashmanager->getCurrentCash() + .025 * cashmanager->getCurrentCash());
    }
    if (m_int_BonusNumber > 40 && m_int_BonusNumber <= 45) {
        cashmanager->setCurrentCash( cashmanager->getCurrentCash() + .05 * cashmanager->getCurrentCash());
    }
    if (m_int_BonusNumber > 45) {
        cashmanager->setCurrentCash( cashmanager->getCurrentCash() + .10 * cashmanager->getCurrentCash());
    }
}
void GameScene::bigPopcorn(){
    m_int_BonusNumber = CCRANDOM_0_1() * 50;
    
    m_spt_GoldenKernel = Sprite::create("goldKernel.png");
    m_spt_GoldenKernel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
    m_spt_GoldenKernel->setScale(G_SCALEM);
    if (m_int_BonusNumber <= 30) {
        m_spt_BigPopcorn = Sprite::create("bigpopcorn_0.5.png");
        
    }
    if (m_int_BonusNumber > 30 && m_int_BonusNumber <= 35) {
        m_spt_BigPopcorn = Sprite::create("bigpopcorn_1.0.png");
    }
    if (m_int_BonusNumber > 35 && m_int_BonusNumber <= 40) {
        m_spt_BigPopcorn = Sprite::create("bigpopcorn_2.5.png");
    }
    if (m_int_BonusNumber > 40 && m_int_BonusNumber <= 45) {
        m_spt_BigPopcorn = Sprite::create("bigpopcorn_5.0.png");
        
    }
    if (m_int_BonusNumber > 45) {
        m_spt_BigPopcorn = Sprite::create("bigpopcorn_10.0.png");
    }
    
    m_spt_BigPopcorn->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
    m_spt_BigPopcorn->setLocalZOrder(3000);
    
    ScaleTo *hugescale=ScaleTo::create(1.5, 30);
    m_spt_BigPopcorn->setOpacity(255.0);
    FadeTo *fadeOut = FadeTo::create(1.5, 64);
    this->addChild(m_spt_GoldenKernel, 3000);
    
    ScaleBy *scale = ScaleBy::create(0.5, 0.8);
    ScaleBy *scale_r = scale->reverse();
    
    Sequence *scale_rep = Sequence::create(scale, DelayTime::create(0.05), scale_r, NULL);
    Repeat *rep = Repeat::create(scale_rep, 3);
    m_spt_GoldenKernel->runAction(Sequence::create(rep, RemoveSelf::create(), NULL));
    
    this->addChild(m_spt_BigPopcorn);
    m_spt_BigPopcorn->setVisible(false);
    m_spt_BigPopcorn->runAction(Sequence::create(DelayTime::create(3.0f),
                                                 CallFunc::create([&]{m_spt_BigPopcorn->setVisible(true);}),
                                                 Spawn::create(hugescale, fadeOut, NULL),
                                                 RemoveSelf::create(),
                                                 NULL));
    
    this->runAction(Sequence::create(DelayTime::create(6.0f), CallFunc::create(CC_CALLBACK_0(GameScene::addBonus, this)), NULL));
}


void GameScene::topMove(){
    moveR=MoveTo::create(600, Vec2(G_SWIDTH, topClickbar->getPositionY()));
    moveL=MoveTo::create(20, Vec2(0, topClickbar->getPositionY()));
    
    Sequence *loop = Sequence::create(moveR,
//                                      DelayTime::create(600),
                                      CallFunc::create(CC_CALLBACK_0(GameScene::multiplier, this)),
                                      moveL,
//                                      DelayTime::create(20),
                                      CallFunc::create(CC_CALLBACK_0(GameScene::removeMultiplier, this)),
                                      NULL);
    RepeatForever *repeat = RepeatForever::create(loop);
    topClickbar->runAction(repeat);
}
void GameScene::removeMultiplier(){
    m_bool_Lmoving = false;
    this->removeChild(m_lbl_MultiplierLabel);
}

void GameScene::multiplier(){
    idle++;
    SimpleAudioEngine::getInstance()->playEffect("jingleSound.mp3");
    m_bool_Lmoving = true;
    m_int_RandomMultiplier = CCRANDOM_0_1() * 50;
    
    if (m_int_RandomMultiplier <= 30) {
        m_lbl_MultiplierLabel = Label::createWithTTF("X10", "AmericanTypewriter.ttf", G_SWIDTH / 5);
    }
    if (m_int_RandomMultiplier > 30 && m_int_RandomMultiplier <= 38 ){
        m_lbl_MultiplierLabel = Label::createWithTTF("X15", "AmericanTypewriter.ttf", G_SWIDTH / 5);
    }
    if (m_int_RandomMultiplier > 38 && m_int_RandomMultiplier <= 46) {
        m_lbl_MultiplierLabel = Label::createWithTTF("X20", "AmericanTypewriter.ttf", G_SWIDTH / 5);
    }
    if (m_int_RandomMultiplier > 46) {
        m_lbl_MultiplierLabel = Label::createWithTTF("X30", "AmericanTypewriter.ttf", G_SWIDTH / 5);
    }
    
    m_lbl_MultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
    m_lbl_MultiplierLabel->setColor(Color3B(1, 50, 20));
    
    this->addChild(m_lbl_MultiplierLabel, 3000);
    
}
void GameScene::multiplyValue(){
    if (m_int_RandomMultiplier <= 30) {
        swapsCount+=10;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  10*CashManager::getInstance()->getCashPerSwap());
    }
    if (m_int_RandomMultiplier > 30 && m_int_RandomMultiplier <= 38 ) {
        swapsCount+=15;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  15*CashManager::getInstance()->getCashPerSwap());
    }
    if (m_int_RandomMultiplier > 38 && m_int_RandomMultiplier <= 46) {
        swapsCount+=20;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  20*CashManager::getInstance()->getCashPerSwap());
    }
    
    if (m_int_RandomMultiplier > 46) {
        swapsCount+=30;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  30*CashManager::getInstance()->getCashPerSwap());
    }
}
void GameScene::tick(float dt)
{
    
    if (m_bool_Lmoving == false) {
        
        if (doublethirty == true) {
            doublethirtytime ++;
            
            if (doublethirtytime >= 6) {
                
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = false;
                doublethirty = false;
                doublethirtytime = 0;
                
            } else {
                
                
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = true;
                threex = false;
                fivex = false;
                twentyx = false;
                m_lbl_ClickMultiplierLabel = Label::createWithTTF("X2", "AmericanTypewriter.ttf", G_SWIDTH / 5);
                m_lbl_ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
                m_lbl_ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(m_lbl_ClickMultiplierLabel, 2500);
                
            }
        }
        if (twentyten == true) {
            twentytentime ++;
            
            if (twentytentime >= 3) {
                
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = false;
                twentyten = false;
                twentytentime = 0;
                
            } else {
                
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = true;
                m_lbl_ClickMultiplierLabel = Label::createWithTTF("X20", "AmericanTypewriter.ttf", G_SWIDTH / 5);
                m_lbl_ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
                m_lbl_ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(m_lbl_ClickMultiplierLabel, 2500);
                
            }
        }else
        {
            if (m_int_ClickMultiplier <= 47 && doublethirty == false && twentyten == false) {
                
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = false;
                m_int_ClickMultiplier=0;
            }
            if (m_int_ClickMultiplier > 47 && m_int_ClickMultiplier <= 52 && doublethirty == false && twentyten == false) {
                m_int_ClickMultiplier=0;
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = true;
                threex = false;
                fivex = false;
                twentyx = false;
                m_lbl_ClickMultiplierLabel = Label::createWithTTF("X2", "AmericanTypewriter.ttf", G_SWIDTH / 5);
                m_lbl_ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
                m_lbl_ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(m_lbl_ClickMultiplierLabel, 2500);
                
                
            }
            if (m_int_ClickMultiplier >52 && m_int_ClickMultiplier <= 56 && doublethirty == false && twentyten == false) {
                m_int_ClickMultiplier=0;
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = false;
                threex = true;
                fivex = false;
                twentyx = false;
                m_lbl_ClickMultiplierLabel = Label::createWithTTF("X3", "AmericanTypewriter.ttf", G_SWIDTH / 5);
                m_lbl_ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
                m_lbl_ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(m_lbl_ClickMultiplierLabel, 2500);
                
                
            }
            if (m_int_ClickMultiplier >56 && doublethirty == false && twentyten == false) {
                m_int_ClickMultiplier=0;
                this->removeChild(m_lbl_ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = true;
                twentyx = false;
                m_lbl_ClickMultiplierLabel = Label::createWithTTF("X5", "AmericanTypewriter.ttf", G_SWIDTH / 5);
                m_lbl_ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
                m_lbl_ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(m_lbl_ClickMultiplierLabel, 2500);
                
            }
        }
    }
}


void GameScene::animateSkewdSprite(){
    int popcornFallNumb = CCRANDOM_0_1() * 3;
    
    if (m_userdefault->getBoolForKey("KingKernel") == true) {
        ScaleTo *bigscalback = ScaleTo::create(1.5, 1 * G_SCALEM);
        m_spt_Bucket->runAction(bigscalback);
    } else {
        ScaleTo *bigscalback = ScaleTo::create(0.05, 1 * G_SCALEM);
        ScaleBy *scalto = ScaleBy::create(0.5, 0.85);
        currentSkewed->runAction(scalto);
        m_spt_Bucket->runAction(bigscalback);
    }
    
    MoveTo *moveto=MoveTo::create(2.50, Vec2(currentSkewed->getPositionX(), G_SHEIGHT+300));
    Sequence *seq = Sequence::create(moveto, RemoveSelf::create(), NULL);
    currentSkewed->runAction(seq);
    
    skewdArray.eraseObject(currentSkewed);
    
    currentSkewed = NULL;
    
    SimpleAudioEngine::getInstance()->playEffect(StringUtils::format("popcornSound%d.mp3", popcornFallNumb % 2 + 1 ).c_str());
    Sprite *sprite = Sprite::create(StringUtils::format("flat popcorn%d.png", popcornFallNumb + 1).c_str());
    sprite->setOpacity(196);
    sprite->setScale(G_SCALEM);
    int number=G_SWIDTH;
    sprite->setPosition(Vec2(arc4random() % number + 10, G_SHEIGHT));
    this->addChild(sprite, 1);
    Spawn *action = Spawn::create(MoveTo::create(3, Vec2(sprite->getPositionX(), 0)),
                                  RotateBy::create(3, arc4random() % 720),
                                  NULL);
    Sequence *se=Sequence::create(action, RemoveSelf::create(), NULL);
    sprite->runAction(se);
}
void GameScene::setBackground(float dt){
    if (m_userdefault->getBoolForKey("NewCustomBG") == false) {
        return;
    } else{
        
        int backgroundID = m_userdefault->getIntegerForKey("CustomBG", 0);
        
        this->removeChild(background1);
        this->removeChild(background2);
        
        switch (backgroundID) {
            case 0:
                background1 = Sprite::create("bluebackground.png");
                background2 = Sprite::create("bluebackground.png");
                break;
            case 1:
                background1 = Sprite::create("ocean.png");
                background2 = Sprite::create("oceanBack.png");
                break;
            case 2:
                background1 = Sprite::create("city.png");
                background2 = Sprite::create("city.png");
                break;
            case 3:
                background1 = Sprite::create("sky.png");
                background2 = Sprite::create("skyBack.png");
                break;
            case 4:
                background1 = Sprite::create("universe.png");
                background2 = Sprite::create("universe.png");
                break;
            case 5:
                background1 = Sprite::create("jungle.png") ;
                background2 = Sprite::create("jungleBack.png");
                break;
            case 6:
                background1 = Sprite::create("desert.png");
                background2 = Sprite::create("desertBack.png");
                break;
            case 7:
                background1 = Sprite::create("beach.png");
                background2 = Sprite::create("beachBack.png");
                break;
            default:
                background1 = Sprite::create("bluebackground.png");
                background2 = Sprite::create("bluebackground.png");
                break;
        }
        
        background1->setScale(G_SCALEM);
        background2->setScale(G_SCALEM);
        background1->setAnchorPoint(Vec2(0, 0));
        background2->setAnchorPoint(Vec2(0, 0));
        background1->setPosition(Vec2(0, 0));
        background2->setPosition(Vec2(background1->getBoundingBox().size.width -1, 0));
        
        //add them to main layer
        this->addChild(background1);
        this->addChild(background2);
        if (m_userdefault->getBoolForKey("Treadmill") == true) {
            this->unschedule(schedule_selector(GameScene::scroll));
            
        }else {
            this->schedule(schedule_selector(GameScene::scroll), 0.005f);
        }
        m_userdefault->setBoolForKey("NewCustomBG", false);
    }    
}

void GameScene::unlockables(float dt){
    
    
    if (m_userdefault->getBoolForKey("facebook") == true && facebook == true) {
        
        CashManager::getInstance()->setCurrentCash(1.15 * CashManager::getInstance()->getCurrentCash());
        facebook = false;
        
    }
    if (m_userdefault->getBoolForKey("twitter") == true && twitter == true) {
        
        CashManager::getInstance()->setCurrentCash(1.15 * CashManager::getInstance()->getCurrentCash());
        twitter = false;
        
    }
    
    
    if (m_userdefault->getBoolForKey("classicbox") == true) {
        
        if (classicbox == false) {
            return;
        } else {
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("flatpopcornbox.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            classicbox = false;
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
            
        }
        
    } else if (m_userdefault->getBoolForKey("chefhat") == true) {
        
        if (chefhat == false) {
            
            
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("hat.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            chefhat = false;
            classicbox = true;
            
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
            
        }
        
    } else if (m_userdefault->getBoolForKey("Upiggbank") == true) {
        
        
        if (piggybank == false) {
            return;
        } else {
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("goldpiggy_bank.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH/1.8, G_SHEIGHT / 2));
            
            piggybank = false;
            classicbox = true;
            
            chefhat = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
            
        }
        
    } else if (m_userdefault->getBoolForKey("moon") == true) {
        
        if (moon == false) {
            
            
            return;
        } else {
            
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("moon.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2.5));
            
            moon = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("earth") == true) {
        
        if (earth == false) {
            
            
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("earth.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            earth = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
            
        }
        
    } else if (m_userdefault->getBoolForKey("spaceship") == true) {
        
        if (spaceship == false) {
            return;
        } else {
            
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("popcorn_spaceship.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2.5));
            
            spaceship = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("ufo") == true) {
        
        if (ufo == false) {
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("popcorn_ufo.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            ufo = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("dinnerplate") == true) {
        
        if (dinnerplate == false) {
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("tray.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            dinnerplate = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            trophy = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("trophycup") == true) {
        
        if (trophy == false) {
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            
            m_spt_Bucket->setTexture("popcorntrophy.png");
            
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            trophy = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            car = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("car") == true) {
        
        if (car == false) {
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("car.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            car = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            umbrella = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("umbrella") == true) {
        
        if (umbrella == false) {
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 4));
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("umbrella.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/1.75));
            
            umbrella = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            diamond = true;
            ribbonshown = true;
            kingkernel = true;
        }
        
    } else if (m_userdefault->getBoolForKey("diamond") == true) {
        
        if (diamond == false) {
            return;
        } else {
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("diamond.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            diamond = false;
            classicbox = true;
            
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            ribbonshown = true;
            kingkernel = true;
            
        }
        
    }else if (m_userdefault->getBoolForKey("KingKernel") == true) {
        
        if (kingkernel == false) {
            return;
        } else {
            
            
            m_spt_Cover->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            m_lbl_MoneyPerSwap->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width / 10, m_spt_Cover->getPositionY()));
            m_spt_Bucket->setTexture("King Kernel.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 2));
            
            kingkernel = false;
            classicbox = true;
            diamond = true;
            chefhat = true;
            piggybank = true;
            moon = true;
            earth = true;
            spaceship = true;
            ufo = true;
            dinnerplate = true;
            trophy = true;
            car = true;
            umbrella = true;
            ribbonshown = true;
            
        }
        
    }
    
    if (m_userdefault->getBoolForKey("Forever20") == true) {
        
        if (m_b_TwentyReward == false) {
            return;
        } else
            this->removeChild(m_spt_ForeverTwenty);
        
        m_spt_ForeverTwenty = Sprite::create("20x.png");
        m_spt_ForeverTwenty->setPosition(Vec2(m_spt_Cover->getPositionX() - m_spt_Cover->getBoundingBox().size.width * 0.5, m_spt_Cover->getPositionY()));
        m_spt_ForeverTwenty->setScale( 0.4 * G_SCALEM);
        m_spt_ForeverTwenty->setAnchorPoint(Vec2(0.4, 0.4));
        this->addChild(m_spt_ForeverTwenty, 1000);
    }
    
    
    
    if (m_userdefault->getIntegerForKey("prestige_count") ==1) {
        
        
        if (m_userdefault->getBoolForKey("RibbonShown") == false) {
            return;
        } else {
            
            int prestigenumber = m_userdefault->getIntegerForKey("prestige_count");
            
            m_spt_PrestigeRibbon = Sprite::create("prestige ribbon.png");
            m_spt_PrestigeRibbon->setPosition(Vec2(G_SWIDTH * 11 / 12, G_SHEIGHT/7));
            m_spt_Bucket->setTexture("flatpopcornbox.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            m_ttfconf_score.fontSize = G_SWIDTH / 15;
            m_lbl_Score->setTTFConfig(m_ttfconf_score);
            this->addChild(m_spt_PrestigeRibbon, 5000);
            m_lbl_Prestige = Label::createWithTTF(StringUtils::format("%.0d",prestigenumber), "AmericanTypewriter.ttf", G_SWIDTH / 25);
            m_lbl_Prestige->setPosition(Vec2(m_spt_PrestigeRibbon->getPositionX(), m_spt_PrestigeRibbon->getPositionY() + 8));
            this->addChild(m_lbl_Prestige, 5001);
            
            m_userdefault->setBoolForKey("RibbonShown", false);
        }
    }
    
    
    else {
        if (m_userdefault->getBoolForKey("RibbonShown") == false) {
            return;
        } else {
            
            int prestigenumber = m_userdefault->getIntegerForKey("prestige_count");
            
            this->removeChild(m_lbl_Prestige);
            m_spt_PrestigeRibbon = Sprite::create("prestige ribbon.png");
            m_spt_PrestigeRibbon->setPosition(Vec2(G_SWIDTH*11/12, G_SHEIGHT/7));
            m_spt_Bucket->setTexture("flatpopcornbox.png");
            m_spt_Bucket->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT / 3));
            
            m_ttfconf_score.fontSize = G_SWIDTH / 15;
            m_lbl_Score->setTTFConfig(m_ttfconf_score);
            
            this->addChild(m_spt_PrestigeRibbon, 5000);
            m_lbl_Prestige = Label::createWithTTF(StringUtils::format("%.0d",prestigenumber), "AmericanTypewriter.ttf", G_SWIDTH / 25);
            m_lbl_Prestige->setPosition(Vec2(m_spt_PrestigeRibbon->getPositionX(), m_spt_PrestigeRibbon->getPositionY() + 8));
            this->addChild(m_lbl_Prestige, 5001);
            
            m_userdefault->setBoolForKey("RibbonShown", false);
        }
        
        
    }
}

void GameScene::addVideoBonus() {
    
    SimpleAudioEngine::getInstance()->playEffect("jingleSound.mp3");
    if (m_int_VideoBonusNumb == 0) {
        CashManager::getInstance()->setCurrentCash(1.1 * CashManager::getInstance()->getCurrentCash());
    }
    if (m_int_VideoBonusNumb == 1) {
        CashManager::getInstance()->setCurrentCash(1.1 * CashManager::getInstance()->getCurrentCash());
    }
    if (m_int_VideoBonusNumb == 2) {
        CashManager::getInstance()->setCurrentCash(1.2 * CashManager::getInstance()->getCurrentCash());
    }
}

void GameScene::panForTranslation(Point translation){
    if (currentSkewed) {
        Point newPos = currentSkewed->getPosition() + translation;
        currentSkewed->setPosition(Vec2(currentSkewed->getPositionX(), newPos.y));
    }
}

void GameScene::onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent) {
    Point touchLocation=touches[0]->getLocation();
    startPoint=touchLocation;
    // Create it
    log("Click = %i", m_int_ClickMultiplier);
    
    if (m_spt_Bucket->getBoundingBox().containsPoint(touchLocation)) {
        
        if (barwidth == 1000) {
            
            int currentCash = (int)CashManager::getInstance()->getCurrentCash();
            int cashPerSecond = (int)CashManager::getInstance()->getCashPerSecond();
            int cashPerSwap = (int)CashManager::getInstance()->getCashPerSwap();
            int prestige = UserDefault::getInstance()->getIntegerForKey("prestige_count");
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
            
#else
            JniMethodInfo t;
            if (JniHelper::getStaticMethodInfo(t
                                              ,  "org/cocos2dx/cpp/AppActivity"
                                              ,  "reportScore"
                                              ,  "(IF)V"))
            {
                t.env->CallStaticVoidMethod(t.classID, t.methodID, 1, currentCash);
                t.env->CallStaticVoidMethod(t.classID, t.methodID, 2, cashPerSecond);
                t.env->CallStaticVoidMethod(t.classID, t.methodID, 3, cashPerSwap);
                t.env->CallStaticVoidMethod(t.classID, t.methodID, 4, prestige);
            }
#endif
            review++;
            log("= %i", review);
            SimpleAudioEngine::getInstance()->playEffect("jingleSound.mp3");
            barwidth = 0;
            this->bigPopcorn();
        }
        if (m_userdefault->getBoolForKey("Treadmill") == true) {
            this->move();
        }
        idle = 0;
        idleshown = false;
        
        if (messageshown == true) {
            
            this->removeChild(m_lbl_Tutorial);
            messageshown = false;
        }
        
        m_int_RDMShaker++;
        
        barwidth++;
        
        bottomClickbar->setPosition(Vec2(barwidth * G_SWIDTH / 1000, perSecondRibbon->getPositionY() - perSecondRibbon->getBoundingBox().size.height / 2 - 20 * G_SCALEM));
        
        this->addSkwedSprite();
        
        if (m_spt_Bucket->getScale() > 4 * G_SCALEM) {
            this->bigPopcorn();
            ScaleTo *bigscalback = ScaleTo::create(0.01, G_SCALEM);
            m_spt_Bucket->runAction(bigscalback);
            m_b_KingBonus = true;
        } else if (m_userdefault->getBoolForKey("KingKernel") == true) {
            if (m_b_KingBonus == false) {
                ScaleBy *bigscalto = ScaleBy::create(0.05, 1.03);
                m_spt_Bucket->runAction(bigscalto);
            }
        }
        else {
            ScaleTo *bigscalto=ScaleTo::create(0.05, 0.95 * G_SCALEM);
            m_spt_Bucket->runAction(bigscalto);
        }
        if (m_bool_Lmoving == true) {
            m_int_ClickMultiplier = 0;
            this->removeChild(m_lbl_ClickMultiplierLabel);
            this->multiplyValue();
        }
        m_int_ClickMultiplier++;
        
        if (twox == true) {
            swapsCount++;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  2*CashManager::getInstance()->getCashPerSwap());
        }
        if (threex == true) {
            swapsCount += 2;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  2*CashManager::getInstance()->getCashPerSwap());
        }
        if (fivex == true) {
            swapsCount += 5;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  5*CashManager::getInstance()->getCashPerSwap());
        }
        if (twentyx == true) {
            swapsCount += 20;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  20*CashManager::getInstance()->getCashPerSwap());
        }
    }
}

void GameScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    
    Point touchLocation = touches[0]->getLocation();
    for (Sprite *sprite : skewdArray) {
        if (sprite->getNumberOfRunningActions() == 0) {
            videoClicks++;
            swapsCount++;
            this->addCashPerSwap();
            this->animateSkewdSprite();
        }
        currentSkewed = NULL;
    }
    
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent) {
    Point touchLocation = touches[0]->getLocation();
    endPoint=touchLocation;
    
    if (endPoint.y-startPoint.y>100) {
        if (currentSkewed) {
            swapsCount++;
            this->addCashPerSwap();
            this->animateSkewdSprite();
        }
    }
    
    Point oldTouchLocation = touches[0]->getPreviousLocation();
    
    Point translation = touchLocation - oldTouchLocation;
    this->panForTranslation(translation);
}