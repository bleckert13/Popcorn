//
//  CashManager.cpp
//  Popcorn
//
//  Created by Hans on 7/25/16.
//
//

#include "CashManager.hpp"

static CashManager *cashManagerSharedInstance = NULL;

CashManager::CashManager()
{
    m_currentShakers = 0;
    m_currentCash = 0;
    m_cashPerSecond = 0;
    m_cashPerSwap = 0;
    m_cashPerhour = 0;
    m_bucketSize = 0;
    m_currentBucket = 0;
    m_convertamount = 0;
    m_isBucketShown = false;
    m_overflow = false;
}

CashManager* CashManager::getInstance()
{
    if (cashManagerSharedInstance == NULL) {
        cashManagerSharedInstance = new CashManager();
    }    
    return cashManagerSharedInstance;
}

void CashManager::saveCurrentCash()
{
    UserDefault::getInstance()->setFloatForKey("currentcash", m_currentCash);
    UserDefault::getInstance()->setFloatForKey("currentshakers", m_currentShakers);
}

string CashManager::convertAmountToShortString(float amount)
{
    string retval = "";
    if (amount < 999) {
        amount = amount;
        retval = StringUtils::format("%.2f", amount);
    }
    else if (amount >= 999 && amount < 999999) {
        amount = amount / 1000;
        retval = StringUtils::format("%.2fK", amount);
    }
    else if (amount >= 999999 && amount < 999999999) {
        amount = amount / 1000000;
        retval = StringUtils::format("%.2fM", amount);
    }
    else if (amount >= 999999999 && amount < 999999999999) {
        amount = amount / 1000000000;
        retval = StringUtils::format("%.2fB", amount);
    }
    else if (amount >= 999999999999 && amount < 999999999999999) {
        amount = amount / 1000000000000;
        retval = StringUtils::format("%.2fKB", amount);
    }
    else if (amount >= 999999999999999){
        amount = amount / 1000000000000000;
        retval = StringUtils::format("%.2fMB", amount);
    }
    return retval;
}

float CashManager::moneyPerSecond()
{
    float moneyPerSecond = 0;
    UserDefault *userdeault = UserDefault::getInstance();
    
    moneyPerSecond += userdeault->getIntegerForKey("piggybank_count", 0)        * 0.5;
    moneyPerSecond += userdeault->getIntegerForKey("mattress_count", 0)         * 1.0;
    moneyPerSecond += userdeault->getIntegerForKey("comicbook_count", 0)        * 3.0;
    moneyPerSecond += userdeault->getIntegerForKey("savingaccount_count", 0)    * 16;
    moneyPerSecond += userdeault->getIntegerForKey("bitcoinaccount_count", 0)   * 50;
    moneyPerSecond += userdeault->getIntegerForKey("stockes_count", 0)          * 200;
    moneyPerSecond += userdeault->getIntegerForKey("bookie_count", 0)           * 833;
    moneyPerSecond += userdeault->getIntegerForKey("loanshark_count", 0)        * 3050;
    moneyPerSecond += userdeault->getIntegerForKey("angelinvestment_count", 0)  * 10500;
    moneyPerSecond += userdeault->getIntegerForKey("vanturecapital_count", 0)   * 27770;
    moneyPerSecond += userdeault->getIntegerForKey("porkbelly_count", 0)        * 72220;
    moneyPerSecond += userdeault->getIntegerForKey("hedgefund_count", 0)        * 2250000;
    moneyPerSecond += userdeault->getIntegerForKey("investmentbank_count", 0)   * 9720000;
    moneyPerSecond += userdeault->getIntegerForKey("insidertrading_count", 0)   * 27077000;
    moneyPerSecond += userdeault->getIntegerForKey("mortgage_count", 0)         * 13330000000;
    moneyPerSecond += userdeault->getIntegerForKey("pyramid_count", 0)          * 55550000000;
    moneyPerSecond += userdeault->getIntegerForKey("hypercube_count", 0)        * 122220000000;
    moneyPerSecond += userdeault->getIntegerForKey("unholy_count", 0)           * 1305000000000;
    moneyPerSecond += userdeault->getIntegerForKey("honey_count", 0)            * 213000000000000;
    
    return moneyPerSecond;
}

