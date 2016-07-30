//
//  VideoScene.hpp
//  Popcorn
//
//  Created by Monkey on 7/28/16.
//
//

#ifndef VideoScene_hpp
#define VideoScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class VideoScene:public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(VideoScene);
private:
    void video(Ref *sender);
    
    Label *lbl_desc;
    int bonus;
    int loads;
    bool reset;
};
#endif /* VideoScene_hpp */
