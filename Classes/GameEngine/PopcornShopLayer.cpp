//
//  PopcornShopLayer.cpp
//  Popcorn
//
//  Created by Monkey on 8/3/16.
//
//

#include "PopcornShopLayer.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "GameScene.hpp"

#define CELL_HEIGHT     250 * G_SCALEY

Scene* PopcornShopLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PopcornShopLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool PopcornShopLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(242, 42, 73, 255))) {
        return false;
    }
    
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmanager = CashManager::getInstance();
    
    IAP::setListener(this);
//    IAP::setDebug(true);
//    IAP::refresh();
    
    list_name.push_back("Shaker of Salt");
    list_name.push_back("Salt Mine");
    list_name.push_back("Classic");
    list_name.push_back("Moustache");
    list_name.push_back("Glasses 1");
    list_name.push_back("Glasses 2");
    list_name.push_back("Glasses 3");
    list_name.push_back("Moustache + Glasses 1");
    list_name.push_back("Moustache + Glasses 2");
    list_name.push_back("Moustache + Glasses 3");
    list_name.push_back("Chef Hat");
    list_name.push_back("Chef Hat + Moustache");
    list_name.push_back("Chef Hat + Glasses 1");
    list_name.push_back("Chef Hat + Glasses 2");
    list_name.push_back("Chef Hat + Glasses 3");
    list_name.push_back("Chef Hat + Moustache + Glasses 1");
    list_name.push_back("Chef Hat + Moustache + Glasses 2");
    list_name.push_back("Chef Hat + Moustache + Glasses 3");
    list_name.push_back("Top Hat");
    list_name.push_back("Top Hat + Moustache");
    list_name.push_back("Top Hat + Glasses 1");
    list_name.push_back("Top Hat + Glasses 2");
    list_name.push_back("Top Hat + Glasses 3");
    list_name.push_back("Top Hat + Moustache + Glasses 1");
    list_name.push_back("Top Hat + Moustache + Glasses 2");
    list_name.push_back("Top Hat + Moustache + Glasses 3");
    list_name.push_back("Disguise");
    list_name.push_back("Chef Hat + Disguise");
    list_name.push_back("Top Hat + Disguise");
    list_name.push_back("Top Hat + Moustache + Monocle");
    
    std::vector<Product> products = sdkbox::IAP::getProducts();
    string price_saltshaker;
    string price_saltmine;
    for (int i = 0; i < products.size(); i++) {
        
        if (products[i].name == "Shaker of Salt") {
            price_saltshaker = products[i].price;
        }else if (products[i].name == "Salt Mine")
        {
            price_saltmine = products[i].price;
        }
    }
    
    list_price.push_back(price_saltshaker);
    list_price.push_back(price_saltmine);
    list_price.push_back("");
    string price_key = "";
    float price;
    for (int i = 1; i < 28; i++) {
        price_key = StringUtils::format("p%d_price", i);
        price = userdefault->getFloatForKey(price_key.c_str());
        list_price.push_back(cashmanager->ConvertAmountToShortString(price));
    }
    
    return true;
}

