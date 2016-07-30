//
//  GameScene.cpp
//  Popcorn
//
//  Created by Monkey on 7/27/16.
//
//

#include "GameScene.hpp"
#include "CashManager.hpp"
#include "Constants.h"

#include "InvestmentLayer.hpp"
#include "BusinessLayer.hpp"
#include "PoliticalLayer.hpp"

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
    userdefault = UserDefault::getInstance();
    
    int backgroundID = userdefault->getIntegerForKey("CustomBG", 0);
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
            background1 = Sprite::create("jugle.png") ;
            background2 = Sprite::create("jugleBack.png");
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
    
    if (userdefault->getBoolForKey("Treadmill", false) == false) {
        this->schedule(schedule_selector(GameScene::scroll), 0.005f);
    }
    
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
    TwentyReward = true;
    kingkernel = true;
    
    bottomClickbar = Sprite::create("BottomClick_Bar.png");
    bottomClickbar->setPosition(Vec2(0, 0));
    bottomClickbar->setAnchorPoint(Vec2(1.0 ,1.0));
    bottomClickbar->setScale(G_SCALEM);
    this->addChild(bottomClickbar ,2000);
    
    topClickbar = Sprite::create("TopClick_Bar.png");
    topClickbar->setPosition(Vec2(0, G_SHEIGHT));
    topClickbar->setAnchorPoint(Vec2(1.0, 1.0));
    topClickbar->setScale(G_SCALEM);
    this->addChild(topClickbar ,2000);
    this->topMove();
    
    bgSprite=Sprite::create("flatpopcornbox.png");
    bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
    bgSprite->setAnchorPoint(Vec2(0.5, 0.5));
    bgSprite->setScale(G_SCALEM);
    this->addChild(bgSprite ,100);
    
    digitSprite=Sprite::create("score_label.png");
    digitSprite->setScale(G_SCALEM);
    digitSprite->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT - topClickbar->getBoundingBox().size.height - digitSprite->getBoundingBox().size.height / 2 - 20 * G_SCALEM));
    this->addChild(digitSprite ,1001);
    
    perSecondRibbon=Sprite::create("PerSecondLabel.png");
    perSecondRibbon->setScale(G_SCALEM);
    perSecondRibbon->setPosition(Vec2(G_SWIDTH/2, digitSprite->getPositionY() - digitSprite->getBoundingBox().size.height - 20 * G_SCALEM));
    this->addChild(perSecondRibbon ,999);
    
    scoreLabel=Label::createWithTTF(StringUtils::format("%.0f Kernels",CashManager::getInstance()->getCurrentCash()),"AmericanTypewriter.ttf" ,G_SWIDTH/15);
    scoreLabel->setDimensions(digitSprite->getBoundingBox().size.width, digitSprite->getBoundingBox().size.height);
    scoreLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    scoreLabel->setVerticalAlignment(TextVAlignment::CENTER);
    scoreLabel->setColor(Color3B(1, 50, 20));
    scoreLabel->setPosition(Vec2(digitSprite->getPositionX(),digitSprite->getPositionY()));
    this->addChild(scoreLabel ,1001);
    
    MenuItemImage *investButton = MenuItemImage::create("button1.png",
                                                        "button1.png",
                                                        [&](Ref *sender)
                                                        {
                                                            log("Invest Button Clicked");
                                                            // Cache ChartboostReward Video.
                                                            adCount++;
                                                            if (adCount >= 12 && !userdefault->getBoolForKey("RemoveAds", false)) {
                                                                // show Ads.
                                                                adCount = 0;
                                                            }
                                                            SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                            
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
                                                              adCount++;
                                                              if (adCount >= 12 && !userdefault->getBoolForKey("RemoveAds", false)) {
                                                                  // show Ads.
                                                                  adCount = 0;
                                                              }
                                                              SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                              
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
                                                               adCount++;
                                                               if (adCount >= 12 && !userdefault->getBoolForKey("RemoveAds", false)) {
                                                                   // show Ads.
                                                                   adCount = 0;
                                                               }
                                                               SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
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
                                                           adCount++;
                                                           if (adCount >= 12 && !userdefault->getBoolForKey("RemoveAds", false)) {
                                                               // show Ads.
                                                               adCount = 0;
                                                           }
                                                           SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                           // Show InAppViewController
                                                       });
    
    MenuItemImage *popcornButton = MenuItemImage::create("new bag.png",
                                                         "new bag.png",
                                                         [&](Ref *sendder)
                                                         {
                                                             log("Popcorn Button Clicked");
                                                             // Cache RewardVideo
                                                             adCount++;
                                                             if (adCount >= 8 && !userdefault->getBoolForKey("RemoveAds", false)) {
                                                                 // show Chartboost Interstitial
                                                                 adCount = 0;
                                                             }
                                                             SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                             // Show Popcorn viewcontroller
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
                                                            // [Chartboost cacheRewardedVideo:CBLocationHomeScreen);
                                                            // Show Ads View
                                                            this->ShowBucket();
                                                            log("Bucket Button Clicked");
                                         });
    bucketButton->setPosition(Vec2(G_SWIDTH / 25, G_SHEIGHT / 10));
    bucketButton->setAnchorPoint(Vec2(0.0f, 0.0f));
    bucketButton->setVisible(false);
    bucketButton->setScale(G_SCALEM);
    
    gamecenterButton = MenuItemImage::create("leaderboard.png",
                                             "leaderboard.png",
                                             [&](Ref *sender){
                                                                // Cach Chartboost Reward Video
                                                                SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                                // Game Center Login
                                                                // Show Leaderboard
                                                                // SubmitScore
                                                                log("GameCenter Button Clicked");
                                             });
    gamecenterButton->setPosition(Vec2(G_SWIDTH / 12, perSecondRibbon->getPositionY() - perSecondRibbon->getContentSize().height / 2 - G_SHEIGHT / 10));
    gamecenterButton->setScale(0.15f * G_SCALEM);
    
    reviewbutton = MenuItemImage::create("whitestar.png",
                                         "whitestar.png",
                                         [&](Ref *sender){
                                                                // Cache RewardVideo
                                                                SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                                // Show ReviewViewController
                                                                log("Review Button Clicked");
                                         });
    reviewbutton->setPosition(Vec2(G_SWIDTH * 11 / 12, perSecondRibbon->getPositionY() - perSecondRibbon->getContentSize().height / 2 - G_SHEIGHT / 10));
    reviewbutton->setVisible(false);
    reviewbutton->setScale(0.1f * G_SCALEM);
    
    videobutton = MenuItemImage::create("tvPlayCrop.png",
                                        "tvPlayCrop.png",
                                        [&](Ref *sender){
                                                            SimpleAudioEngine::getInstance()->playEffect("Click.mp3");
                                                            // Show Video ViewController
                                                            userdefault->setBoolForKey("RDMNUMB", true);
                                                            log("Video Button Clicked");
                                        });
    videobutton->setPosition(Vec2(G_SWIDTH / 12, gamecenterButton->getPositionY() - gamecenterButton->getContentSize().height / 2 - G_SHEIGHT / 25));
    videobutton->setVisible(false);
    videobutton->setScale(0.15f * G_SCALEM);
    
    Menu *btnmenu = Menu::create(investButton, businessButton, politicalButton, inappButton, popcornButton, bucketButton, gamecenterButton, videobutton, reviewbutton, NULL);
    btnmenu->setPosition(Vec2(0, 0));
    this->addChild(btnmenu, 1100);
        
    Sprite *belowBorder=Sprite::create("bar.png");
    belowBorder->setAnchorPoint(Vec2(0, 0));
    belowBorder->setPosition(Vec2(0, 0));
    belowBorder->setScale(1.2f * G_SCALEM);
    this->addChild(belowBorder ,1000);
    
    coverSprite=Sprite::create("flat ribbon.png");
    coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
    coverSprite->setScale(G_SCALEM);
    this->addChild(coverSprite ,1000);
    
    MoneyPerSwapLabel=Label::createWithTTF(StringUtils::format("%.0f Kernels",CashManager::getInstance()->getCashPerSwap()) ,"AmericanTypewriter.ttf" ,G_SWIDTH/15);
    MoneyPerSwapLabel->setColor(Color3B(1, 50, 20));
    MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
    MoneyPerSwapLabel->setDimensions(coverSprite->getBoundingBox().size.width, coverSprite->getBoundingBox().size.height);
    MoneyPerSwapLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    MoneyPerSwapLabel->setVerticalAlignment(TextVAlignment::CENTER);
    this->addChild(MoneyPerSwapLabel ,1000);
    
    MoneyPerSecondLabel=Label::createWithTTF(StringUtils::format("%.2f Kernels/Sec",CashManager::getInstance()->getCashPerSecond()) ,"AmericanTypewriter.ttf" ,G_SWIDTH/15);
    MoneyPerSecondLabel->setColor(Color3B(255, 255, 255));
    MoneyPerSecondLabel->setPosition(perSecondRibbon->getPosition());
    MoneyPerSecondLabel->setDimensions(perSecondRibbon->getBoundingBox().size.width, perSecondRibbon->getBoundingBox().size.height);
    MoneyPerSecondLabel->setHorizontalAlignment(TextHAlignment::CENTER);
    MoneyPerSecondLabel->setVerticalAlignment(TextVAlignment::CENTER);
    this->addChild(MoneyPerSecondLabel ,1000);
    
    swapsCount=0;
    
    this->schedule(schedule_selector(GameScene::AddPerSecond), 1.0f);
    this->schedule(schedule_selector(GameScene::RollDollar), 0.2f);
    this->schedule(schedule_selector(GameScene::PersecondLabel), 0.1f);
    this->CheckUnlockables();
    
    this->schedule(schedule_selector(::GameScene::Unlockables), 0.5f);
    this->schedule(schedule_selector(GameScene::Background), 0.5f);
    this->schedule(schedule_selector(GameScene::CheckVideo), 5.0f);
    this->schedule(schedule_selector(GameScene::CheckPlayedVideo), 1.0f);
    this->schedule(schedule_selector(GameScene::CheckReward), 1.0f);
    
    return true;
}

