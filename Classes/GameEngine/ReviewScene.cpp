//
//  ReviewScene.cpp
//  Popcorn
//
//  Created by Hans on 7/28/16.
//
//

#include "ReviewScene.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "GameScene.hpp"

Scene* ReviewScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ReviewScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ReviewScene::init()
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
    bg_title->setPosition(G_SWIDTH / 2, G_SHEIGHT * 5 / 6);
    this->addChild(bg_title);
    
    Label *lbl_title = Label::createWithTTF(T_REVIEW_TITLE, "AmericanTypewriter.ttf", G_SWIDTH / 15);
    lbl_title->setPosition(bg_title->getPosition());
    lbl_title->setAlignment(TextHAlignment::CENTER);
    lbl_title->setWidth(bg_title->getBoundingBox().size.width * 0.9);
    this->addChild(lbl_title);
    
    Label *lbl_desc = Label::createWithTTF(T_REVIEW_DESC, "AmericanTypewriter.ttf", G_SWIDTH / 10);
    lbl_desc->setPosition(G_SWIDTH / 2, bg_title->getPositionY() - bg_title->getBoundingBox().size.height / 2 - 100 * G_SCALEM);
    lbl_desc->setAnchorPoint(Vec2(0.5f, 1.0f));
    lbl_desc->setWidth(G_SWIDTH * 0.9);
    lbl_desc->setAlignment(TextHAlignment::CENTER);
    this->addChild(lbl_desc);
    
    MenuItemImage *btn_sugg = MenuItemImage::create("PerSecondLabel.png",
                                                    "PerSecondLabel.png",
                                                    [&](Ref *sender){
                                                        log("Suggest Button Clicked -- Send Email --");
                                                        
                                                    });
    btn_sugg->setPosition(G_SWIDTH / 2, G_SHEIGHT / 3);
    btn_sugg->setScale(G_SCALEM * 0.9);
    
    MenuItemImage *btn_better = MenuItemImage::create("btn_left.png",
                                                      "btn_left.png",
                                                      [&](Ref *sender){
                                                          log("Don't Like Clicked - Send Email -");
                                                      });
    btn_better->setScale(G_SCALEM * 0.8);
    btn_better->setAnchorPoint(Vec2(1.0f, 1.0f));
    btn_better->setPosition(G_SWIDTH / 2 - 5 * G_SCALEM, btn_sugg->getPositionY() - btn_sugg->getBoundingBox().size.height / 2 - 10 * G_SCALEM);
    
    MenuItemImage *btn_rate = MenuItemImage::create("btn_right.png",
                                                    "btn_right.png",
                                                    [&](Ref *sender){
                                                        log("Rate Button Clicked");
                                                        
                                                        if (!UserDefault::getInstance()->getBoolForKey("Reviewed")) {
                                                            CashManager::getInstance()->setCurrentCash(CashManager::getInstance()->getCurrentCash() * 1.05);
                                                        }
                                                    });
    btn_rate->setScale(G_SCALEM * 0.8);
    btn_rate->setAnchorPoint(Vec2(0.0f, 1.0f));
    btn_rate->setPosition(G_SWIDTH / 2 + 5 * G_SCALEM, btn_sugg->getPositionY() - btn_sugg->getBoundingBox().size.height / 2 - 10 * G_SCALEM);
    
    MenuItemImage* btn_close = MenuItemImage::create("cross.png",
                                                     "cross.png",
                                                     [&](Ref *sender)
                                                     {
                                                         log("Review -- Close Button Clicked");
                                                         Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
                                                         
                                                         if (dynamic_cast<GameScene*>(this->getParent())) {
                                                             GameScene* gamescene = (GameScene*)this->getParent();
                                                             gamescene->setButtonEnable(true);
                                                         }
                                                         
                                                         this->removeFromParent();
                                                     });
    btn_close->setPosition(G_SWIDTH * 0.9, G_SHEIGHT * 0.95);
    btn_close->setScale(G_SCALEM * 1.5);
    
    Menu *menu = Menu::create(btn_sugg, btn_better, btn_rate, btn_close, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    Label *lbl_sugg = Label::createWithTTF(T_REVIEW_SUGG, "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_sugg->setWidth(btn_sugg->getBoundingBox().size.width * 0.5);
    lbl_sugg->setAlignment(TextHAlignment::CENTER);
    lbl_sugg->setAnchorPoint(Vec2(0.5, 0.5));
    lbl_sugg->setPosition(btn_sugg->getPosition());
    this->addChild(lbl_sugg);
    
    Label *lbl_cancel = Label::createWithTTF(T_REVIEW_CANCEL,  "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_cancel->setWidth(btn_better->getBoundingBox().size.width * 0.8);
    lbl_cancel->setAlignment(TextHAlignment::CENTER);
    lbl_cancel->setAnchorPoint(Vec2(1.0, 0.5));
    lbl_cancel->setPosition(btn_better->getPositionX() - 10 * G_SCALEM, btn_better->getPositionY() - btn_better->getBoundingBox().size.height / 2);
    this->addChild(lbl_cancel);
    
    Label *lbl_rate = Label::createWithTTF(T_REVIEW_RATE,  "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_rate->setWidth(btn_rate->getBoundingBox().size.width * 0.8);
    lbl_rate->setAlignment(TextHAlignment::CENTER);
    lbl_rate->setAnchorPoint(Vec2(0.0, 0.5));
    lbl_rate->setPosition(btn_rate->getPositionX() + 10 * G_SCALEM, btn_rate->getPositionY() - btn_rate->getBoundingBox().size.height / 2);
    this->addChild(lbl_rate);
    
    return true;
}