void PopcornShopLayer::showContent()
{
    auto bg_title = Sprite::create();
    bg_title->setAnchorPoint(Vec2(0, 1));
    bg_title->setTextureRect(Rect(0, 0, G_SWIDTH, 200 * G_SCALEY));
    bg_title->setColor(Color3B(235, 13, 57));
    bg_title->setPosition(Vec2(0, this->getContentSize().height));
    this->addChild(bg_title);
    
    Label *lbl_title = Label::createWithTTF("SHOP", "AmericanTypewriter.ttf", G_SWIDTH / 15);
    lbl_title->setPosition(G_SWIDTH / 2, bg_title->getPositionY() - 50 * G_SCALEY);
    this->addChild(lbl_title);
    
    Label *lbl_desc = Label::createWithTTF("Customize Your Kernels", "AmericanTypewriter.ttf", G_SWIDTH / 20);
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
    
    Sprite *spt_shaker = Sprite::create("shaker.png");
    spt_shaker->setScale(G_SCALEM * 0.07);
    spt_shaker->setPosition(G_SWIDTH / 2 - 10 * G_SCALEX, lbl_desc->getPositionY() - lbl_desc->getBoundingBox().size.height - spt_shaker->getBoundingBox().size.height / 2);
    spt_shaker->setAnchorPoint(Vec2(1.0, 0.5));
    this->addChild(spt_shaker);
    
    Sprite *spt_line = Sprite::create();
    spt_line->setAnchorPoint(Vec2(0, 0));
    spt_line->setTextureRect(Rect(0, 0, G_SWIDTH, 5 * G_SCALEY));
    spt_line->setColor(Color3B::WHITE);
    spt_line->setPosition(0, bg_title->getPositionY() - bg_title->getBoundingBox().size.height - spt_line->getBoundingBox().size.height);
    this->addChild(spt_line, 10);
    
    int shakers = CashManager::getInstance()->getCurrentShaker();
    m_lbl_shaker = Label::createWithTTF(StringUtils::format("%d", shakers), "AmericanTypewriter.ttf", G_SWIDTH / 20);
    m_lbl_shaker->setPosition(G_SWIDTH / 2 + 10 * G_SCALEX, spt_shaker->getPositionY());
    m_lbl_shaker->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(m_lbl_shaker);
    
    m_tableview = TableView::create(this, Size(G_SWIDTH, this->getContentSize().height - bg_title->getContentSize().height));
    m_tableview->setDirection(TableView::Direction::VERTICAL);
    m_tableview->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_tableview->setAnchorPoint(Vec2(0.5, 0.5));
    m_tableview->setDelegate(this);
    m_tableview->setPosition(Vec2(0, 0));
    m_tableview->setColor(Color3B(242, 42, 73));
    this->addChild(m_tableview);
}

ssize_t PopcornShopLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return list_name.size();
}

