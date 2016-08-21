//
//  BucketScene.cpp
//  Popcorn
//
//  Created by Monkey on 8/8/16.
//
//

#include "BucketScene.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "PoliticalLayer.hpp"
#include "PluginChartboost/PluginChartboost.h"
#include "GameScene.hpp"

using namespace sdkbox;

Scene* BucketScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BucketScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool BucketScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Sprite *spt_bgBucket = Sprite::create("bucktbg.png");
    spt_bgBucket->setPosition(G_SWIDTH / 2, G_SHEIGHT / 2);
    spt_bgBucket->setScale(G_SWIDTH / 1024 , G_SHEIGHT / 1024);
    this->addChild(spt_bgBucket);
    
    m_spt_bucket = Sprite::create();
    m_spt_bucket->setAnchorPoint(Vec2(0, 0));
    m_spt_bucket->setPosition(0, 0);
    m_spt_bucket->setScale(G_SWIDTH / 500);
    this->addChild(m_spt_bucket);
    
    Sprite *spt_hand = Sprite::create("newpopcornshaker.png");
    spt_hand->setAnchorPoint(Vec2(1.0f, 1.0));
    spt_hand->setPosition(G_SWIDTH, G_SHEIGHT * 0.9);
    spt_hand->setScale(G_SCALEM * 0.3);
    this->addChild(spt_hand);
    
    this->schedule(schedule_selector(BucketScene::checkVideo), 0.1);
    
    m_btn_double = MenuItemImage::create("PerSecondLabel.png",
                                         "PerSecondLabel.png",
                                         [&](Ref *sender){
                                             log("Double Button Clicked");
                                             SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                             // Show reward Video.
                                             PluginChartboost::show("Rewarded Video");
                                             UserDefault::getInstance()->setBoolForKey("DBLVide0", true);
                                         });
    m_btn_double->setPosition(G_SWIDTH / 2, G_SHEIGHT / 3);
    m_btn_double->setScale(G_SCALEM * 0.9, G_SCALEY * 1.2);
    
    MenuItemImage *btn_increase = MenuItemImage::create("btn_left.png",
                                                        "btn_left.png",
                                                        [&](Ref *sender){
                                                            log("Increase Button Clicked");
                                                            SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                            Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
                                                            this->setButtonEnable(false);
                                                            PoliticalLayer *layer = PoliticalLayer::create();
                                                            layer->setContentSize(Size(G_SWIDTH, G_SHEIGHT * 0.75));
                                                            layer->showContent();
                                                            this->addChild(layer, 100);
                                                        });
    btn_increase->setScale(G_SCALEM * 0.8, G_SCALEY * 1.1);
    btn_increase->setAnchorPoint(Vec2(1.0f, 1.0f));
    btn_increase->setPosition(G_SWIDTH / 2 - 5 * G_SCALEM, m_btn_double->getPositionY() - m_btn_double->getBoundingBox().size.height / 2 - 10 * G_SCALEM);
    
    MenuItemImage *btn_collect = MenuItemImage::create("btn_right.png",
                                                       "btn_right.png",
                                                       [&](Ref *sender){
                                                           log("Collect Button Clicked");
                                                           CashManager *cashmanager = CashManager::getInstance();
                                                           float currentcash = cashmanager->getCurrentCash();
                                                           float currentbucket = cashmanager->getCurrentBucket();
                                                           cashmanager->setCurrentCash(currentcash + currentbucket);
                                                           cashmanager->setCurrentBucket(0);
                                                           cashmanager->setisBucketShown(false);
                                                           Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
                                                           this->removeFromParent();
                                                       });
    btn_collect->setScale(G_SCALEM * 0.8, G_SCALEY * 1.1);
    btn_collect->setAnchorPoint(Vec2(0.0f, 1.0f));
    btn_collect->setPosition(G_SWIDTH / 2 + 5 * G_SCALEM, m_btn_double->getPositionY() - m_btn_double->getBoundingBox().size.height / 2 - 10 * G_SCALEM);
    
    MenuItemImage* btn_close = MenuItemImage::create("cross.png",
                                                     "cross.png",
                                                     [&](Ref *sender)
                                                     {
                                                         SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                         log("Bucket -- Close Button Clicked");
                                                         Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
                                                         
                                                         if (dynamic_cast<GameScene*>(this->getParent())) {
                                                             GameScene* gamescene = (GameScene*)this->getParent();
                                                             gamescene->setButtonEnable(true);
                                                         }
                                                         
                                                         this->removeFromParent();
                                                     });
    btn_close->setPosition(G_SWIDTH * 0.9, G_SHEIGHT * 0.95);
    btn_close->setScale(G_SCALEM * 1.5);
    
    m_menu = Menu::create(m_btn_double, btn_increase, btn_collect, btn_close, NULL);
    m_menu->setPosition(Vec2::ZERO);
    this->addChild(m_menu);
    
    m_spt_TV = Sprite::create("tvPlayCrop.png");
    m_spt_TV->setScale(G_SCALEM * 0.9);
    m_spt_TV->setAnchorPoint(Vec2(1.0, 0.5));
    m_spt_TV->setPosition(m_btn_double->getPositionX() + m_btn_double->getBoundingBox().size.width * 0.38, m_btn_double->getPositionY());
    this->addChild(m_spt_TV);
    
    
    
    CashManager *cashmananger = CashManager::getInstance();
    float currentCash = cashmananger->getCurrentCash();
    float bucketSize = cashmananger->getBucketSize();
    float perHour = cashmananger->getCashPerHour();
    
    m_lbl_double = Label::createWithTTF(StringUtils::format("Double It? Get %s\n Kernels", cashmananger->ConvertAmountToShortString(bucketSize * 2).c_str()), "AmericanTypewriter.ttf", G_SWIDTH / 20);
    m_lbl_double->setPosition(m_btn_double->getPositionX() - m_btn_double->getBoundingBox().size.width * 0.38, m_btn_double->getPositionY());
    m_lbl_double->setAlignment(TextHAlignment::CENTER);
    m_lbl_double->setAnchorPoint(Vec2(0.0f, 0.5f));
    this->addChild(m_lbl_double);
    
    m_lbl_cash = Label::createWithTTF(StringUtils::format("%s\n /%s Kernels", cashmananger->ConvertAmountToShortString(currentCash).c_str(), cashmananger->ConvertAmountToShortString(currentCash).c_str()), "AmericanTypewriter.ttf", G_SWIDTH / 10);
    m_lbl_cash->setColor(Color3B::BLACK);
    m_lbl_cash->setAlignment(TextHAlignment::CENTER);
    m_lbl_cash->setPosition(G_SWIDTH / 2, m_btn_double->getPositionY() + m_btn_double->getBoundingBox().size.height / 2 + m_lbl_cash->getBoundingBox().size.height);
    this->addChild(m_lbl_cash);
    
    m_lbl_perHour = Label::createWithTTF(StringUtils::format("%s Kernels /Hour", cashmananger->ConvertAmountToShortString(perHour).c_str()), "AmericanTypewriter.ttf", G_SWIDTH / 10);
    m_lbl_perHour->setPosition((G_SWIDTH - spt_hand->getBoundingBox().size.width) * 0.5, G_SHEIGHT * 0.8);
    m_lbl_perHour->setWidth((G_SWIDTH - spt_hand->getBoundingBox().size.width) * 0.8);
    m_lbl_perHour->setAlignment(TextHAlignment::CENTER);
    this->addChild(m_lbl_perHour);
    
    
    Label *lbl_increase = Label::createWithTTF("Increase Size", "AmericanTypewriter.ttf", G_SWIDTH / 20);
    lbl_increase->setPosition(btn_increase->getPositionX() - btn_increase->getBoundingBox().size.width * 0.4, btn_increase->getPositionY() - btn_increase->getBoundingBox().size.height / 2);
    this->addChild(lbl_increase);
    
    Label *lbl_collect = Label::createWithTTF("Collect Kernels", "AmericanTypewriter.ttf", G_SWIDTH / 20);
    lbl_collect->setPosition(btn_collect->getPositionX() + btn_collect->getBoundingBox().size.width * 0.4, btn_collect->getPositionY() - btn_collect->getBoundingBox().size.height / 2);
    this->addChild(lbl_collect);
    
    m_btn_double->setVisible(false);
    m_spt_TV->setVisible(false);
    m_lbl_double->setVisible(false);
    
    PluginChartboost::cache("Rewarded Video");
    
    this->schedule(schedule_selector(BucketScene::update), 0.5f);
    
    return true;
}

