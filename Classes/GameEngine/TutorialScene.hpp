//
//  TutorialScene.hpp
//  Popcorn
//
//  Created by Hans on 7/28/16.
//
//

#ifndef TutorialScene_hpp
#define TutorialScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class TutorialScene:public LayerColor
{
private:
    Sprite *m_spt_tutorial;
    MenuItemImage* m_btn_next;
    void onNextButton(Ref *sender);
    int m_tutorIndex;
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(TutorialScene);
};

#endif /* TutorialScene_hpp */
