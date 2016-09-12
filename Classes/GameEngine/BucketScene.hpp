//
//  BucketScene.hpp
//  Popcorn
//
//  Created by Hans on 8/8/16.
//
//

#ifndef BucketScene_hpp
#define BucketScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

class BucketScene:public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    void setButtonEnable(bool value);
    CREATE_FUNC(BucketScene);    
private:
    Label *m_lbl_cash;
    Label *m_lbl_perHour;
    Label *m_lbl_double;
    Sprite *m_spt_bucket;
    Sprite *m_spt_TV;
    MenuItemImage *m_btn_double;
    Menu *m_menu;
    void update(float dt);
    void checkVideo(float dt);
};


#endif /* BucketScene_hpp */
