//
//  InvestmentLayer.cpp
//  Popcorn
//
//  Created by Hans on 7/28/16.
//
//

#include "InvestmentLayer.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "GameScene.hpp"

#define CELL_HEIGHT     200 * G_SCALEY

Scene* InvestmentLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InvestmentLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool InvestmentLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(242, 42, 73, 255))) {
        return false;
    }
    
    list_name.push_back("Skillet");
    list_name.push_back("Air Popper");
    list_name.push_back("Cart");
    list_name.push_back("Stand");
    list_name.push_back("Kernel Store");
    list_name.push_back("Franchise");
    list_name.push_back("Popcorn Farm");
    list_name.push_back("Factory");
    list_name.push_back("Secret Formula");
    list_name.push_back("Popcorn Patent");
    list_name.push_back("Popcorn Gun");
    list_name.push_back("Radioactive Popcorn");
    list_name.push_back("Nuclear Popcorn Plant");
    list_name.push_back("3D Printing");
    list_name.push_back("Cloning");
    list_name.push_back("Moon Popcorn");
    list_name.push_back("Space Factory");
    list_name.push_back("Alien Alliance");
    list_name.push_back("Popcorn Galaxy");
    
    list_countkey.push_back("piggybank_count");
    list_countkey.push_back("mattress_count");
    list_countkey.push_back("comicbook_count");
    list_countkey.push_back("savingaccount_count");
    list_countkey.push_back("bitcoinaccount_count");
    list_countkey.push_back("stockes_count");
    list_countkey.push_back("bookie_count");
    list_countkey.push_back("loanshark_count");
    list_countkey.push_back("angelinvestment_count");
    list_countkey.push_back("vanturecapital_count");
    list_countkey.push_back("porkbelly_count");
    list_countkey.push_back("hedgefund_count");
    list_countkey.push_back("investmentbank_count");
    list_countkey.push_back("insidertrading_count");
    list_countkey.push_back("mortgage_count");
    list_countkey.push_back("pyramid_count");
    list_countkey.push_back("hypercube_count");
    list_countkey.push_back("unholy_count");
    list_countkey.push_back("honey_count");
    
    list_pricekey.push_back("piggybank_price");
    list_pricekey.push_back("mattress_price");
    list_pricekey.push_back("comicbook_price");
    list_pricekey.push_back("savingaccount_price");
    list_pricekey.push_back("bitcoinaccount_price");
    list_pricekey.push_back("stockes_price");
    list_pricekey.push_back("bookie_price");
    list_pricekey.push_back("loanshark_price");
    list_pricekey.push_back("angelinvestment_price");
    list_pricekey.push_back("vanturecapital_price");
    list_pricekey.push_back("porkbelly_price");
    list_pricekey.push_back("hedgefund_price");
    list_pricekey.push_back("investmentbank_price");
    list_pricekey.push_back("insidertrading_price");
    list_pricekey.push_back("mortgage_price");
    list_pricekey.push_back("pyramid_price");
    list_pricekey.push_back("hypercube_price");
    list_pricekey.push_back("unholy_price");
    list_pricekey.push_back("honey_price");
    
    list_profit.push_back("+0.5 Kernels/Sec");
    list_profit.push_back("+1 Kernels/Sec");
    list_profit.push_back("+3 Kernels/Sec");
    list_profit.push_back("+16 Kernels/Sec");
    list_profit.push_back("+50 Kernels/Sec");
    list_profit.push_back("+200 Kernels/Sec");
    list_profit.push_back("+833 Kernels/Sec");
    list_profit.push_back("+3.05K Kernels/Sec");
    list_profit.push_back("+10.55K Kernels/Sec");
    list_profit.push_back("+27.77K Kernels/Sec");
    list_profit.push_back("+72.22K Kernels/Sec");
    list_profit.push_back("+2.25M Kernels/Sec");
    list_profit.push_back("+9.72M Kernels/Sec");
    list_profit.push_back("+27.77M Kernels/Sec");
    list_profit.push_back("+13.33B Kernels/Sec");
    list_profit.push_back("+55.55B Kernels/Sec");
    list_profit.push_back("+122.22B Kernels/Sec");
    list_profit.push_back("+1.31KB Kernels/Sec");
    list_profit.push_back("+213KB Kernels/Sec");
    
    log("Name Count %ld", list_name.size());
    log("Name Count %ld", list_countkey.size());
    log("Name Count %ld", list_pricekey.size());
    return true;
}