void CashManager::updateMoneyPerSecond(int index)
{
    switch (index) {
        case 0:
            m_cashPerSecond += 0.5;
            break;
        case 1:
            m_cashPerSecond += 1.0;
            break;
        case 2:
            m_cashPerSecond += 3.0;
            break;
        case 3:
            m_cashPerSecond += 16;
            break;
        case 4:
            m_cashPerSecond += 50;
            break;
        case 5:
            m_cashPerSecond += 200;
            break;
        case 6:
            m_cashPerSecond += 833;
            break;
        case 7:
            m_cashPerSecond += 3050;
            break;
        case 8:
            m_cashPerSecond += 10500;
            break;
        case 9:
            m_cashPerSecond += 27770;
            break;
        case 10:
            m_cashPerSecond += 72220;
            break;
        case 11:
            m_cashPerSecond += 2250000;
            break;
        case 12:
            m_cashPerSecond += 9720000;
            break;
        case 13:
            m_cashPerSecond += 27077000;
            break;
        case 14:
            m_cashPerSecond += 13330000000;
            break;
        case 15:
            m_cashPerSecond += 55550000000;
            break;
        case 16:
            m_cashPerSecond += 122220000000;
            break;
        case 17:
            m_cashPerSecond += 1305000000000;
            break;
        case 18:
            m_cashPerSecond += 213000000000000;
            break;
        default:
            break;
    }
    UserDefault::getInstance()->setFloatForKey("CashPerSceond", m_cashPerSecond);
}

float CashManager::moneyPerHour(){
    
    float moneyperhour=0;
    
    UserDefault *userdeault = UserDefault::getInstance();
    moneyperhour += userdeault->getIntegerForKey("0_count", 0) * 50;
    moneyperhour += userdeault->getIntegerForKey("1_count", 0) * 100;
    moneyperhour += userdeault->getIntegerForKey("3_count", 0) * 4000;
    moneyperhour += userdeault->getIntegerForKey("5_count", 0) * 18000;
    moneyperhour += userdeault->getIntegerForKey("7_count", 0) * 600000;
    moneyperhour += userdeault->getIntegerForKey("9_count", 0) * 25000000;
    moneyperhour += userdeault->getIntegerForKey("11_count", 0) * 1000000000;
    moneyperhour += userdeault->getIntegerForKey("13_count", 0) * 10000000000000;
    moneyperhour += userdeault->getIntegerForKey("15_count", 0) * 800000000000000;
    return moneyperhour;
}

float CashManager::bucketSize()
{
    float bucketsize=0;
    UserDefault *userdeault = UserDefault::getInstance();
    bucketsize += userdeault->getIntegerForKey("0_count", 0) * 30;
    bucketsize += userdeault->getIntegerForKey("2_count", 0) * 1000;
    bucketsize += userdeault->getIntegerForKey("4_count", 0) * 8000;
    bucketsize += userdeault->getIntegerForKey("6_count", 0) * 150000;
    bucketsize += userdeault->getIntegerForKey("8_count", 0) * 6000000;
    bucketsize += userdeault->getIntegerForKey("10_count", 0) * 400000000;
    bucketsize += userdeault->getIntegerForKey("12_count", 0) * 600000000000;
    bucketsize += userdeault->getIntegerForKey("14_count", 0) * 45000000000000;
    
    return bucketsize;
}

