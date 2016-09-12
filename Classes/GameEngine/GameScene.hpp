//
//  GameScene.hpp
//  Popcorn
//
//  Created by Hans on 7/27/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameScene : public Layer
{
public:
    virtual bool init();
    static Scene* createScene();
    void setButtonEnable(bool value);
    CREATE_FUNC(GameScene);    
private:
    Sprite *BG;
    Sprite *m_spt_Bucket;
    Sprite *currentSkewed;
    Sprite *digitSprite;
    Sprite *perSecondRibbon;
    Sprite *bottomClickbar;
    Sprite *topClickbar;
    Sprite *m_spt_BigPopcorn;
    Sprite *m_spt_GoldenKernel;
    
    Sprite *mBG1;
    Sprite *mBG2;
    Size s;
    
    Sprite *background1;
    Sprite *background2;
    
    Sprite *BonusKernel1;
    Sprite *BonusKernel2;
    Sprite *BonusKernel3;
    Sprite *BonusRibbon;
    
    Sprite *skewd;
    
    Sprite *m_spt_PrestigeRibbon;
    Sprite *m_spt_Cover;
    Sprite *m_spt_ForeverTwenty;
    MoveTo *moveL;
    MoveTo *moveR;
    MenuItemImage *bucketButton;
    MenuItemImage *videobutton;
    MenuItemImage *reviewbutton;
    MenuItemImage *gamecenterButton;
//    MenuItemImage *popcornButton;
    Menu *m_btnmenu;
    
    Vector<Sprite*> skewdArray;
    
    Label *m_lbl_MoneyPerSwap;
    
    Label *m_lbl_MoneyPerSecond;
    
    Label *m_lbl_Score;
    
    Label *m_lbl_Prestige;
    // UILabel *Score_Label;
    
    Label *m_lbl_MultiplierLabel;
    Label *m_lbl_ClickMultiplierLabel;
    Label *m_lbl_Bonus;
    
    Label *m_lbl_Tutorial;
    
    TTFConfig m_ttfconf_score;
    
    
    Point startPoint;
    Point endPoint;
    int review;
    int adCount;
    int swapsCount;
    int barwidth;
    bool popping;
    bool m_bool_Lmoving;
    int m_int_BonusNumber;
    int m_int_RandomMultiplier;
    int m_int_ClickMultiplier;
    int videoClicks;
    int m_int_VideoBonusNumb;;
    int m_int_LoadedVideo;
    bool twox;
    bool threex;
    bool fivex;
    bool twentyx;
    bool classicbox;
    bool chefhat;
    bool piggybank;
    bool moon;
    bool earth;
    bool spaceship;
    bool ufo;
    bool dinnerplate;
    bool trophy;
    bool car;
    bool umbrella;
    bool diamond;
    bool kingkernel;
    bool ribbonshown;
    bool prestiged;
    bool facebook;
    bool twitter;
    bool m_b_VideoBonus;
    bool m_b_TwentyReward;
    bool m_b_KingBonus;
    int idle;
    bool doublethirty;
    int  doublethirtytime;
    bool twentyten;
    int  twentytentime;
    int  m_int_RDMShaker;
    bool idleshown;
    bool messageshown;
    
    UserDefault *m_userdefault;
    
    void tick(float dt);
    void scroll(float dt);
    void topMove();
    void move();
    void checkPrestige();
    void checkPlayedVideo(float dt);
    void checkReward(float dt);
    void checkVideo(float dt);
    void bigPopcorn();
    void checkUnlockables();
    void rollDollar(float dt);
    void persecondLabel(float dt);
    void addPerSecond(float dt);
    void showBucket();
    void addCashPerSwap();
    void addSkwedSprite();
    void addBonus();
    void removeMultiplier();
    void multiplier();
    void multiplyValue();
    void animateSkewdSprite();
    void setBackground(float dt);
    void unlockables(float dt);
    void addVideoBonus();
    void bonusAnimation();
    void panForTranslation(Point translation);
    
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
};
#endif /* GameScene_hpp */