void InvestmentLayer::showContent()
{
    auto bg_title = Sprite::create();
    bg_title->setAnchorPoint(Vec2(0, 1));
    bg_title->setTextureRect(Rect(0, 0,G_SWIDTH, CELL_HEIGHT));
    bg_title->setColor(Color3B(235, 13, 57));
    bg_title->setPosition(Vec2(0, this->getContentSize().height));
    this->addChild(bg_title);
    
    Label *lbl_title = Label::createWithTTF("POPPER INVESTMENTS", "AmericanTypewriter.ttf", G_SWIDTH / 15);
    lbl_title->setPosition(G_SWIDTH / 2, bg_title->getPositionY() - 50 * G_SCALEY);
    this->addChild(lbl_title);
    
    Label *lbl_desc = Label::createWithTTF("Earn Kernels Without Clicking", "AmericanTypewriter.ttf", G_SWIDTH / 20);
    lbl_desc->setPosition(G_SWIDTH / 2, lbl_title->getPositionY() - lbl_title->getBoundingBox().size.height);
    this->addChild(lbl_desc);
    
    MenuItemImage* btn_close = MenuItemImage::create("cross.png",
                                                     "cross.png",
                                                     [&](Ref *sender)
                                                     {
                                                         SimpleAudioEngine::getInstance()->playEffect("click.mp3");
                                                         Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
                                                         
                                                         if (dynamic_cast<GameScene*>(this->getParent())) {
                                                             GameScene* gamescene = (GameScene*)this->getParent();
                                                             gamescene->setButtonEnable(true);
                                                         }
                                                         
                                                         this->removeFromParent();
                                                     });
    btn_close->setPosition(G_SWIDTH * 0.95, lbl_title->getPositionY());
    btn_close->setScale(G_SCALEM * 1.5);
    
    Menu *menu = Menu::create(btn_close, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    Sprite *spt_line = Sprite::create();
    spt_line->setAnchorPoint(Vec2(0, 0));
    spt_line->setTextureRect(Rect(0, 0, G_SWIDTH, 5 * G_SCALEY));
    spt_line->setColor(Color3B::WHITE);
    spt_line->setPosition(0, lbl_desc ->getPositionY() - 50 * G_SCALEY);
    this->addChild(spt_line);
    
    Label *lbl_item = Label::createWithTTF("Item", "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_item->setAnchorPoint(Vec2(0.0f, 0.0f));
    lbl_item->setPosition(50 * G_SCALEX, this->getContentSize().height - bg_title->getBoundingBox().size.height + 10 * G_SCALEY);
    this->addChild(lbl_item);
    
    Label *lbl_level = Label::createWithTTF("Level", "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_level->setAnchorPoint(Vec2(0.0f, 0.0f));
    lbl_level->setPosition(300 * G_SCALEX, lbl_item->getPositionY());
    this->addChild(lbl_level);
    
    Label *lbl_price = Label::createWithTTF("Price", "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_price->setAnchorPoint(Vec2(0.0f, 0.0f));
    lbl_price->setPosition(630 * G_SCALEX, lbl_item->getPositionY());
    this->addChild(lbl_price);
    
    Label *lbl_benefit = Label::createWithTTF("Benefit", "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_benefit->setAnchorPoint(Vec2(0.0f, 0.0f));
    lbl_benefit->setPosition(1100 * G_SCALEX, lbl_item->getPositionY());
    this->addChild(lbl_benefit);
    
    m_tableview = TableView::create(this, Size(G_SWIDTH, this->getContentSize().height - bg_title->getContentSize().height));
    m_tableview->setDirection(TableView::Direction::VERTICAL);
    m_tableview->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_tableview->setAnchorPoint(Vec2(0.5, 0.5));
    m_tableview->setDelegate(this);
    m_tableview->setPosition(Vec2(0, 0));
    m_tableview->setColor(Color3B(242, 42, 73));
    this->addChild(m_tableview);
}

ssize_t InvestmentLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return list_name.size();
    
}

TableViewCell* InvestmentLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    int count = UserDefault::getInstance()->getIntegerForKey(list_countkey[idx].c_str(), 0) ;
    float price = UserDefault::getInstance()->getFloatForKey(list_pricekey[idx].c_str(), 0.0f);
    
    auto background_color = Color3B(242, 42, 73);
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0,G_SWIDTH, CELL_HEIGHT));
    bg->setColor(background_color);
    cell->addChild(bg);
    
    auto line = Sprite::create();
    line->setAnchorPoint(Vec2(0, 0));
    line->setTextureRect(Rect(0, 0, G_SWIDTH, 3));
    line->setColor(Color3B::WHITE);
    cell->addChild(line);
    
    Sprite* spt_item = Sprite::create(StringUtils::format("invest%zd.png", idx + 1));
    if (spt_item != nullptr) {
        spt_item->setAnchorPoint(Vec2(0, 0.5));
        spt_item->setScale(G_SCALEM * 0.7);
        spt_item->setPosition(5 * G_SCALEX, CELL_HEIGHT * 0.55);
        spt_item->setTag(456);
        cell->addChild(spt_item);
    }
    
    Sprite* spt_ribb_l = Sprite::create("iapRibbon_l.png");
    spt_ribb_l->setAnchorPoint(Vec2(1, 0.5));
    spt_ribb_l->setPosition(G_SWIDTH * 0.6 - 10 * G_SCALEX, spt_item->getPositionY());
    spt_ribb_l->setScale(G_SCALEX * 1.5, G_SCALEY * 1.2);
    cell->addChild(spt_ribb_l);
    
    Sprite* spt_ribb_r = Sprite::create("iapRibbon_r.png");
    spt_ribb_r->setAnchorPoint(Vec2(0, 0.5));
    spt_ribb_r->setPosition(G_SWIDTH * 0.6 + 10 * G_SCALEX, spt_item->getPositionY());
    spt_ribb_r->setScale(G_SCALEX * 1.5, G_SCALEY * 1.2);
    cell->addChild(spt_ribb_r);
    
    Label *lbl_name = Label::createWithTTF(list_name[idx].c_str(), "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_name->setPosition(20 * G_SCALEX, 25 * G_SCALEY);
    lbl_name->setAnchorPoint(Vec2(0, 0.5));
    cell->addChild(lbl_name);
    
    
    Label *lbl_count = Label::createWithTTF(StringUtils::format("%d", count), "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_count->setPosition(spt_item->getPositionX() + spt_item->getBoundingBox().size.width + 10 * G_SCALEX, spt_item->getPositionY());
    lbl_count->setAnchorPoint(Vec2(0, 0.5));
    cell->addChild(lbl_count);
    
    Label *lbl_price = Label::createWithTTF(StringUtils::format("%s Kernels", CashManager::getInstance()->convertAmountToShortString(price).c_str()),
                                            "AmericanTypewriter.ttf",
                                            G_SWIDTH / 25);
    lbl_price->setWidth(spt_ribb_l->getBoundingBox().size.width * 0.8);
    lbl_price->setAnchorPoint(Vec2(1.0, 0.5));
    lbl_price->setAlignment(TextHAlignment::CENTER);
    lbl_price->setColor(Color3B::BLACK);
    lbl_price->setPosition(spt_ribb_l->getPositionX() - 10 * G_SCALEX, spt_ribb_l->getPositionY());
    cell->addChild(lbl_price);
    
    Label *lbl_profit = Label::createWithTTF(list_profit[idx].c_str(),
                                             "AmericanTypewriter.ttf",
                                             G_SWIDTH / 25);
    lbl_profit->setWidth(spt_ribb_r->getBoundingBox().size.width * 0.8);
    lbl_profit->setAnchorPoint(Vec2(0.0, 0.5));
    lbl_profit->setAlignment(TextHAlignment::CENTER);
    lbl_profit->setColor(Color3B::BLACK);
    lbl_profit->setPosition(spt_ribb_r->getPositionX() - 10 * G_SCALEX, spt_ribb_r->getPositionY());
    cell->addChild(lbl_profit);
    
    if (count == 0) {
        Label *lbl_shaker = Label::createWithTTF("+1", "AmericanTypewriter.ttf", G_SWIDTH / 25);
        lbl_shaker->setPosition(G_SWIDTH * 0.7, lbl_name->getPositionY());
        cell->addChild(lbl_shaker);
        
        Sprite *spt_shaker = Sprite::create("shaker.png");
        spt_shaker->setScale(G_SCALEM * 0.07);
        spt_shaker->setPosition(lbl_shaker->getPositionX() + lbl_shaker->getBoundingBox().size.width + 60 * G_SCALEX, lbl_shaker->getPositionY());
        cell->addChild(spt_shaker);
    }
    
    return cell;
}

Size InvestmentLayer::cellSizeForTable(TableView *table)
{
    return Size(G_SWIDTH, CELL_HEIGHT);
}

void InvestmentLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    log(" %zd Cell Clicked", cell->getIdx());
    
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmanager = CashManager::getInstance();
    SimpleAudioEngine::getInstance()->playEffect("click.mp3");
    
    int index = (int)cell->getIdx();
    float currentCash = cashmanager->getCurrentCash();
    float price = userdefault->getFloatForKey(list_pricekey[index].c_str());
    float count = userdefault->getIntegerForKey(list_countkey[index].c_str());
    float currentShaker = cashmanager->getCurrentShaker();
    
    if (currentCash < price) {
        MessageBox("Not Enough Kernels", "");
        return;
    }else
    {
        cashmanager->setCurrentCash(currentCash - price);
        userdefault->setFloatForKey(list_pricekey[cell->getIdx()].c_str(), price * 1.4);
        if (count == 0) {
            cashmanager->setCurrentShaker(currentShaker + 1);
        }
    }
    cashmanager->updateMoneyPerSecond((int)cell->getIdx());
    userdefault->setIntegerForKey(list_countkey[cell->getIdx()].c_str(), count + 1);
    
    cashmanager->reloadCashPerSecondAndCashPerSwap();
    
    Vec2 offset = table->getContentOffset();
    table->reloadData();
    table->setContentOffset(offset);
}
