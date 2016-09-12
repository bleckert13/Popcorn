//
//  ReviewScene.hpp
//  Popcorn
//
//  Created by Hans on 7/28/16.
//
//

#ifndef ReviewScene_hpp
#define ReviewScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class ReviewScene:public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(ReviewScene);
};

#endif /* ReviewScene_hpp */