float CashManager::moneyPerSwap()
{
    float moneyPerSwap = 0.1f;
    UserDefault *userdeault = UserDefault::getInstance();
    
    if (userdeault->getIntegerForKey("paperroute_count", 0) ==1) {
        moneyPerSwap=.3;
    }
    if (userdeault->getIntegerForKey("paperroute_count", 0) ==2) {
        moneyPerSwap = .5;
    }
    if (userdeault->getIntegerForKey("paperroute_count", 0) ==3) {
        moneyPerSwap = 1;
    }
    if (userdeault->getIntegerForKey("lemon_count", 0) ==1) {
        moneyPerSwap = 1.75;
    }
    if (userdeault->getIntegerForKey("lemon_count", 0) ==2) {
        moneyPerSwap=3.25;
    }
    if (userdeault->getIntegerForKey("lemon_count", 0) ==3) {
        moneyPerSwap=5.75;
    }
    if (userdeault->getIntegerForKey("flower_count", 0) ==1) {
        moneyPerSwap=10;
    }
    if (userdeault->getIntegerForKey("flower_count", 0) ==2) {
        moneyPerSwap=18.75;
    }
    if (userdeault->getIntegerForKey("flower_count", 0) ==3) {
        moneyPerSwap=35;
    }
    if (userdeault->getIntegerForKey("coffee_count", 0) ==1) {
        moneyPerSwap=60;
    }
    if (userdeault->getIntegerForKey("coffee_count", 0) ==2) {
        moneyPerSwap=110;
    }
    if (userdeault->getIntegerForKey("coffee_count", 0) ==3) {
        moneyPerSwap=200;
    }
    if (userdeault->getIntegerForKey("fastfood_count", 0) ==1) {
        moneyPerSwap=350;
    }
    if (userdeault->getIntegerForKey("fastfood_count", 0) ==2) {
        moneyPerSwap=600;
    }
    if (userdeault->getIntegerForKey("fastfood_count", 0) ==3) {
        moneyPerSwap=1100;
    }
    if (userdeault->getIntegerForKey("casino_count", 0) ==1) {
        moneyPerSwap=2050;
    }
    if (userdeault->getIntegerForKey("casino_count", 0) ==2) {
        moneyPerSwap=3690;
    }
    if (userdeault->getIntegerForKey("casino_count", 0) ==3) {
        moneyPerSwap=6600;
    }
    if (userdeault->getIntegerForKey("cigrate_count", 0) ==1) {
        moneyPerSwap=12000;
    }
    if (userdeault->getIntegerForKey("cigrate_count", 0) ==2) {
        moneyPerSwap=22000;
    }
    if (userdeault->getIntegerForKey("cigrate_count", 0) ==3) {
        moneyPerSwap=38000;
    }
    if (userdeault->getIntegerForKey("soda_count", 0) ==1) {
        moneyPerSwap=70000;
    }
    if (userdeault->getIntegerForKey("soda_count", 0) ==2) {
        moneyPerSwap=125000;
    }
    if (userdeault->getIntegerForKey("soda_count", 0) ==3) {
        moneyPerSwap=225000;
    }
    if (userdeault->getIntegerForKey("railroad_count", 0) ==1) {
        moneyPerSwap=400000;
    }
    if (userdeault->getIntegerForKey("railroad_count", 0) ==2) {
        moneyPerSwap=730000;
    }
    if (userdeault->getIntegerForKey("railroad_count", 0) ==3) {
        moneyPerSwap=1300000;
    }
    if (userdeault->getIntegerForKey("strip_count", 0) ==1) {
        moneyPerSwap=2400000;
    }
    if (userdeault->getIntegerForKey("strip_count", 0) ==2) {
        moneyPerSwap=4250000;
    }
    if (userdeault->getIntegerForKey("strip_count", 0) ==3) {
        moneyPerSwap=7700000;
    }
    if (userdeault->getIntegerForKey("arctic_count", 0) ==1) {
        moneyPerSwap=14000000;
    }
    if (userdeault->getIntegerForKey("arctic_count", 0) ==2) {
        moneyPerSwap=25000000;
    }
    if (userdeault->getIntegerForKey("arctic_count", 0) ==3) {
        moneyPerSwap=45000000;
    }
    if (userdeault->getIntegerForKey("candytheft_count", 0) ==1) {
        moneyPerSwap=80000000;
    }
    if (userdeault->getIntegerForKey("candytheft_count", 0) ==2) {
        moneyPerSwap=145000000;
    }
    if (userdeault->getIntegerForKey("candytheft_count", 0) ==3) {
        moneyPerSwap=260000000;
    }
    if (userdeault->getIntegerForKey("oldlady_count", 0) ==1) {
        moneyPerSwap=470000000;
    }
    if (userdeault->getIntegerForKey("oldlady_count", 0) ==2) {
        moneyPerSwap=850000000;
    }
    if (userdeault->getIntegerForKey("oldlady_count", 0) ==3) {
        moneyPerSwap=1500000000;
    }
    if (userdeault->getIntegerForKey("clown_count", 0) ==1) {
        moneyPerSwap=2750000000;
    }
    if (userdeault->getIntegerForKey("clown_count", 0) ==2) {
        moneyPerSwap=4900000000;
    }
    if (userdeault->getIntegerForKey("clown_count", 0) ==3) {
        moneyPerSwap=8900000000;
    }
    
    if (userdeault->getIntegerForKey("nsa_count", 0) ==1) {
        moneyPerSwap=16000000000;
    }
    if (userdeault->getIntegerForKey("nsa_count", 0) ==2) {
        moneyPerSwap=28800000000;
    }
    if (userdeault->getIntegerForKey("nsa_count", 0) ==3) {
        moneyPerSwap=52000000000;
    }
    if (userdeault->getIntegerForKey("dog_count", 0) ==1) {
        moneyPerSwap=93300000000;
    }
    if (userdeault->getIntegerForKey("dog_count", 0) ==2) {
        moneyPerSwap=168000000000;
    }
    if (userdeault->getIntegerForKey("dog_count", 0) ==3) {
        moneyPerSwap=302000000000;
    }
    if (userdeault->getIntegerForKey("cat_count", 0) ==1) {
        moneyPerSwap=544000000000;
    }
    if (userdeault->getIntegerForKey("cat_count", 0) ==2) {
        moneyPerSwap=980000000000;
    }
    if (userdeault->getIntegerForKey("cat_count", 0) ==3) {
        moneyPerSwap=1750000000000;
    }
    if (userdeault->getIntegerForKey("cryogenic_count", 0) ==1) {
        moneyPerSwap=3200000000000;
    }
    if (userdeault->getIntegerForKey("cryogenic_count", 0) ==2) {
        moneyPerSwap=5750000000000;
    }
    if (userdeault->getIntegerForKey("cryogenic_count", 0) ==3) {
        moneyPerSwap=10200000000000;
    }
    if (userdeault->getIntegerForKey("banana_count", 0) ==1) {
        moneyPerSwap=18500000000000;
    }
    if (userdeault->getIntegerForKey("banana_count", 0) ==2) {
        moneyPerSwap=33300000000000;
    }
    if (userdeault->getIntegerForKey("banana_count", 0) ==3) {
        moneyPerSwap=60000000000000;
    }
    return moneyPerSwap;
}

