//
//  BusinessLayer.cpp
//  Popcorn
//
//  Created by Monkey on 7/30/16.
//
//

#include "BusinessLayer.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "GameScene.hpp"

#define CELL_HEIGHT     200 * G_SCALEY

Scene* BusinessLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BusinessLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool BusinessLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(242, 42, 73, 255))) {
        return false;
    }
    
    list_name.push_back("Popcorn Chicken");
    list_name.push_back("Popcorn Shrimp");
    list_name.push_back("Popcorn Protein");
    list_name.push_back("Popcorn Tree");
    list_name.push_back("Genetically Modified Corn");
    list_name.push_back("Popcorn Bricks");
    list_name.push_back("House of Corn");
    list_name.push_back("Popcorn City");
    list_name.push_back("Island of Corn");
    list_name.push_back("Popcorn Country");
    list_name.push_back("Sea of Corn");
    list_name.push_back("Popcorn Rain");
    list_name.push_back("Popcorn Virus");
    list_name.push_back("Digital Corn");
    list_name.push_back("Electric Corn");
    list_name.push_back("Popcorn Air");
    list_name.push_back("Popcorn Planet");
    list_name.push_back("Atomic Popcorn");
    list_name.push_back("Anti-Popcorn");
    
    list_countkey.push_back("paperroute_count");
    list_countkey.push_back("lemon_count");
    list_countkey.push_back("flower_count");
    list_countkey.push_back("coffee_count");
    list_countkey.push_back("fastfood_count");
    list_countkey.push_back("casino_count");
    list_countkey.push_back("cigrate_count");
    list_countkey.push_back("soda_count");
    list_countkey.push_back("railroad_count");
    list_countkey.push_back("strip_count");
    list_countkey.push_back("arctic_count");
    list_countkey.push_back("candytheft_price");
    list_countkey.push_back("oldlady_count");
    list_countkey.push_back("clown_count");
    list_countkey.push_back("nsa_count");
    list_countkey.push_back("dog_count");
    list_countkey.push_back("cat_count");
    list_countkey.push_back("cryogenic_count");
    list_countkey.push_back("banana_count");
    
    list_pricekey.push_back("paperroute_price");
    list_pricekey.push_back("lemon_price");
    list_pricekey.push_back("flower_price");
    list_pricekey.push_back("coffee_price");
    list_pricekey.push_back("fastfood_price");
    list_pricekey.push_back("casino_price");
    list_pricekey.push_back("cigrate_price");
    list_pricekey.push_back("soda_price");
    list_pricekey.push_back("railroad_price");
    list_pricekey.push_back("strip_price");
    list_pricekey.push_back("arctic_price");
    list_pricekey.push_back("candytheft_count");
    list_pricekey.push_back("oldlady_price");
    list_pricekey.push_back("clown_price");
    list_pricekey.push_back("nsa_price");
    list_pricekey.push_back("dog_price");
    list_pricekey.push_back("cat_price");
    list_pricekey.push_back("cryogenic_price");
    list_pricekey.push_back("banana_price");
    
    list_profit1.push_back(".3 Kernels/Click");
    list_profit1.push_back("1.75 Kernels/Click");
    list_profit1.push_back("10 Kernels/Click");
    list_profit1.push_back("60 Kernels/Click");
    list_profit1.push_back("350 Kernels/Click");
    list_profit1.push_back("2.05K Kernels/Click");
    list_profit1.push_back("12K Kernels/Click");
    list_profit1.push_back("70K Kernels/Click");
    list_profit1.push_back("400K Kernels/Click");
    list_profit1.push_back("2.4M Kernels/Click");
    list_profit1.push_back("14M Kernels/Click");
    list_profit1.push_back("80M Kernels/Click");
    list_profit1.push_back("470M Kernels/Click");
    list_profit1.push_back("2.75B Kernels/Click");
    list_profit1.push_back("16B Kernels/Click");
    list_profit1.push_back("93.3B Kernels/Click");
    list_profit1.push_back("544B Kernels/Click");
    list_profit1.push_back("3.2KB Kernels/Click");
    list_profit1.push_back("18.5KB Kernels/Click");
    
    list_profit2.push_back(".5 Kernels/Click");
    list_profit2.push_back("3.25 Kernels/Click");
    list_profit2.push_back("18.75 Kernels/Click");
    list_profit2.push_back("110 Kernels/Click");
    list_profit2.push_back("600 Kernels/Click");
    list_profit2.push_back("3.69K Kernels/Click");
    list_profit2.push_back("22K Kernels/Click");
    list_profit2.push_back("125K Kernels/Click");
    list_profit2.push_back("730K Kernels/Click");
    list_profit2.push_back("4.25M Kernels/Click");
    list_profit2.push_back("25M Kernels/Click");
    list_profit2.push_back("145M Kernels/Click");
    list_profit2.push_back("850M Kernels/Click");
    list_profit2.push_back("4.9B Kernels/Click");
    list_profit2.push_back("28.8B Kernels/Click");
    list_profit2.push_back("168B Kernels/Click");
    list_profit2.push_back("980B Kernels/Click");
    list_profit2.push_back("5.75KB Kernels/Click");
    list_profit2.push_back("33.3KB Kernels/Click");
    
    list_profit3.push_back("1 Kernels/Click");
    list_profit3.push_back("5.75 Kernels/Click");
    list_profit3.push_back("35 Kernels/Click");
    list_profit3.push_back("200 Kernels/Click");
    list_profit3.push_back("1.1K Kernels/Click");
    list_profit3.push_back("6.6K Kernels/Click");
    list_profit3.push_back("38K Kernels/Click");
    list_profit3.push_back("225K Kernels/Click");
    list_profit3.push_back("1.3M Kernels/Click");
    list_profit3.push_back("7.7M Kernels/Click");
    list_profit3.push_back("45M Kernels/Click");
    list_profit3.push_back("260M Kernels/Click");
    list_profit3.push_back("1.5B Kernels/Click");
    list_profit3.push_back("8.9B Kernels/Click");
    list_profit3.push_back("52B Kernels/Click");
    list_profit3.push_back("302B Kernels/Click");
    list_profit3.push_back("1.75KB Kernels/Click");
    list_profit3.push_back("10.2KB Kernels/Click");
    list_profit3.push_back("60KB Kernels/Click");
    
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    list_profit4.push_back("Completed");
    
    
    log("Name Count %ld", list_name.size());
    log("Name Count %ld", list_countkey.size());
    log("Name Count %ld", list_pricekey.size());
    return true;
}

