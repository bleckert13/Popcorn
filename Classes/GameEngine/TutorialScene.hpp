//
//  TutorialScene.hpp
//  Popcorn
//
//  Created by Monkey on 7/28/16.
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
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(TutorialScene);

};

#endif /* TutorialScene_hpp */