void GameScene::scroll(float dt) {
    if (UserDefault::getInstance()->getIntegerForKey("CustomBG") > 0) {
        
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
    if (UserDefault::getInstance()->getIntegerForKey("CustomBG") > 0) {
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

void GameScene::CheckPrestige(){
    if (UserDefault::getInstance()->getIntegerForKey("prestige_count")) {
        PrestigeRibbon=Sprite::create("prestige ribbon");
        PrestigeRibbon->setPosition(Vec2(G_SWIDTH - G_SWIDTH/25, G_SHEIGHT/8));
        this->addChild(PrestigeRibbon);
    }
}

void GameScene::CheckPlayedVideo(float dt){
    if (UserDefault::getInstance()->getBoolForKey("Video") == true) {
        videobutton->setVisible(false);
        UserDefault::getInstance()->setBoolForKey("Video", false);
    }
}
void GameScene::CheckReward(float dt){
    if (UserDefault::getInstance()->getBoolForKey("ShowReview") == true) {
        UserDefault::getInstance()->setIntegerForKey("reviewPopup", 1);
        UserDefault::getInstance()->setBoolForKey("ShowReview", false);
//        ReviewViewController *Obj=[[ReviewViewController alloc] initWithNibName:@"ReviewViewController" bundle:NULL);
//        
//        if (UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPad){
//            Obj=[[IpadReviewViewController alloc] initWithNibName:@"IpadReviewViewController" bundle:NULL);
//            
//        }
//        [[[CCDirector sharedDirector] openGLView] insertSubview:Obj.view atIndex:0);
        
    }
    
    if (UserDefault::getInstance()->getBoolForKey("CollectDBL") == true) {
        UserDefault::getInstance()->setBoolForKey("CollectDBL", false);
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() + CashManager::getInstance()->getCurrentBucket() *  2);
        CashManager::getInstance()->setCurrentBucket(0);
        CashManager::getInstance()->setisBucketShown(false);
    }
    
    if (UserDefault::getInstance()->getBoolForKey("20XVideo") == true) {
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() * 1.1f);
        UserDefault::getInstance()->setBoolForKey("20XVideo", false);
    }
    if (UserDefault::getInstance()->getBoolForKey("PlayedShaker") == true) {
        CashManager::getInstance()->setCurrentShaker(CashManager::getInstance()->getCurrentShaker() + 2);
        UserDefault::getInstance()->setBoolForKey("PlayedShaker", false);
    }
    if (UserDefault::getInstance()->getBoolForKey("PlayedGold") == true) {
        this->BigPopcorn();
        UserDefault::getInstance()->setBoolForKey("PlayedGold", false);
    }
    if (UserDefault::getInstance()->getBoolForKey("Played2x") == true) {
        doublethirty = true;
        UserDefault::getInstance()->setBoolForKey("Played2x", false);
    }
    if (UserDefault::getInstance()->getBoolForKey("Played20x") == true) {
        twentyten = true;
        UserDefault::getInstance()->setBoolForKey("Played20x", false);
    }
}

void GameScene::CheckVideo(float dt){
    
    if( true /*![Chartboost hasRewardedVideo:CBLocationHomeScreen]*/) {
        videobutton->setVisible(false);
//        [Chartboost cacheRewardedVideo:CBLocationHomeScreen);
    } else
        
        if (Lmoving == false) {
            if (videoClicks >800) {
                
                
                if(true/*[Chartboost hasRewardedVideo:CBLocationHomeScreen]*/) {
                    
                    LoadedVideo ++;
                    
                    if (UserDefault::getInstance()->getBoolForKey("DEF") == false) {
                        UserDefault::getInstance()->setBoolForKey("ABC", true);
                        UserDefault::getInstance()->setBoolForKey("DEF", true);
                    }
                    if (LoadedVideo == 4) {
                        videoClicks = 0;
                        LoadedVideo = 0;
                        videobutton->setVisible(false);
                        UserDefault::getInstance()->setBoolForKey("DEF", false);
                    } else {
                        videobutton->setVisible(true);
                    }
                }
                else {
                    videobutton->setVisible(false);
//                    [Chartboost cacheRewardedVideo:CBLocationHomeScreen);                    
                }
            }
        }
        if (Review >= 5){
            Review = 0;
            reviewbutton->setVisible(true);
        }
}
void GameScene::CheckUnlockables(){
    
    if (UserDefault::getInstance()->getBoolForKey("classicbox") == true) {
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("flatpopcornbox.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        this->addChild(bgSprite ,100);
        classicbox = false;
    }  else if (UserDefault::getInstance()->getBoolForKey("chefhat") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("hat.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        chefhat = false;
    }
    else if (UserDefault::getInstance()->getBoolForKey("Upiggbank") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("goldpiggy_bank.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/1.8, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        piggybank = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("moon") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("moon.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2.5));
        this->addChild(bgSprite ,100);
        moon = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("earth") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("earth.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        earth = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("spaceship") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("popcornspaceship.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2.5));
        this->addChild(bgSprite ,100);
        spaceship = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("ufo") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("popcorn_ufo.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        ufo = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("dinnerplate") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("tray.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        dinnerplate = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("trophycup") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("popcorntrophy.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        trophy = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("car") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("car.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        car = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("umbrella") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("umbrella.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/1.75));
        this->addChild(bgSprite ,100);
        umbrella = false;
        
    } else if (UserDefault::getInstance()->getBoolForKey("diamond") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("diamond.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        this->addChild(bgSprite ,100);
        diamond = false;
        
    }
    else if (UserDefault::getInstance()->getBoolForKey("KingKernel") == true){
        this->removeChild(bgSprite);
        coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
        MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
        bgSprite=Sprite::create("King Kernel.png");
        bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
        this->addChild(bgSprite ,100);
        kingkernel = false;
        
    }
    if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
        ForeverTwenty = Sprite::create("20x.png");
        ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY()));
        ForeverTwenty->setScaleX(0.4);
        ForeverTwenty->setScaleY(0.4);
        ForeverTwenty->setAnchorPoint(Vec2(1.2, 0.2));
        this->addChild(ForeverTwenty ,1000);
    }
    
    if (UserDefault::getInstance()->getIntegerForKey("prestige_count") > 0) {
        int prestigenumber = UserDefault::getInstance()->getIntegerForKey("prestige_count");
        PrestigeRibbon=Sprite::create("prestige ribbon.png");
        PrestigeRibbon->setPosition(Vec2(G_SWIDTH*11/12, G_SHEIGHT/7));
        this->addChild(PrestigeRibbon ,5000);
        prestigeLabel = Label::createWithTTF(StringUtils::format("%.0d",prestigenumber) ,"AmericanTypewriter.ttf" ,G_SWIDTH/25);
        prestigeLabel->setPosition(Vec2(PrestigeRibbon->getPositionX(), PrestigeRibbon->getPositionY() + 8));
        this->addChild(prestigeLabel ,5001);
    }
}
void GameScene::RollDollar(float dt){
    
    if (CashManager::getInstance()->getCashPerSecond() == 0) {
        return;
    }
    Sprite *sprite=Sprite::create("flat popcorn.png");
    sprite->setOpacity(255);
    
    int number=G_SWIDTH;
    sprite->setPosition(Vec2(arc4random()%number+10, G_SHEIGHT));
    this->addChild(sprite ,0);
    MoveTo *moveto=MoveTo::create(1, Vec2(sprite->getPositionX(), 0));
    RotateBy *rot=RotateBy::create(1, arc4random()%180);
    Sequence *seq=Sequence::create(moveto,RemoveSelf::create(), NULL);
    sprite->runAction(seq);
    sprite->runAction(rot);
}
void GameScene::PersecondLabel(float dt){
    
    double cash = CashManager::getInstance()->getCurrentCash();
    scoreLabel->setString(StringUtils::format("%s Kernels", CashManager::getInstance()->ConvertAmountToShortString(cash).c_str()));
    
    if (cash>999999999999999999) {
       scoreLabel->setSystemFontSize(G_SWIDTH/25);
    }
    
//    log("Kernels %f", cash);
    if (cash > 500000 && UserDefault::getInstance()->getIntegerForKey("share_count") == 0) {
        UserDefault::getInstance()->setBoolForKey("facebook", false);
        UserDefault::getInstance()->setBoolForKey("twitter", false);
        UserDefault::getInstance()->setIntegerForKey("share_count", 1);
    }
    else if (cash > 500000000 && UserDefault::getInstance()->getIntegerForKey("share_count") == 1) {
        UserDefault::getInstance()->setBoolForKey("facebook", false);
        UserDefault::getInstance()->setBoolForKey("twitter", false);
        UserDefault::getInstance()->setIntegerForKey("share_count", 2);
    }
    else  if (cash > 500000000000 && UserDefault::getInstance()->getIntegerForKey("share_count") == 2) {
        UserDefault::getInstance()->setBoolForKey("facebook", false);
        UserDefault::getInstance()->setBoolForKey("twitter", false);
        UserDefault::getInstance()->setIntegerForKey("share_count", 3);
    }
    else if (cash > 500000000000000 && UserDefault::getInstance()->getIntegerForKey("share_count") == 3) {
        UserDefault::getInstance()->setBoolForKey("facebook", false);
        UserDefault::getInstance()->setBoolForKey("twitter", false);
        UserDefault::getInstance()->setIntegerForKey("share_count", 4);
    }
    else if (cash > 500000000000000000 && UserDefault::getInstance()->getIntegerForKey("share_count") == 4) {
        UserDefault::getInstance()->setBoolForKey("facebook", false);
        UserDefault::getInstance()->setBoolForKey("twitter", false);
        UserDefault::getInstance()->setIntegerForKey("share_count", 5);
    }
}

void GameScene::AddPerSecond(float dt){
    
    
    if (messageshown == true && idle == 0) {
        
        this->removeChild(TutorialLabel);
        messageshown = false;
    }
    
    bucketButton->setVisible(true);
    float cashpersec=CashManager::getInstance()->getCashPerSecond()+(CashManager::getInstance()->getCashPerSwap() * swapsCount);
    
    if (idle >= 1) {
        
        if (idleshown == false) {
            TutorialLabel=Label::createWithTTF(StringUtils::format("Tap The Box To Pop Popcorn!") ,"AmericanTypewriter.ttf" ,G_SWIDTH/20);
            TutorialLabel->setDimensions(digitSprite->getBoundingBox().size.width, digitSprite->getBoundingBox().size.height);
            TutorialLabel->setHorizontalAlignment(TextHAlignment::CENTER);
            TutorialLabel->setVerticalAlignment(TextVAlignment::CENTER);
            
            TutorialLabel->setColor(Color3B(255, 255, 255));
            
            TutorialLabel->setPosition(Vec2(G_SWIDTH / 2,G_SHEIGHT *2/ 3.2));
            this->addChild(TutorialLabel ,1001);
            messageshown = true;
            
        }
        
        idleshown = true;
        
        return;
        
    } else {
        
        MoneyPerSecondLabel->setString(StringUtils::format("%s Kernels/Sec",CashManager::getInstance()->ConvertAmountToShortString(cashpersec).c_str()));
    }
    
    MoneyPerSecondLabel->setString(StringUtils::format("%s Kernels/Sec", CashManager::getInstance()->ConvertAmountToShortString(cashpersec).c_str()));
    
    swapsCount=0;
    float perswap=CashManager::getInstance()->getCashPerSwap();
    MoneyPerSecondLabel->setString(StringUtils::format("%s Kernels",CashManager::getInstance()->ConvertAmountToShortString(perswap).c_str()));
    CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() + CashManager::getInstance()->getCashPerSecond());
    if (CashManager::getInstance()->getCurrentBucket() < CashManager::getInstance()->getBucketSize()) {
        CashManager::getInstance()->setCurrentBucket(CashManager::getInstance()->getCurrentBucket() +(CashManager::getInstance()->getCashPerHour() / 3600));
    }
    else{
        
        CashManager::getInstance()->setCurrentBucket(CashManager::getInstance()->getBucketSize());
        if (CashManager::getInstance()->getBucketSize()!=0 ){
            if (!CashManager::getInstance()->getisBucketShown()){
                CashManager::getInstance()->setisBucketShown(true);
                this->ShowBucket();
            }
        }
        else{
            
            bucketButton->setVisible(false);
        }
    }
    
}
void GameScene::ShowBucket(){
    
//    BucketViewController *Obj=[[BucketViewController alloc] initWithNibName:@"BucketViewController" bundle:NULL);
//    if (UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPad){
//        Obj=[[BucketViewController alloc] initWithNibName:@"BucketViewController~ipad" bundle:NULL);
//        
//    }
//    [[[CCDirector sharedDirector] openGLView] insertSubview:Obj.view atIndex:0);
}

void GameScene::AddCashPerSwap(){
    
    if (UserDefault::getInstance()->getIntegerForKey("prestige_count") ==0) {
        if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
            swapsCount = 20;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  20*CashManager::getInstance()->getCashPerSwap());
        }
        
        else {
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  CashManager::getInstance()->getCashPerSwap());
        }
    }
    
    if (UserDefault::getInstance()->getIntegerForKey("prestige_count")>0) {
        
        
        
        if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
            int plus=UserDefault::getInstance()->getIntegerForKey("prestige_count");
            swapsCount=21 + plus;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  swapsCount*CashManager::getInstance()->getCashPerSwap());
        }
        
        else {
            int plus=UserDefault::getInstance()->getIntegerForKey("prestige_count");
            swapsCount=1 + plus;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  swapsCount*CashManager::getInstance()->getCashPerSwap());
        }
        
    }
}