void BusinessLayer::showContent()
{
    auto bg_title = Sprite::create();
    bg_title->setAnchorPoint(Vec2(0, 1));
    bg_title->setTextureRect(Rect(0, 0,G_SWIDTH, CELL_HEIGHT));
    bg_title->setColor(Color3B(235, 13, 57));
    bg_title->setPosition(Vec2(0, this->getContentSize().height));
    this->addChild(bg_title);
    
    Label *lbl_title = Label::createWithTTF("RECIPE INVESTMENTS", "AmericanTypewriter.ttf", G_SWIDTH / 15);
    lbl_title->setPosition(G_SWIDTH / 2, bg_title->getPositionY() - 50 * G_SCALEY);
    this->addChild(lbl_title);
    
    Label *lbl_desc = Label::createWithTTF("Earn More Kernels Per Click", "AmericanTypewriter.ttf", G_SWIDTH / 20);
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

ssize_t BusinessLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return list_name.size();
    
}

TableViewCell* BusinessLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
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
    
    Sprite* spt_item = Sprite::create(StringUtils::format("business%zd.png", idx + 1));
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
    
    Label *lbl_price = Label::createWithTTF(StringUtils::format("%s Kernels", CashManager::getInstance()->ConvertAmountToShortString(price).c_str()),
                                            "AmericanTypewriter.ttf",
                                            G_SWIDTH / 25);
    lbl_price->setWidth(spt_ribb_l->getBoundingBox().size.width * 0.8);
    lbl_price->setAnchorPoint(Vec2(1.0, 0.5));
    lbl_price->setAlignment(TextHAlignment::CENTER);
    lbl_price->setColor(Color3B::BLACK);
    lbl_price->setPosition(spt_ribb_l->getPositionX() - 10 * G_SCALEX, spt_ribb_l->getPositionY());
    cell->addChild(lbl_price);
    
    Label *lbl_profit;
    if (count == 0) {
        lbl_profit = Label::createWithTTF(list_profit1[idx].c_str(), "AmericanTypewriter.ttf", G_SWIDTH / 25);
        
        Label *lbl_shaker = Label::createWithTTF("+1", "AmericanTypewriter.ttf", G_SWIDTH / 25);
        lbl_shaker->setPosition(G_SWIDTH * 0.7, lbl_name->getPositionY());
        cell->addChild(lbl_shaker);
        
        Sprite *spt_shaker = Sprite::create("shaker.png");
        spt_shaker->setScale(G_SCALEM * 0.07);
        spt_shaker->setPosition(lbl_shaker->getPositionX() + lbl_shaker->getBoundingBox().size.width + 60 * G_SCALEX, lbl_shaker->getPositionY());
        cell->addChild(spt_shaker);
    }else if (count == 1){
        lbl_profit = Label::createWithTTF(list_profit2[idx].c_str(), "AmericanTypewriter.ttf", G_SWIDTH / 25);
    }else if (count == 2){
        lbl_profit = Label::createWithTTF(list_profit3[idx].c_str(), "AmericanTypewriter.ttf", G_SWIDTH / 25);
    }else {
        lbl_profit = Label::createWithTTF(list_profit4[idx].c_str(), "AmericanTypewriter.ttf", G_SWIDTH / 25);
    }
    
    lbl_profit->setWidth(spt_ribb_r->getBoundingBox().size.width * 0.8);
    lbl_profit->setAnchorPoint(Vec2(0.0, 0.5));
    lbl_profit->setColor(Color3B::BLACK);
    lbl_profit->setAlignment(TextHAlignment::CENTER);
    lbl_profit->setPosition(spt_ribb_r->getPositionX() - 10 * G_SCALEX, spt_ribb_r->getPositionY());
    cell->addChild(lbl_profit);
    
    return cell;
}

Size BusinessLayer::cellSizeForTable(TableView *table)
{
    return Size(G_SWIDTH, CELL_HEIGHT);
}

void BusinessLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
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
    
    if (count < 3) {
        if (index > 0) {
            if (userdefault->getIntegerForKey(list_countkey[index - 1].c_str()) < 3) {
                MessageBox("Upgrade the previous investment completely to purchase this one.", "");
                return;
            }
        }
        if (currentCash < price) {
            MessageBox("Not Enough Kernels", "");
            return;
        }else
        {
            cashmanager->setCurrentCash(currentCash - price);
            userdefault->setFloatForKey(list_pricekey[cell->getIdx()].c_str(), price * 1.8);
            if (count == 0) {
                cashmanager->setCurrentShaker(currentShaker + 1);
            }
        }
        userdefault->setIntegerForKey(list_countkey[cell->getIdx()].c_str(), count + 1);
    }
    
    cashmanager->reloadCashPerSecondAndCashPerSwap();
    table->reloadData();
    
}
