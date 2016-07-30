//
//  TutorialScene.cpp
//  Popcorn
//
//  Created by Monkey on 7/28/16.
//
//

#include "TutorialScene.hpp"
#include "Constants.h"
#include "GameScene.hpp"

Scene* TutorialScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TutorialScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TutorialScene::init()
{
    if (!LayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
        return false;
    }
    
    Label *title = Label::createWithTTF(T_TUTOR_TITLE, "AmericanTypewriter.ttf", G_SWIDTH / 12);
    title->setPosition(G_SWIDTH / 2, G_SHEIGHT * 4 / 5);
    title->setColor(Color3B::BLACK);
    this->addChild(title);
    
    Label *desc = Label::createWithTTF(T_TUTOR_DES, "AmericanTypewriter.ttf", G_SWIDTH / 20);
    desc->setPosition(G_SWIDTH / 2, title->getPositionY() - 100 * G_SCALEM);
    desc->setAnchorPoint(Vec2(0.5, 1));
    desc->setWidth(G_SWIDTH * 0.9);
    desc->setColor(Color3B::BLACK);
    this->addChild(desc);

    Sprite *shaker = Sprite::create("shaker.png");
    shaker->setScale(G_SCALEM * 0.12);
    shaker->setAnchorPoint(Vec2(0.0f, 0.5f));
    shaker->setPosition(G_SWIDTH * 0.1, desc->getPositionY() - desc->getBoundingBox().size.height - shaker->getBoundingBox().size.height / 2 - 20 * G_SCALEM);
    this->addChild(shaker);

    Label *item_desc1 = Label::createWithTTF(T_TUTOR_ITEM1, "AmericanTypewriter.ttf", G_SWIDTH / 25);
    item_desc1->setWidth(G_SWIDTH * 0.6);
    item_desc1->setAnchorPoint(Vec2(0.0f, 0.5f));
    item_desc1->setPosition(shaker->getPositionX() + shaker->getBoundingBox().size.width + 40 * G_SCALEM, shaker->getPositionY());
    item_desc1->setColor(Color3B::BLACK);
    this->addChild(item_desc1);

    Sprite *presteige = Sprite::create("presteige.png");
    presteige->setScale(G_SCALEM * 0.2);
    presteige->setAnchorPoint(Vec2(0.0f, 0.5f));
    presteige->setPosition(G_SWIDTH * 0.1, item_desc1->getPositionY() - item_desc1->getBoundingBox().size.height - 20 * G_SCALEM);
    this->addChild(presteige);
    
    Label *item_desc2 = Label::createWithTTF(T_TUTOR_ITEM2, "AmericanTypewriter.ttf", G_SWIDTH / 25);
    item_desc2->setWidth(G_SWIDTH * 0.6);
    item_desc2->setAnchorPoint(Vec2(0.0f, 0.5f));
    item_desc2->setPosition(item_desc1->getPositionX(), presteige->getPositionY());
    item_desc2->setColor(Color3B::BLACK);
    this->addChild(item_desc2);
    
    MenuItemImage* btn_close = MenuItemImage::create("cross.png",
                                                     "cross.png",
                                                     [&](Ref *sender)
                                                     {
                                                         UserDefault::getInstance()->setBoolForKey("tutorial", true);
                                                         Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::createScene()));
                                                     });
    btn_close->setPosition(G_SWIDTH * 0.9, G_SHEIGHT * 0.9);
    btn_close->setScale(G_SCALEM * 1.5);
    
    Menu *menu = Menu::create(btn_close, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}