//
//  VideoScene.cpp
//  Popcorn
//
//  Created by Monkey on 7/28/16.
//
//

#include "VideoScene.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "PluginChartboost/PluginChartboost.h"
#include "GameScene.hpp"

using namespace sdkbox;

Scene* VideoScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = VideoScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool VideoScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Sprite *spt_bgBucket = Sprite::create("bucktbg.png");
    spt_bgBucket->setPosition(G_SWIDTH / 2, G_SHEIGHT / 2);
    spt_bgBucket->setScale(G_SWIDTH / 1024 , G_SHEIGHT / 1024);
    this->addChild(spt_bgBucket);
    
    Sprite *bg_title = Sprite::create("PerSecondLabel.png");
    bg_title->setScale(G_SCALEM * 0.9);
    bg_title->setPosition(G_SWIDTH / 2, G_SHEIGHT * 6 / 7);
    this->addChild(bg_title);
    
    Label *lbl_title = Label::createWithTTF(T_VIDEO_TITLE, "AmericanTypewriter.ttf", G_SWIDTH / 15);
    lbl_title->setPosition(bg_title->getPosition());
    lbl_title->setAlignment(TextHAlignment::CENTER);
    lbl_title->setWidth(bg_title->getBoundingBox().size.width * 0.9);
    this->addChild(lbl_title);
    
    MenuItemImage *btn_tv = MenuItemImage::create("tvPlay.png",
                                                  "tvPlay.png",
                                                  CC_CALLBACK_1(VideoScene::video, this));
    btn_tv->setPosition(G_SWIDTH / 2, G_SHEIGHT / 2);
    
    
    MenuItemImage* btn_close = MenuItemImage::create("cross.png",
                                                     "cross.png",
                                                     [&](Ref *sender)
                                                     {
                                                         SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                         log("Video -- Close Button Clicked");
                                                         Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
                                                         
                                                         if (dynamic_cast<GameScene*>(this->getParent())) {
                                                             GameScene* gamescene = (GameScene*)this->getParent();
                                                             gamescene->setButtonEnable(true);
                                                         }
                                                         
                                                         this->removeFromParent();
                                                     });
    btn_close->setPosition(G_SWIDTH * 0.9, G_SHEIGHT * 0.95);
    btn_close->setScale(G_SCALEM * 1.5);
    
    Menu *menu = Menu::create(btn_tv, btn_close, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    lbl_desc = Label::createWithTTF("", "AmericanTypewriter.ttf", G_SWIDTH / 10);
    lbl_desc->setPosition(G_SWIDTH / 2, bg_title->getPositionY() - bg_title->getBoundingBox().size.height / 2 - 20 * G_SCALEM);
    lbl_desc->setAnchorPoint(Vec2(0.5f, 1.0f));
    lbl_desc->setWidth(G_SWIDTH * 0.9);
    lbl_desc->setAlignment(TextHAlignment::CENTER);
    this->addChild(lbl_desc);
    
    if (UserDefault::getInstance()->getBoolForKey("ABC")) {
        UserDefault::getInstance()->setBoolForKey("ABC", false);
        bonus = CCRANDOM_0_1() * 50;
        UserDefault::getInstance()->setIntegerForKey("VBonus", bonus);
    }
    
    this->schedule(schedule_selector(VideoScene::checkVideo), 0.1);
    
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") <= 5) {
        
        // Do any additional setup after loading the view from its nib.
        double cash= CashManager::getInstance()->getCurrentCash();
        
        lbl_desc->setString(StringUtils::format("Get %s Kernels Instantly", CashManager::getInstance()->ConvertAmountToShortString(cash*.15).c_str()));
        
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 5 && UserDefault::getInstance()->getIntegerForKey("VBonus") <=28) {
        
        
        //percent boost for kernels per second
        
        lbl_desc->setString("Get 2 Shakers Instantly");
        
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 28 && UserDefault::getInstance()->getIntegerForKey("VBonus") <= 35) {
        
        //percent boost for kernels per second
        
        lbl_desc->setString("Earn a Golden Kernel");
        
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 35 && UserDefault::getInstance()->getIntegerForKey("VBonus") <=42) {
               
        //percent boost for kernels per second
        
        lbl_desc->setString("Get 2x Kernels/Click for 30 Seconds");
        
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 42 && UserDefault::getInstance()->getIntegerForKey("VBonus") <= 50) {
                
        //percent boost for kernels per second
        
        lbl_desc->setString("Get 20x Kernels/Click for 10 Seconds");
        
    }
    
    return true;
}

void VideoScene::video(cocos2d::Ref *sender)
{
    log("Video Button Clicked");
    
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") <= 5) {
        UserDefault::getInstance()->setBoolForKey("KBVideo", true);
        SimpleAudioEngine::getInstance()->playEffect("click.mp3");
        PluginChartboost::show("Rewarded Video");
    }
    
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 5 && UserDefault::getInstance()->getIntegerForKey("VBonus") <=28) {
        UserDefault::getInstance()->setBoolForKey("ShakerBonus", true);
        SimpleAudioEngine::getInstance()->playEffect("click.mp3");
        PluginChartboost::show("Rewarded Video");
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 28 && UserDefault::getInstance()->getIntegerForKey("VBonus") <= 35) {
        UserDefault::getInstance()->setBoolForKey("GoldBonus", true);
        SimpleAudioEngine::getInstance()->playEffect("click.mp3");
        PluginChartboost::show("Rewarded Video");
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 35 && UserDefault::getInstance()->getIntegerForKey("VBonus") <=42) {
        UserDefault::getInstance()->setBoolForKey("2xBonus", true);
        SimpleAudioEngine::getInstance()->playEffect("click.mp3");
        PluginChartboost::show("Rewarded Video");
    }
    if (UserDefault::getInstance()->getIntegerForKey("VBonus") > 42 && UserDefault::getInstance()->getIntegerForKey("VBonus") <= 50) {
        UserDefault::getInstance()->setBoolForKey("20xBonus", true);
        SimpleAudioEngine::getInstance()->playEffect("click.mp3");
        PluginChartboost::show("Rewarded Video");
    }
}

void VideoScene::checkVideo(float dt)
{
    if (UserDefault::getInstance()->getBoolForKey("Video")) {
        this->removeFromParent();
    }
}