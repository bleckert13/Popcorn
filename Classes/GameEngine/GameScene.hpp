//
//  GameScene.hpp
//  Popcorn
//
//  Created by Monkey on 7/27/16.
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
    CREATE_FUNC(GameScene);
private:
    Sprite *BG;
    Sprite *bgSprite;
    Sprite *currentSkewed;
    Sprite *digitSprite;
    Sprite *perSecondRibbon;
    Sprite *bottomClickbar;
    Sprite *topClickbar;
    Sprite *m_BigPopcorn;
    Sprite *GoldenKernel;
    
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
    
    Sprite *PrestigeRibbon;
    Sprite *coverSprite;
    Sprite *ForeverTwenty;
    MoveTo *moveL;
    MoveTo *moveR;
    MenuItemImage *bucketButton;
    MenuItemImage *videobutton;
    MenuItemImage *reviewbutton;
    MenuItemImage *gamecenterButton;
//    MenuItemImage *popcornButton;
    
    Vector<Sprite*> skewdArray;
    
    Label *MoneyPerSwapLabel;
    
    Label *MoneyPerSecondLabel;
    
    Label *scoreLabel;
    
    Label *prestigeLabel;
    // UILabel *Score_Label;
    
    Label *MultiplierLabel;
    Label *ClickMultiplierLabel;
    Label *BonusLabel;
    
    Label *TutorialLabel;
    
    
    Point startPoint;
    Point endPoint;
    int Review;
    int adCount;
    int swapsCount;
    int barwidth;
    bool popping;
    bool Lmoving;
    int BonusNumber;
    int RandomMultiplier;
    int ClickMultiplier;
    int videoClicks;
    int VideoBonusNumb;;
    int LoadedVideo;
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
    bool VideoBonus;
    bool TwentyReward;
    bool KingBonus;
    int idle;
    bool doublethirty;
    int  doublethirtytime;
    bool twentyten;
    int  twentytentime;
    int     RDMShaker;
    bool    idleshown;
    bool    messageshown;
    
//    NSMutableArray *NumbersArray;
//    
//    NSMutableArray *NumbersArraylower;
    
    UserDefault *userdefault;
    
    void tick(float dt);
    void scroll(float dt);
    void topMove();
    void move();
    void CheckPrestige();
    void CheckPlayedVideo(float dt);
    void CheckReward(float dt);
    void CheckVideo(float dt);
    void BigPopcorn();
    void CheckUnlockables();
    void RollDollar(float dt);
    void PersecondLabel(float dt);
    void AddPerSecond(float dt);
    void ShowBucket();
    void AddCashPerSwap();
    void AddSkwedSprite();
    void AddBonus();
    void RemoveMultiplier();
    void Multiplier();
    void MultiplyValue();
    void AnimateSkewdSprite();
    void Background(float dt);
    void Unlockables(float dt);
    void AddVideoBonus();
    void BonusAnimation();
    void panForTranslation(Point translation);
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *pEvent);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *pEvent);
};
#endif /* GameScene_hpp */