void GameScene::AddSkwedSprite(){
    int r = CCRANDOM_0_1() * 200;
    int popcornNumb = CCRANDOM_0_1() * 2;
    if (popcornNumb == 0) {
        if (RDMShaker >= 1800) {
            CashManager::getInstance()->setCurrentShaker(CashManager::getInstance()->getCurrentShaker() +1);
            Sprite *skewd=Sprite::create("clickshaker.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
            RDMShaker =0;
        }else {
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 0) {
                Sprite *skewd=Sprite::create("flat popcorn1.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
                
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 1) {
                Sprite *skewd=Sprite::create("moustache-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 2) {
                Sprite *skewd=Sprite::create("cornglasses-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 3) {
                Sprite *skewd=Sprite::create("lineglasses-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 4) {
                Sprite *skewd=Sprite::create("aviators-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 5) {
                Sprite *skewd=Sprite::create("cornstache-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 6) {
                Sprite *skewd=Sprite::create("linestache-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 7) {
                Sprite *skewd=Sprite::create("avistache-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 8) {
                
                
                Sprite *skewd=Sprite::create("chefhat-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 9) {
                
                
                Sprite *skewd=Sprite::create("chefhatstache-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 10) {
                
                
                Sprite *skewd=Sprite::create("chefcorn-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 11) {
                
                
                Sprite *skewd=Sprite::create("chefline-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 12) {
                
                
                Sprite *skewd=Sprite::create("chefavi-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 13) {
                
                
                Sprite *skewd=Sprite::create("chefcs-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 14) {
                
                
                Sprite *skewd=Sprite::create("chefla-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 15) {
                
                
                Sprite *skewd=Sprite::create("chefsa-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 16) {
                
                
                Sprite *skewd=Sprite::create("tophat-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 17) {
                
                
                Sprite *skewd=Sprite::create("tophatstache-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 18) {
                
                
                Sprite *skewd=Sprite::create("cornhat-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 19) {
                
                
                Sprite *skewd=Sprite::create("linedhat-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 20) {
                
                
                Sprite *skewd=Sprite::create("avihat-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 21) {
                
                
                Sprite *skewd=Sprite::create("csm-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 22) {
                
                
                Sprite *skewd=Sprite::create("linesm-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 23) {
                
                
                Sprite *skewd=Sprite::create("asm-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 24) {
                
                
                Sprite *skewd=Sprite::create("disguise-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 25) {
                
                
                Sprite *skewd=Sprite::create("chefdisguise-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 26) {
                
                
                Sprite *skewd=Sprite::create("tophatdisguise-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 27) {
                
                
                Sprite *skewd=Sprite::create("hsm-popcorn.png");
                skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
                skewd->setAnchorPoint(Vec2(0.5, 0.25));
                this->addChild(skewd ,101);
                currentSkewed=skewd;
                skewdArray.pushBack(skewd);
            }
            
        }
        
    }
    
    if (popcornNumb == 1) {
        
        
        
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 0) {
            
            
            Sprite *skewd=Sprite::create("flat popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 1) {
            
            
            Sprite *skewd=Sprite::create("moustache-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 2) {
            
            
            Sprite *skewd=Sprite::create("cornglasses-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 3) {
            
            
            Sprite *skewd=Sprite::create("lineglasses-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 4) {
            
            
            Sprite *skewd=Sprite::create("aviators-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 5) {
            
            
            Sprite *skewd=Sprite::create("cornstache-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 6) {
            
            
            Sprite *skewd=Sprite::create("linestache-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 7) {
            
            
            Sprite *skewd=Sprite::create("avistache-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 8) {
            
            
            Sprite *skewd=Sprite::create("chefhat-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 9) {
            
            
            Sprite *skewd=Sprite::create("chefhatstache-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 10) {
            
            
            Sprite *skewd=Sprite::create("chefcorn-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 11) {
            
            
            Sprite *skewd=Sprite::create("chefline-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 12) {
            
            
            Sprite *skewd=Sprite::create("chefavi-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 13) {
            
            
            Sprite *skewd=Sprite::create("chefcs-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 14) {
            
            
            Sprite *skewd=Sprite::create("chefla-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 15) {
            
            
            Sprite *skewd=Sprite::create("chefsa-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 16) {
            
            
            Sprite *skewd=Sprite::create("tophat-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 17) {
            
            
            Sprite *skewd=Sprite::create("tophatstache-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 18) {
            
            
            Sprite *skewd=Sprite::create("cornhat-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 19) {
            
            
            Sprite *skewd=Sprite::create("linedhat-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 20) {
            
            
            Sprite *skewd=Sprite::create("avihat-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 21) {
            
            
            Sprite *skewd=Sprite::create("csm-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 22) {
            
            
            Sprite *skewd=Sprite::create("linesm-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 23) {
            
            
            Sprite *skewd=Sprite::create("asm-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 24) {
            
            
            Sprite *skewd=Sprite::create("disguise-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 25) {
            
            
            Sprite *skewd=Sprite::create("chefdisguise-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 26) {
            
            
            Sprite *skewd=Sprite::create("tophatdisguise-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 27) {
            
            
            Sprite *skewd=Sprite::create("hsm-popcorn2.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
    }
    
    if (popcornNumb == 2) {
        
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 0) {
            
            
            Sprite *skewd=Sprite::create("flat popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 1) {
            
            
            Sprite *skewd=Sprite::create("moustache-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 2) {
            
            
            Sprite *skewd=Sprite::create("cornglasses-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 3) {
            
            
            Sprite *skewd=Sprite::create("lineglasses-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 4) {
            
            
            Sprite *skewd=Sprite::create("aviators-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 5) {
            
            
            Sprite *skewd=Sprite::create("cornstache-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 6) {
            
            
            Sprite *skewd=Sprite::create("linestache-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 7) {
            
            
            Sprite *skewd=Sprite::create("avistache-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 8) {
            
            
            Sprite *skewd=Sprite::create("chefhat-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 9) {
            
            
            Sprite *skewd=Sprite::create("chefhatstache-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 10) {
            
            
            Sprite *skewd=Sprite::create("chefcorn-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 11) {
            
            
            Sprite *skewd=Sprite::create("chefline-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 12) {
            
            
            Sprite *skewd=Sprite::create("chefavi-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 13) {
            
            
            Sprite *skewd=Sprite::create("chefcs-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 14) {
            
            
            Sprite *skewd=Sprite::create("chefla-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 15) {
            
            
            Sprite *skewd=Sprite::create("chefsa-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 16) {
            
            
            Sprite *skewd=Sprite::create("tophat-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 17) {
            
            
            Sprite *skewd=Sprite::create("tophatstache-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 18) {
            
            
            Sprite *skewd=Sprite::create("cornhat-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 19) {
            
            
            Sprite *skewd=Sprite::create("linedhat-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 20) {
            
            
            Sprite *skewd=Sprite::create("avihat-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 21) {
            
            
            Sprite *skewd=Sprite::create("csm-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 22) {
            
            
            Sprite *skewd=Sprite::create("linesm-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 23) {
            
            
            Sprite *skewd=Sprite::create("asm-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 24) {
            
            
            Sprite *skewd=Sprite::create("disguise-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 25) {
            
            
            Sprite *skewd=Sprite::create("chefdisguise-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 26) {
            
            
            Sprite *skewd=Sprite::create("tophatdisguise-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        if (UserDefault::getInstance()->getIntegerForKey("CustomPopcorn") == 27) {
            
            
            Sprite *skewd=Sprite::create("hsm-popcorn3.png");
            skewd->setPosition(Vec2(G_SWIDTH/4 + r,G_SHEIGHT/2));
            skewd->setAnchorPoint(Vec2(0.5, 0.25));
            this->addChild(skewd ,101);
            currentSkewed=skewd;
            skewdArray.pushBack(skewd);
        }
        
    }
}

void GameScene::AddBonus(){
    KingBonus = false;
    if (BonusNumber <= 30) {
        CashManager::getInstance()->setCurrentCash( CashManager::getInstance()->getCurrentCash() + .005*CashManager::getInstance()->getCurrentCash());
    }
    if (BonusNumber > 30 && BonusNumber <= 35) {
        CashManager::getInstance()->setCurrentCash( CashManager::getInstance()->getCurrentCash() + .01*CashManager::getInstance()->getCurrentCash());
    }
    if (BonusNumber > 35 && BonusNumber <= 40) {
        CashManager::getInstance()->setCurrentCash( CashManager::getInstance()->getCurrentCash() + .025*CashManager::getInstance()->getCurrentCash());
    }
    if (BonusNumber > 40 && BonusNumber <= 45) {
        CashManager::getInstance()->setCurrentCash( CashManager::getInstance()->getCurrentCash() + .05*CashManager::getInstance()->getCurrentCash());
    }
    if (BonusNumber > 45) {
        CashManager::getInstance()->setCurrentCash( CashManager::getInstance()->getCurrentCash() + .10*CashManager::getInstance()->getCurrentCash());
    }
}
void GameScene::BigPopcorn(){
    BonusNumber = CCRANDOM_0_1() * 50;
    
    GoldenKernel = Sprite::create("goldKernel.png");
    GoldenKernel->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT / 2));
    if (BonusNumber <= 30) {
        m_BigPopcorn = Sprite::create("bigpopcorn.5%.png");
        
    }
    if (BonusNumber > 30 && BonusNumber <= 35) {
        m_BigPopcorn = Sprite::create("bigpopcorn1%.png");
    }
    if (BonusNumber > 35 && BonusNumber <= 40) {
        m_BigPopcorn = Sprite::create("bigpopcorn1.png");
    }
    if (BonusNumber > 40 && BonusNumber <= 45) {
        m_BigPopcorn = Sprite::create("bigpopcorn2.png");
        
    }
    if (BonusNumber > 45) {
        m_BigPopcorn = Sprite::create("bigpopcorn3.png");
    }
    
    m_BigPopcorn->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT / 2));
    m_BigPopcorn->setLocalZOrder(3000);
    
    ScaleTo *hugescale=ScaleTo::create(1.5, 20);
    m_BigPopcorn->setOpacity(255.0);
    FadeTo *fadeOut = FadeTo::create(1.5 ,100);
    
    this->addChild(GoldenKernel ,3000);
    
    ScaleTo *scale1=ScaleTo::create(0.5 ,0.85);
    ScaleTo *scale2=ScaleTo::create(0.07 ,0.90);
    ScaleTo *scale3=ScaleTo::create(0.07 ,0.80);
    ScaleTo *scale4=ScaleTo::create(0.07 ,0.85);
    ScaleTo *scale5=ScaleTo::create(0.07 ,0.83);
    ScaleTo *scale6=ScaleTo::create(0.07 ,0.87);
    ScaleTo *scale7=ScaleTo::create(0.07 ,0.80);
    ScaleTo *scale8=ScaleTo::create(0.07 ,0.86);
    ScaleTo *scale9=ScaleTo::create(0.07 ,0.78);
    ScaleTo *scale10=ScaleTo::create(0.07 ,0.80);
    ScaleTo *scale11=ScaleTo::create(0.07 ,0.76);
    ScaleTo *scale12=ScaleTo::create(0.07 ,0.84);
    ScaleTo *scale13=ScaleTo::create(0.07 ,0.80);
    ScaleTo *scale14=ScaleTo::create(0.07 ,0.82);
    ScaleTo *scale15=ScaleTo::create(0.07 ,0.78);
    ScaleTo *scale16=ScaleTo::create(0.07 ,0.84);
    ScaleTo *scale17=ScaleTo::create(0.07 ,0.80);
    ScaleTo *scale18=ScaleTo::create(0.07 ,0.87);
    ScaleTo *scale19=ScaleTo::create(0.07 ,0.83);
    ScaleTo *scale20=ScaleTo::create(0.07 ,0.86);
    ScaleTo *scale21=ScaleTo::create(0.07 ,0.79);
    ScaleTo *scale22=ScaleTo::create(0.07 ,0.81);
    ScaleTo *scale23=ScaleTo::create(0.07 ,0.76);
    ScaleTo *scale24=ScaleTo::create(0.07 ,0.84);
    ScaleTo *scale25=ScaleTo::create(0.07 ,0.80);

    this->runAction(Sequence::create(CallFunc::create([&]{
                                                                GoldenKernel->runAction(Sequence::create(scale1, scale2, scale3, scale4, scale5, scale6, scale7, scale8, scale9, scale10, scale11, scale12, scale13, scale14, scale15, scale16, scale17, scale18, scale19, scale20, scale21, scale22, scale23, scale24, scale25, RemoveSelf::create(), NULL));
                                                           }),
                                     CallFunc::create([&]{
                                                                this->addChild(m_BigPopcorn);
                                                                m_BigPopcorn->runAction(Sequence::create(hugescale, fadeOut, DelayTime::create(1.5), RemoveSelf::create(), NULL));
                                                          }),
                                     DelayTime::create(0.05),
                                     CallFunc::create(CC_CALLBACK_0(GameScene::AddBonus, this)),
                                     NULL));
}


void GameScene::topMove(){
    moveR=MoveTo::create(600, Vec2(G_SWIDTH, topClickbar->getPositionY()));
    moveL=MoveTo::create(20, Vec2(0, topClickbar->getPositionY()));
    
    Sequence *loop = Sequence::create(moveR,
                                      DelayTime::create(600),
                                      CallFunc::create(CC_CALLBACK_0(GameScene::Multiplier, this)),
                                      moveL,
                                      DelayTime::create(20),
                                      CallFunc::create(CC_CALLBACK_0(GameScene::RemoveMultiplier, this)),
                                      NULL);
    RepeatForever *repeat = RepeatForever::create(loop);
    topClickbar->runAction(repeat);
}
void GameScene::RemoveMultiplier(){
    Lmoving = false;
    this->removeChild(MultiplierLabel);
}


void GameScene::Multiplier(){
    idle++;
    SimpleAudioEngine::getInstance()->playEffect("jingleSound.mp3");
    Lmoving = true;
    RandomMultiplier = CCRANDOM_0_1() * 50;
    
    if (RandomMultiplier <= 30) {
        MultiplierLabel = Label::createWithTTF("X10" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
    }
    if (RandomMultiplier > 30 && RandomMultiplier <= 38 ){
        MultiplierLabel = Label::createWithTTF("X15" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
    }
    if (RandomMultiplier > 38 && RandomMultiplier <= 46) {
        MultiplierLabel = Label::createWithTTF("X20" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
    }
    if (RandomMultiplier > 46) {
        MultiplierLabel = Label::createWithTTF("X30" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
    }
    
    MultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/2));
    MultiplierLabel->setColor(Color3B(1, 50, 20));
    
    this->addChild(MultiplierLabel ,3000);
    
}
void GameScene::MultiplyValue(){
    if (RandomMultiplier <= 30) {
        swapsCount+=10;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  10*CashManager::getInstance()->getCashPerSwap());
    }
    if (RandomMultiplier > 30 && RandomMultiplier <= 38 ) {
        swapsCount+=15;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  15*CashManager::getInstance()->getCashPerSwap());
    }
    if (RandomMultiplier > 38 && RandomMultiplier <= 46) {
        swapsCount+=20;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  20*CashManager::getInstance()->getCashPerSwap());
    }
    
    if (RandomMultiplier > 46) {
        swapsCount+=30;
        CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  30*CashManager::getInstance()->getCashPerSwap());
    }
    
    
}
void GameScene::tick(float dt)
{
    
    if (Lmoving == false) {
        
        if (doublethirty == true) {
            doublethirtytime ++;
            
            if (doublethirtytime >= 6) {
                
                this->removeChild(ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = false;
                doublethirty = false;
                doublethirtytime = 0;
                
            } else {
                
                
                this->removeChild(ClickMultiplierLabel);
                twox = true;
                threex = false;
                fivex = false;
                twentyx = false;
                ClickMultiplierLabel = Label::createWithTTF("X2" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
                ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/2));
                ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(ClickMultiplierLabel ,2500);
                
            }
        }
        if (twentyten == true) {
            twentytentime ++;
            
            if (twentytentime >= 3) {
                
                this->removeChild(ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = false;
                twentyten = false;
                twentytentime = 0;
                
            } else {
                
                this->removeChild(ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = true;
                ClickMultiplierLabel = Label::createWithTTF("X20" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
                ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/2));
                ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(ClickMultiplierLabel ,2500);
                
            }
        }
        
        else {
            
            
            if (ClickMultiplier <= 47 && doublethirty == false && twentyten == false) {
                
                this->removeChild(ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = false;
                twentyx = false;
                ClickMultiplier=0;
            }
            if (ClickMultiplier > 47 && ClickMultiplier <= 52 && doublethirty == false && twentyten == false) {
                ClickMultiplier=0;
                this->removeChild(ClickMultiplierLabel);
                twox = true;
                threex = false;
                fivex = false;
                twentyx = false;
                ClickMultiplierLabel = Label::createWithTTF("X2" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
                ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/2));
                ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(ClickMultiplierLabel ,2500);
                
                
            }
            if (ClickMultiplier >52 && ClickMultiplier <= 56 && doublethirty == false && twentyten == false) {
                ClickMultiplier=0;
                this->removeChild(ClickMultiplierLabel);
                twox = false;
                threex = true;
                fivex = false;
                twentyx = false;
                ClickMultiplierLabel = Label::createWithTTF("X3" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
                ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/2));
                ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(ClickMultiplierLabel ,2500);
                
                
            }
            if (ClickMultiplier >56 && doublethirty == false && twentyten == false) {
                ClickMultiplier=0;
                this->removeChild(ClickMultiplierLabel);
                twox = false;
                threex = false;
                fivex = true;
                twentyx = false;
                ClickMultiplierLabel = Label::createWithTTF("X5" ,"AmericanTypewriter.ttf" ,G_SWIDTH / 5);
                ClickMultiplierLabel->setPosition(Vec2(G_SWIDTH / 2, G_SHEIGHT/2));
                ClickMultiplierLabel->setColor(Color3B(1, 50, 20));
                this->addChild(ClickMultiplierLabel ,2500);
                
            }
        }
    }
}


void GameScene::AnimateSkewdSprite(){
    int popcornFallNumb = CCRANDOM_0_1() * 3;
    
    if (UserDefault::getInstance()->getBoolForKey("KingKernel") == true) {
        ScaleTo *bigscalback=ScaleTo::create(1.5 ,1 * G_SCALEM);
        bgSprite->runAction(bigscalback);
    } else {
        ScaleTo *bigscalback=ScaleTo::create(0.05 ,1 * G_SCALEM);
        ScaleTo *scalto=ScaleTo::create(0.5 ,0.85);
        currentSkewed->runAction(scalto);
        bgSprite->runAction(bigscalback);
    }
    
    MoveTo *moveto=MoveTo::create(2.50, Vec2(currentSkewed->getPositionX(), G_SHEIGHT+300));
    Sequence *seq = Sequence::create(moveto, RemoveSelf::create(), NULL);
    currentSkewed->runAction(seq);
    
    skewdArray.eraseObject(currentSkewed);
    
    currentSkewed=NULL;
    
    SimpleAudioEngine::getInstance()->playEffect(StringUtils::format("popcornSound%d.mp3", popcornFallNumb % 2 + 1 ).c_str());
    Sprite *sprite=Sprite::create(StringUtils::format("flat popcorn%d.png", popcornFallNumb + 1).c_str());
    sprite->setOpacity(255);
    int number=G_SWIDTH;
    sprite->setPosition(Vec2(arc4random() % number + 10, G_SHEIGHT));
    this->addChild(sprite ,1);
    MoveTo *movet=MoveTo::create(3, Vec2(sprite->getPositionX(), 0));
    RotateBy *rot=RotateBy::create(3, arc4random() % 720);
    Sequence *se=Sequence::create(movet, RemoveSelf::create(), NULL);
    sprite->runAction(se);
    sprite->runAction(rot);
}
void GameScene::Background(float dt){
    if (UserDefault::getInstance()->getBoolForKey("NewCustomBG") == false) {
        return;
    } else{
        
        int backgroundID = UserDefault::getInstance()->getIntegerForKey("CustomBG", 0);
        
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
                background1 = Sprite::create("jugle.png") ;
                background2 = Sprite::create("jugleBack.png");
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
        
        background1->setAnchorPoint(Vec2(0, 0));
        background2->setAnchorPoint(Vec2(0, 0));
        background1->setPosition(Vec2(0, 0));
        background2->setPosition(Vec2(background1->getBoundingBox().size.width -1, 0));
        
        //add them to main layer
        this->addChild(background1);
        this->addChild(background2);
        if (UserDefault::getInstance()->getBoolForKey("Treadmill") == true) {
            this->unschedule(schedule_selector(GameScene::scroll));
            
        }else {
            this->schedule(schedule_selector(GameScene::scroll), 0.005f);
        }
        UserDefault::getInstance()->setBoolForKey("NewCustomBG", false);
    }    
}

void GameScene::Unlockables(float dt){
    
    
    if (UserDefault::getInstance()->getBoolForKey("facebook") == true && facebook == true) {
        
        CashManager::getInstance()->setCurrentCash(1.15 * CashManager::getInstance()->getCurrentCash());
        facebook = false;
        
    }
    if (UserDefault::getInstance()->getBoolForKey("twitter") == true && twitter == true) {
        
        CashManager::getInstance()->setCurrentCash(1.15 * CashManager::getInstance()->getCurrentCash());
        twitter = false;
        
    }
    
    
    if (UserDefault::getInstance()->getBoolForKey("classicbox") == true) {
        
        if (classicbox == false) {
            
            
            return;
        } else {
            
            this->removeChild(bgSprite);
            
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            //            ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            
            bgSprite=Sprite::create("flatpopcornbox.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("chefhat") == true) {
        
        if (chefhat == false) {
            
            
            return;
        } else {
            
            
            
            this->removeChild(bgSprite);
            //   this->removeChild(ForeverTwenty);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            //          ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("hat.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("Upiggbank") == true) {
        
        
        if (piggybank == false) {
            
            
            return;
        } else {
            
            this->removeChild(bgSprite);
            //   coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            //            ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("goldpiggy_bank.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/1.8, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("moon") == true) {
        
        if (moon == false) {
            
            
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("moon.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2.5));
            this->addChild(bgSprite ,100);
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
            /*    if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
             this->removeChild(ForeverTwenty);
             
             ForeverTwenty = Sprite::create("20x.png");
             ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
             ForeverTwenty.scaleX = 0.4;
             ForeverTwenty.scaleY = 0.4;
             ForeverTwenty.opacity = 0.5;
             this->addChild(ForeverTwenty ,1000);
             
             }*/
        }
        
    } else if (UserDefault::getInstance()->getBoolForKey("earth") == true) {
        
        if (earth == false) {
            
            
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            //          ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
            bgSprite=Sprite::create("earth.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
            /*   if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
             this->removeChild(ForeverTwenty);
             
             ForeverTwenty = Sprite::create("20x.png");
             ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
             ForeverTwenty.scaleX = 0.4;
             ForeverTwenty.scaleY = 0.4;
             ForeverTwenty.opacity = 0.5;
             this->addChild(ForeverTwenty ,1000);
             
             }*/
        }
        
    } else if (UserDefault::getInstance()->getBoolForKey("spaceship") == true) {
        
        if (spaceship == false) {
            
            
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("popcornspaceship.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2.5));
            this->addChild(bgSprite ,100);
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
            /*   if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
             this->removeChild(ForeverTwenty);
             
             ForeverTwenty = Sprite::create("20x.png");
             ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
             ForeverTwenty.scaleX = 0.4;
             ForeverTwenty.scaleY = 0.4;
             ForeverTwenty.opacity = 0.5;
             this->addChild(ForeverTwenty ,1000);
             
             }*/
        }
        
    } else if (UserDefault::getInstance()->getBoolForKey("ufo") == true) {
        
        if (ufo == false) {
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            //          ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("popcorn_ufo.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
            //      this->addChild(ForeverTwenty);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("dinnerplate") == true) {
        
        if (dinnerplate == false) {
            
            
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            //         ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY());
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("tray.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("trophycup") == true) {
        
        if (trophy == false) {
            return;
        } else {
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            
            bgSprite=Sprite::create("popcorntrophy.png");
            
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("car") == true) {
        
        if (car == false) {
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("car.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("umbrella") == true) {
        
        if (umbrella == false) {
            return;
        } else {
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/4));
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("umbrella.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/1.75));
            this->addChild(bgSprite ,100);
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
        
    } else if (UserDefault::getInstance()->getBoolForKey("diamond") == true) {
        
        if (diamond == false) {
            return;
        } else {
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("diamond.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            this->addChild(bgSprite ,100);
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
        
    }
    
    else if (UserDefault::getInstance()->getBoolForKey("KingKernel") == true) {
        
        if (kingkernel == false) {
            return;
        } else {
            
            this->removeChild(bgSprite);
            coverSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            
            MoneyPerSwapLabel->setPosition(Vec2(coverSprite->getPositionX() - coverSprite->getBoundingBox().size.width/10, coverSprite->getPositionY()));
            bgSprite=Sprite::create("King Kernel.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/2));
            this->addChild(bgSprite ,100);
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
    
    if (UserDefault::getInstance()->getBoolForKey("Forever20") == true) {
        
        if (TwentyReward == false) {
            return;
        } else
            this->removeChild(ForeverTwenty);
        
        
        ForeverTwenty = Sprite::create("20x.png");
        ForeverTwenty->setPosition(Vec2(coverSprite->getPositionX(), coverSprite->getPositionY()));
        ForeverTwenty->setScaleX(0.4);
        ForeverTwenty->setScaleY(0.4);
        ForeverTwenty->setAnchorPoint(Vec2(1.2, 0.2));
        this->addChild(ForeverTwenty ,1000);
    }
    
    
    
    if (UserDefault::getInstance()->getIntegerForKey("prestige_count") ==1) {
        
        
        if (UserDefault::getInstance()->getBoolForKey("RibbonShown") == false) {
            
            
            return;
        } else {
            
            int prestigenumber = UserDefault::getInstance()->getIntegerForKey("prestige_count");
            this->removeChild(bgSprite);
            PrestigeRibbon=Sprite::create("prestige ribbon.png");
            PrestigeRibbon->setPosition(Vec2(G_SWIDTH * 11 / 12, G_SHEIGHT/7));
            bgSprite=Sprite::create("flatpopcornbox.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            
            scoreLabel->setSystemFontSize(G_SWIDTH / 15);
            this->addChild(PrestigeRibbon, 5000);
            prestigeLabel = Label::createWithTTF(StringUtils::format("%.0d",prestigenumber), "AmericanTypewriter.ttf" ,G_SWIDTH/25);
            prestigeLabel->setPosition(Vec2(PrestigeRibbon->getPositionX(), PrestigeRibbon->getPositionY() + 8));
            this->addChild(prestigeLabel ,5001);
            this->addChild(bgSprite ,100);
            UserDefault::getInstance()->setBoolForKey("RibbonShown", false);
        }
    }
    
    
    else {
        if (UserDefault::getInstance()->getBoolForKey("RibbonShown") == false) {
            
            
            return;
        } else {
            
            int prestigenumber = UserDefault::getInstance()->getIntegerForKey("prestige_count");
            this->removeChild(bgSprite);
            this->removeChild(prestigeLabel);
            PrestigeRibbon=Sprite::create("prestige ribbon.png");
            PrestigeRibbon->setPosition(Vec2(G_SWIDTH*11/12, G_SHEIGHT/7));
            bgSprite=Sprite::create("flatpopcornbox.png");
            bgSprite->setPosition(Vec2(G_SWIDTH/2, G_SHEIGHT/3));
            
            scoreLabel->setSystemFontSize(G_SWIDTH / 15);
            this->addChild(PrestigeRibbon ,5000);
            prestigeLabel = Label::createWithTTF(StringUtils::format("%.0d",prestigenumber) ,"AmericanTypewriter.ttf" ,G_SWIDTH/25);
            prestigeLabel->setPosition(Vec2(PrestigeRibbon->getPositionX(), PrestigeRibbon->getPositionY() + 8));
            this->addChild(prestigeLabel ,5001);
            this->addChild(bgSprite ,100);
            UserDefault::getInstance()->setBoolForKey("RibbonShown", false);
        }
        
        
    }
}

void GameScene::AddVideoBonus() {
    
    SimpleAudioEngine::getInstance()->playEffect("jingleSound.mp3");
    if (VideoBonusNumb == 0) {
        CashManager::getInstance()->setCurrentCash(1.1 * CashManager::getInstance()->getCurrentCash());
    }
    if (VideoBonusNumb == 1) {
        CashManager::getInstance()->setCurrentCash(1.1 * CashManager::getInstance()->getCurrentCash());
    }
    if (VideoBonusNumb == 2) {
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
    log("Click = %i", ClickMultiplier);
    
    if (bgSprite->getBoundingBox().containsPoint(touchLocation)) {
        
        if (barwidth == 1000) {
            
//            GameKitHelper *gkHelper = [GameKitHelper sharedGameKitHelper);
//            gkHelper.delegate = self;
//            [gkHelper submitScore:CashManager::getInstance().CurrentCash category:LeaderboardID);
//            [gkHelper submitScore:CashManager::getInstance().cashPerSecond category:LeaderboardID2);
//            [gkHelper submitScore:CashManager::getInstance().cashPerSwap category:LeaderboardID3);
//            [gkHelper submitScore:UserDefault::getInstance()->getIntegerForKey("prestige_count") category:LeaderboardID4);
            
            Review++;
            log("= %i",Review);
            SimpleAudioEngine::getInstance()->playEffect("jingleSound.mp3");
            barwidth=0;
            this->BigPopcorn();
        }
        if (UserDefault::getInstance()->getBoolForKey("Treadmill") == true) {
            
            this->move();
        }
        idle = 0;
        idleshown = false;
        
        if (messageshown == true) {
            
            this->removeChild(TutorialLabel);
            messageshown = false;
        }
        
        RDMShaker++;
        
        barwidth++;
        bottomClickbar->setPosition(Vec2(barwidth * G_SWIDTH / 1000, perSecondRibbon->getPositionY() - perSecondRibbon->getBoundingBox().size.height / 2 - 20 * G_SCALEM));
        
        this->AddSkwedSprite();
        
        if (bgSprite->getScale() > 4) {
            this->BigPopcorn();
            
            ScaleTo *bigscalback=ScaleTo::create(0.01 ,1);
            bgSprite->runAction(bigscalback);
            
            KingBonus = true;
        } else
            
            
            if (UserDefault::getInstance()->getBoolForKey("KingKernel") == true) {
                if (KingBonus == false) {
                    ScaleTo *bigscalto=ScaleTo::create(0.05, bgSprite->getScale() * 1.03 * G_SCALEM);
                    bgSprite->runAction(bigscalto);
                }
            }
            else {
                ScaleTo *bigscalto=ScaleTo::create(0.05 ,0.95 * bgSprite->getScale());
                bgSprite->runAction(bigscalto);
            }
        //break;
        
        if (Lmoving == true) {
            ClickMultiplier=0;
            this->removeChild(ClickMultiplierLabel);
            this->MultiplyValue();
        }
        ClickMultiplier++;
        
        if (twox == true) {
            swapsCount++;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  2*CashManager::getInstance()->getCashPerSwap());
        }
        if (threex == true) {
            swapsCount+=2;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  2*CashManager::getInstance()->getCashPerSwap());
        }
        if (fivex == true) {
            swapsCount +=5;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  5*CashManager::getInstance()->getCashPerSwap());
        }
        if (twentyx == true) {
            swapsCount +=20;
            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() +  20*CashManager::getInstance()->getCashPerSwap());
        }
    }
}

void GameScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    
    Point touchLocation = touches[0]->getLocation();
    for (Sprite *sprite : skewdArray) {
        if (sprite->numberOfRunningActions() == 0) {
            videoClicks++;
            swapsCount++;
            this->AddCashPerSwap();
            this->AnimateSkewdSprite();
        }
        currentSkewed=NULL;
    }
    
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent) {
    Point touchLocation = touches[0]->getLocation();
    endPoint=touchLocation;
    
    if (endPoint.y-startPoint.y>100) {
        if (currentSkewed) {
            
            swapsCount++;
            this->AddCashPerSwap();
            this->AnimateSkewdSprite();
        }
    }
    
    Point oldTouchLocation = touches[0]->getPreviousLocation();
    
    Point translation = touchLocation - oldTouchLocation;
    this->panForTranslation(translation);
}