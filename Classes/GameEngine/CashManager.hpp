//
//  CashManager.hpp
//  Popcorn
//
//  Created by Monkey on 7/25/16.
//
//

#ifndef CashManager_hpp
#define CashManager_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class CashManager{
private:
    float m_currentShakers;
    float m_currentCash;
    float m_cashPerSecond;
    float m_cashPerSwap;
    float m_cashPerhour;
    float m_bucketSize;
    float m_currentBucket;
    float m_convertamount;
    bool m_isBucketShown;
    bool m_overflow;
    
public:
    CashManager();
    ~CashManager();
    static CashManager* getInstance();
    string ConvertAmountToShortString(float amount);
    string ConvertNewAmountToShortString(float newamount);
    void reloadCashPerSecondAndCashPerSwap();
    void saveCurrentCash();
    float moneyPerSecond();
    float moneyPerHour();
    float bucketSize();
    float moneyPerSwap();
    
    float getCurrentCash();
    float getCashPerSwap();
    float getCashPerSecond();
    float getCurrentShaker();
    float getCashPerHour();
    float getBucketSize();
    float getCurrentBucket();
    bool  getisBucketShown();
    
    void setCurrentCash(float value);
    void setCashPerSwap(float value);
    void setCashPerScecond(float value);
    void setCurrentShaker(float value);
    void setCurrentBucket(float value);
    void setisBucketShown(bool value);
    void setCashPerHour(float value);
    void setBucketSize(float value);

};

#endif /* CashManager_hpp */