TableViewCell* PopcornShopLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    
    TableViewCell* cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmananger =  CashManager::getInstance();
    float cash = cashmananger->getCurrentCash();
    
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
    
    Sprite* spt_item = Sprite::create();
    if (spt_item != nullptr) {
        spt_item->setAnchorPoint(Vec2(0, 0.5));
        spt_item->setScale(G_SCALEM * 0.7);
        spt_item->setPosition(5 * G_SCALEX, CELL_HEIGHT * 0.6);
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
    
    Label *lbl_product = Label::createWithTTF(list_name[idx], "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_product->setWidth(spt_ribb_l->getBoundingBox().size.width * 0.8);
    lbl_product->setAnchorPoint(Vec2(1.0, 0.5));
    lbl_product->setAlignment(TextHAlignment::CENTER);
    lbl_product->setColor(Color3B::BLACK);
    lbl_product->setPosition(spt_ribb_l->getPositionX() - 10 * G_SCALEX, spt_ribb_l->getPositionY());
    cell->addChild(lbl_product);
    
    Label *lbl_price = Label::createWithTTF(list_price[idx], "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_price->setWidth(spt_ribb_r->getBoundingBox().size.width * 0.8);
    lbl_price->setAnchorPoint(Vec2(0.0, 0.5));
    lbl_price->setAlignment(TextHAlignment::CENTER);
    lbl_price->setColor(Color3B::BLACK);
    lbl_price->setPosition(spt_ribb_r->getPositionX() - 10 * G_SCALEX, spt_ribb_r->getPositionY());
    cell->addChild(lbl_price);
    
    Label *lbl_desc = Label::createWithTTF("", "AmericanTypewriter.ttf", G_SWIDTH / 30);
    lbl_desc->setPosition(spt_ribb_l->getPositionX() - spt_ribb_l->getBoundingBox().size.width, spt_ribb_l->getPositionY()   - spt_ribb_l->getBoundingBox().size.height / 2 - 25 * G_SCALEY);
    lbl_desc->setAnchorPoint(Vec2(0, 0.5));
    cell->addChild(lbl_desc);
    
    Sprite *spt_shaker = Sprite::create("shaker.png");
    spt_shaker->setScale(G_SCALEM * 0.07);
    spt_shaker->setPosition(spt_ribb_r->getPositionX() + spt_ribb_r->getBoundingBox().size.width - 150 * G_SCALEX, spt_ribb_r->getPositionY());
    cell->addChild(spt_shaker);
    
    if (idx == 0) {
        lbl_desc->setString("Get 25 Shakers Instantly");
        spt_item->setTexture("squareShaker.png");
        spt_shaker->setVisible(false);
    }else if (idx == 1)
    {
        lbl_desc->setString("Get 150 Shakers Instantly");
        spt_item->setTexture("salt mine.png");
        spt_shaker->setVisible(false);
    }else
    {
        if (idx == 2) {
            spt_shaker->setVisible(false);
        }
        lbl_desc->setString("");
        spt_item->setTexture(StringUtils::format("popcorn_%ld.png", idx - 2));
    }
    
    return cell;
}

Size PopcornShopLayer::cellSizeForTable(TableView *table)
{
    return Size(G_SWIDTH, CELL_HEIGHT);
}

void PopcornShopLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    log(" %zd Cell Clicked", cell->getIdx());
    
    SimpleAudioEngine::getInstance()->playEffect("click.mp3");
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmanager = CashManager::getInstance();
    
    int index = (int)cell->getIdx();
    if (index == 0) {
        // In-App Purchase
    }else if (index == 1)
    {
        // In-App Purchase
    }else if (index == 2)
    {
        userdefault->setIntegerForKey("CustomPopcorn", 0);
    }else
    {
        
        if (!userdefault->getBoolForKey(StringUtils::format("p%d", index - 2).c_str()) && index > 3) {
            MessageBox("Purchase the previous upgrade to purchase this one.", "");
            return;
        }
        
        string key_price = StringUtils::format("p%d_price", index - 2);
        float price = userdefault->getFloatForKey(key_price.c_str());
        float currentShaker = cashmanager->getCurrentShaker();
        
        if (price > currentShaker) {
            MessageBox("Not Enough Shakers", "");
        }else
        {
            currentShaker -= price;
            cashmanager->setCurrentShaker(currentShaker);
            userdefault->setIntegerForKey(key_price.c_str(), 0);
            userdefault->setIntegerForKey("CustomPopcorn", index - 2);
            m_lbl_shaker->setString(StringUtils::format("%d", (int)currentShaker));
            userdefault->setBoolForKey(StringUtils::format("p%d", index - 2).c_str(), true);
        }
    }
    cashmanager->reloadCashPerSecondAndCashPerSwap();
}

void PopcornShopLayer::onInitialized(bool ok)
{
    log("%s", ok?"IAP >>> Initialized":"IAP >>> Initialize Failed");
}

void PopcornShopLayer::onSuccess(sdkbox::Product const& p)
{
    log("IAP >>> Purchase Succesed: %s", p.name.c_str());
    
    CashManager *cashmanager = CashManager::getInstance();
    
    float currentshaker = cashmanager->getCurrentShaker();
    if (p.name == "Shaker of Salt") {
        cashmanager->setCurrentShaker(currentshaker + 25);
        currentshaker = cashmanager->getCurrentShaker();
        m_lbl_shaker->setString(StringUtils::format("%d", (int)currentshaker));
    }
    
    if (p.name == "Salt Mine") {
        cashmanager->setCurrentShaker(currentshaker + 150);
        currentshaker = cashmanager->getCurrentShaker();
        m_lbl_shaker->setString(StringUtils::format("%d", (int)currentshaker));
    }
}

void PopcornShopLayer::onFailure(sdkbox::Product const& p, const std::string &msg)
{
    log("IAP >>> Purchase Failed: %s", p.name.c_str());
}

void PopcornShopLayer::onCanceled(sdkbox::Product const& p)
{
    log("IAP >>> Purchase Canceled: %s", p.name.c_str());
}

void PopcornShopLayer::onRestored(sdkbox::Product const& p)
{
    log("IAP >>> Purchase Restored: %s", p.name.c_str());
}

void PopcornShopLayer::onProductRequestSuccess(std::vector<sdkbox::Product> const &products)
{
    log("IAP >>> ProductRequest Success >> count : %lu", products.size());
}

void PopcornShopLayer::onProductRequestFailure(const std::string &msg)
{
    log("IAP >>> ProductRequest Failed >> message : %s", msg.c_str());
}

void PopcornShopLayer::onRestoreComplete(bool ok, const std::string &msg)
{
    
}