void BucketScene::setButtonEnable(bool value)
{
    m_menu->setEnabled(value);
}

void BucketScene::update(float dt)
{
    CashManager *cashmananger = CashManager::getInstance();
    float currentCash = cashmananger->getCurrentCash();
    float currentBucket = cashmananger->getCurrentBucket();
    float bucketSize = cashmananger->getBucketSize();
    float perHour = cashmananger->getCashPerHour();
    
    m_lbl_cash->setString(StringUtils::format("%s\n /%s Kernels", cashmananger->ConvertAmountToShortString(currentCash).c_str(), cashmananger->ConvertAmountToShortString(currentCash).c_str()));
    
    m_lbl_perHour->setString(StringUtils::format("%s Kernels /Hour", cashmananger->ConvertAmountToShortString(perHour).c_str()));
    
    if (currentBucket < bucketSize * 0.25) {
        m_spt_bucket->setTexture("bucketLayer1.png");
        m_btn_double->setVisible(false);
        m_spt_TV->setVisible(false);
        m_lbl_double->setVisible(false);
    }else if (currentBucket < bucketSize * 0.5)
    {
        m_spt_bucket->setTexture("bucketLayer2.png");
        m_btn_double->setVisible(false);
        m_spt_TV->setVisible(false);
        m_lbl_double->setVisible(false);
    }else if (currentBucket < bucketSize * 0.75)
    {
        m_spt_bucket->setTexture("bucketLayer3.png");
        m_btn_double->setVisible(false);
        m_spt_TV->setVisible(false);
        m_lbl_double->setVisible(false);
    }else if (currentBucket == bucketSize)
    {
        m_spt_bucket->setTexture("bucketLayer4.png");
        if (PluginChartboost::isAvailable("Rewarded Video")) {
            m_btn_double->setVisible(true);
            m_spt_TV->setVisible(true);
            m_lbl_double->setVisible(true);
            m_lbl_double->setString(StringUtils::format("Double It? Get %s\n Kernels", cashmananger->ConvertAmountToShortString(bucketSize * 2).c_str()));
        }
    }
}

void BucketScene::checkVideo(float dt)
{
    if (UserDefault::getInstance()->getBoolForKey("CollectDBL")) {
        this->removeFromParent();
    }
}
