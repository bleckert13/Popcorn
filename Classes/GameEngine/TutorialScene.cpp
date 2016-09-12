//
//  TutorialScene.cpp
//  Popcorn
//
//  Created by Hans on 7/28/16.
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
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) {
        return false;
    }
    
    m_tutorIndex = 0;
    
    m_spt_tutorial = Sprite::create(StringUtils::format("tutorialpic%d.png", m_tutorIndex));    
    m_spt_tutorial->setScale(G_SWIDTH / 750, G_SHEIGHT / 1334);
    m_spt_tutorial->setAnchorPoint(Vec2::ZERO);
    m_spt_tutorial->setPosition(Vec2::ZERO);
    this->addChild(m_spt_tutorial);
    
    m_btn_next = MenuItemImage::create("btn_start.png",
                                       "btn_start.png",
                                       CC_CALLBACK_1(TutorialScene::onNextButton, this)
                                       );
    m_btn_next->setPosition(G_SWIDTH * 0.75, 100 * G_SCALEY);
    m_btn_next->setScale(G_SCALEM);
    
    Menu *menu = Menu::create(m_btn_next, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

void TutorialScene::onNextButton(cocos2d::Ref *sender)
{
    m_tutorIndex++;
    if (m_tutorIndex < 13){
        m_spt_tutorial->setTexture(StringUtils::format("tutorialpic%d.png", m_tutorIndex));
    }    
    if (m_tutorIndex == 1) {
        m_btn_next->setNormalImage(Sprite::create("btn_next.png"));
        m_btn_next->setSelectedImage(Sprite::create("btn_next.png"));
    }else if (m_tutorIndex == 12)
    {
        m_btn_next->setNormalImage(Sprite::create("btn_play.png"));
        m_btn_next->setSelectedImage(Sprite::create("btn_play.png"));
    }
    
    switch (m_tutorIndex) {
        case 3:
            m_btn_next->setPosition(G_SWIDTH * 0.75, 40 * G_SCALEY);
            break;
        default:
            m_btn_next->setPosition(G_SWIDTH * 0.75, 150 * G_SCALEY);
            break;
    }
    
    if (m_tutorIndex == 13) {
        UserDefault::getInstance()->setBoolForKey("tutorial", true);
        Director::getInstance()->replaceScene(GameScene::createScene());
    }
}