void CashManager::reloadCashPerSecondAndCashPerSwap()
{
//    m_cashPerSecond = moneyPerSecond();
    m_cashPerSecond = UserDefault::getInstance()->getFloatForKey("CashPerSceond", 0.0f);
    m_cashPerSwap = moneyPerSwap();
    m_cashPerhour = moneyPerHour();
    m_bucketSize = bucketSize();
}

float CashManager::getCurrentCash()
{
    return m_currentCash;
}

float CashManager::getCashPerSwap()
{
    return m_cashPerSwap;
}

float CashManager::getCashPerSecond()
{
    return m_cashPerSecond;
}

float CashManager::getCurrentShaker()
{
    return m_currentShakers;
}

bool CashManager::getisBucketShown()
{
    return m_isBucketShown;
}

float CashManager::getBucketSize()
{
    return m_bucketSize;
}

float CashManager::getCashPerHour()
{
    return m_cashPerhour;
}

float CashManager::getCurrentBucket()
{
    return m_currentBucket;
}

void CashManager::setCashPerSwap(float value)
{
    m_cashPerSwap = value;
}

void CashManager::setCurrentCash(float value)
{
    m_currentCash = value;
}

void CashManager::setCashPerScecond(float value)
{
    m_cashPerSecond = value;
    UserDefault::getInstance()->setFloatForKey("CashPerSceond", m_cashPerSecond);
}

void CashManager::setCurrentShaker(float value)
{
    m_currentShakers = value;
}

void CashManager::setCurrentBucket(float value)
{
    m_currentBucket = value;
}

void CashManager::setisBucketShown(bool value)
{
    m_isBucketShown = value;
}

void CashManager::setCashPerHour(float value)
{
    m_cashPerhour = value;
}

void CashManager::setBucketSize(float value)
{
    m_bucketSize = value;
}
