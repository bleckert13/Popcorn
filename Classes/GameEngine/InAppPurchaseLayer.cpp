//
//  InAppPurchaseLayer.cpp
//  Popcorn
//
//  Created by Hans on 8/1/16.
//
//

#include "InAppPurchaseLayer.hpp"
#include "InAppPurchaseLayer.hpp"
#include "Constants.h"
#include "CashManager.hpp"
#include "GameScene.hpp"

#define CELL_HEIGHT     250 * G_SCALEY

Scene* InAppPurchaseLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InAppPurchaseLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool InAppPurchaseLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(242, 42, 73, 255))) {
        return false;
    }
    
    IAP::setListener(this);
    IAP::setDebug(true);
    IAP::refresh();
    
    UserDefault *userdefault = UserDefault::getInstance();
    
    list_iapname.push_back("Kernel Blast");
    list_iapname.push_back("Kernel Bomb");
    list_iapname.push_back("Double Kernels Per Second");
    list_iapname.push_back("Double Kernels");
    list_iapname.push_back("Forever 20x");
    list_iapname.push_back("Remove Ads");
    list_iapname.push_back("Kernel Sale");
    list_iapname.push_back("King Kernel");
    list_iapname.push_back("Treadmill");
    
    log("Name Count %ld", list_name.size());
    log("Name Count %ld", list_countkey.size());
    log("Name Count %ld", list_description.size());
    return true;
}

void InAppPurchaseLayer::showContent()
{
    auto bg_title = Sprite::create();
    bg_title->setAnchorPoint(Vec2(0, 1));
    bg_title->setTextureRect(Rect(0, 0,G_SWIDTH, 150 * G_SCALEY));
    bg_title->setColor(Color3B(235, 13, 57));
    bg_title->setPosition(Vec2(0, this->getContentSize().height));
    this->addChild(bg_title);
    
    Label *lbl_title = Label::createWithTTF("STORE", "AmericanTypewriter.ttf", G_SWIDTH / 15);
    lbl_title->setPosition(G_SWIDTH / 2, bg_title->getPositionY() - 50 * G_SCALEY);
    this->addChild(lbl_title);
    
    Label *lbl_desc = Label::createWithTTF("Supercharge Your Kernels", "AmericanTypewriter.ttf", G_SWIDTH / 20);
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
    
    m_tableview = TableView::create(this, Size(G_SWIDTH, this->getContentSize().height - bg_title->getContentSize().height));
    m_tableview->setDirection(TableView::Direction::VERTICAL);
    m_tableview->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_tableview->setAnchorPoint(Vec2(0.5, 0.5));
    m_tableview->setDelegate(this);
    m_tableview->setPosition(Vec2(0, 0));
    m_tableview->setColor(Color3B(242, 42, 73));
    this->addChild(m_tableview);
}

ssize_t InAppPurchaseLayer::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 34;
}

TableViewCell* InAppPurchaseLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell* cell = table->dequeueCell();
    cell = new TableViewCell();
    cell->autorelease();
    
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmananger =  CashManager::getInstance();
    float cash = cashmananger->getCurrentCash();
    
    chefhat_price = userdefault->getFloatForKey("chefhat_price");
    upiggybank_price = userdefault->getFloatForKey("Upiggybank_price");
    moon_price = userdefault->getFloatForKey("moon_price");
    earth_price = userdefault->getFloatForKey("earth_price");
    spaceship_price = userdefault->getFloatForKey("spaceship_price");
    ufo_price = userdefault->getFloatForKey("ufo_price");
    dinnerplate_price = userdefault->getFloatForKey("dinnerplate_price");
    trophycup_price = userdefault->getFloatForKey("trophycup_price");
    car_price = userdefault->getFloatForKey("car_price");
    umbrella_price = userdefault->getFloatForKey("umbrella_price");
    diamond_price = userdefault->getFloatForKey("diamond_price");
    prestige_price = userdefault->getFloatForKey("prestige_price");
    ocean_price = userdefault->getFloatForKey("ocean_price");
    city_price = userdefault->getFloatForKey("city_price");
    sky_price = userdefault->getFloatForKey("sky_price");
    universe_price = userdefault->getFloatForKey("universe_price");
    jungle_price = userdefault->getFloatForKey("jungle_price");
    desert_price = userdefault->getFloatForKey("desert_price");
    beach_price = userdefault->getFloatForKey("beach_price");
    prestige_count = userdefault->getIntegerForKey("prestige_count");
    
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
    
    Label *lbl_product = Label::createWithTTF("", "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_product->setWidth(spt_ribb_l->getBoundingBox().size.width * 0.8);
    lbl_product->setAnchorPoint(Vec2(1.0, 0.5));
    lbl_product->setAlignment(TextHAlignment::CENTER);
    lbl_product->setColor(Color3B::BLACK);
    lbl_product->setPosition(spt_ribb_l->getPositionX() - 10 * G_SCALEX, spt_ribb_l->getPositionY());
    cell->addChild(lbl_product);
    
    Label *lbl_price = Label::createWithTTF("", "AmericanTypewriter.ttf", G_SWIDTH / 25);
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
    
    Label *lbl_shaker = Label::createWithTTF("+1", "AmericanTypewriter.ttf", G_SWIDTH / 25);
    lbl_shaker->setPosition(G_SWIDTH * 0.7, 25 * G_SCALEY);
    lbl_shaker->setVisible(false);
    cell->addChild(lbl_shaker);
    
    Sprite *spt_shaker = Sprite::create("shaker.png");
    spt_shaker->setScale(G_SCALEM * 0.07);
    spt_shaker->setPosition(lbl_shaker->getPositionX() + lbl_shaker->getBoundingBox().size.width + 60 * G_SCALEX, lbl_shaker->getPositionY());
    spt_shaker->setVisible(false);
    cell->addChild(spt_shaker);
    
    std::vector<Product> products = sdkbox::IAP::getProducts();
    string price;
    
    switch (idx) {
        case 0:
            spt_item->setTexture("iap_reviewstar.png");
            lbl_desc->setString("");
            if (userdefault->getBoolForKey("Reviewed")) {
                lbl_product->setString("Have a suggestion?");
                lbl_price->setString("We'd love to hear");
                lbl_desc->setString(T_EMAIL_ADDRESS);
            }else
            {
                lbl_product->setString("Write a Review");
                lbl_price->setString("Leave a Review for a Bonus");
                lbl_desc->setString("+15% Kernel Boost");
                lbl_shaker->setVisible(true);
                spt_shaker->setVisible(true);
            }
            break;
        case 1:
            spt_item->setTexture("iap_facebook.png");
            lbl_desc->setString("");
            lbl_product->setString("Facebook");
            lbl_price->setString("Share");
            if (!userdefault->getBoolForKey("facebook")) {
                lbl_desc->setString("+15% Kernel Boost");
                lbl_shaker->setVisible(true);
                spt_shaker->setVisible(true);
            }
            break;
        case 2:
            spt_item->setTexture("iap_twitter.png");
            lbl_desc->setString("");
            lbl_product->setString("Twitter");
            lbl_price->setString("Share");
            if (!userdefault->getBoolForKey("twitter")) {
                lbl_desc->setString("+15% Kernel Boost");
                lbl_shaker->setVisible(true);
                spt_shaker->setVisible(true);
            }
            break;
        case 3:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Kernel Blast");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);
            
            lbl_desc->setString(StringUtils::format("Get %s Kernels Instantly", cashmananger->convertAmountToShortString(cash * 100).c_str()));
            if (cash < 600) {
                lbl_desc->setString("Get 1000 Kernels Instantly");
            }
            spt_shaker->setVisible(true);
            lbl_shaker->setVisible(true);
            break;
        case 4:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Kernel Bomb");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);
            
            lbl_desc->setString(StringUtils::format("Get %s Kernels Instantly", cashmananger->convertAmountToShortString(cash * 100).c_str()));
            if (cash < 1000) {
                lbl_desc->setString("Get 20K Kernels Instantly");
            }
            spt_shaker->setVisible(true);
            lbl_shaker->setVisible(true);
            break;
        case 5:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Double Kernels/Sec");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);
            
            spt_shaker->setVisible(true);
            lbl_shaker->setVisible(true);
            break;
        case 6:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Double Kernels");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);

            spt_shaker->setVisible(true);
            lbl_shaker->setVisible(true);
            break;
        case 7:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Forever 20x");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);

            lbl_desc->setString("Get 20x Kernels Per Click");
            if (!userdefault->getBoolForKey("Forever20")) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 8:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Remove Ads");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);

            if (!userdefault->getBoolForKey("RemoveAds")) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 9:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Kernel Sale");
            
            for (int i = 0; i < products.size(); i++) {
                
                if (products[i].name == list_iapname[idx - 3]) {
                    price = products[i].price;
                }
            }
            lbl_price->setString(price);
            
            lbl_desc->setString("All Investments Are Half Price");
            if (!userdefault->getBoolForKey("RemoveAds")) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 10:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("King Kernel");
            lbl_desc->setString("Earn bonuses the faster you tap");
            if (!userdefault->getBoolForKey("KingKernelPurchased")) {
                
                for (int i = 0; i < products.size(); i++) {
                    
                    if (products[i].name == list_iapname[idx - 3]) {
                        price = products[i].price;
                    }
                }
                lbl_price->setString(price);
                
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 11:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Treadmill");
            lbl_desc->setString("Scrolling background moves as you click");
            if (!userdefault->getBoolForKey("TreadmillPurchased")) {
                
                for (int i = 0; i < products.size(); i++) {
                    
                    if (products[i].name == list_iapname[idx - 3]) {
                        price = products[i].price;
                    }
                }
                lbl_price->setString(price);
                
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }else
            {
                if (userdefault->getBoolForKey("Treadmill")) {
                    lbl_price->setString("Enabled");
                }else
                {
                    lbl_price->setString("Disabled");
                }
            }
            break;
        case 12:
            spt_item->setTexture("iap_clump.png");
            lbl_product->setString("Restore");
            lbl_price->setString("");
            break;
        case 13:
            spt_item->setTexture("iap_flatpopcornbox.png");
            lbl_product->setString("Classic Box");
            break;
        case 14:
            spt_item->setTexture("iap_hat.png");
            lbl_product->setString("Chef Hat");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(chefhat_price).c_str()));
            if (chefhat_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 15:
            spt_item->setTexture("iap_goldpiggy.png");
            lbl_product->setString("Piggy Bank");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(upiggybank_price).c_str()));
            if (upiggybank_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 16:
            spt_item->setTexture("iap_moon.png");
            lbl_product->setString("Moon");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(moon_price).c_str()));
            if (moon_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 17:
            spt_item->setTexture("iap_earth.png");
            lbl_product->setString("Earth");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(earth_price).c_str()));
            if (earth_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 18:
            spt_item->setTexture("iap_spaceship.png");
            lbl_product->setString("Spaceship");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(spaceship_price).c_str()));
            if (spaceship_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 19:
            spt_item->setTexture("iap_ufo.png");
            lbl_product->setString("UFO");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(ufo_price).c_str()));
            if (ufo_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 20:
            spt_item->setTexture("iap_tray.png");
            lbl_product->setString("Dinner Plate");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(dinnerplate_price).c_str()));
            if (dinnerplate_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 21:
            spt_item->setTexture("iap_trophy.png");
            lbl_product->setString("Trophy Cup");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(trophycup_price).c_str()));
            if (trophycup_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 22:
            spt_item->setTexture("iap_car.png");
            lbl_product->setString("Car");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(car_price).c_str()));
            if (car_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 23:
            spt_item->setTexture("iap_umbrella.png");
            lbl_product->setString("Umbrella");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(umbrella_price).c_str()));
            if (umbrella_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 24:
            spt_item->setTexture("iap_diamond.png");
            lbl_product->setString("Diamond");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(diamond_price).c_str()));
            if (diamond_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 25:
            spt_item->setTexture("iap_presteige.png");
            lbl_product->setString("Prestige");
            lbl_price->setString(StringUtils::format("%s Kernels", cashmananger->convertAmountToShortString(prestige_price).c_str()));
/////////////
            lbl_desc->setString("(Resets Kernels and Investments)");
            if (prestige_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 26:
            spt_item->setTexture("iap_blue.png");
            lbl_product->setString("Classic Blue");
            lbl_price->setString("");
            if (prestige_price != 0) {
                spt_shaker->setVisible(true);
                lbl_shaker->setVisible(true);
            }
            break;
        case 27:
            spt_item->setTexture("iap_ocean.png");
            lbl_product->setString("Ocean");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 1) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(ocean_price).c_str()));
            }
            break;
        case 28:
            spt_item->setTexture("iap_city.png");
            lbl_product->setString("City");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 2) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(city_price).c_str()));
            }
            break;
        case 29:
            spt_item->setTexture("iap_sky.png");
            lbl_product->setString("Sky");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 3) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(sky_price).c_str()));
            }
            break;
        case 30:
            spt_item->setTexture("iap_universe.png");
            lbl_product->setString("Universe");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 4) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(universe_price).c_str()));
            }
            break;
        case 31:
            spt_item->setTexture("iap_jungle.png");
            lbl_product->setString("Jungle");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 5) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(jungle_price).c_str()));
            }
            break;
        case 32:
            spt_item->setTexture("iap_desert.png");
            lbl_product->setString("Desert");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 6) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(desert_price).c_str()));
            }
            break;
        case 33:
            spt_item->setTexture("iap_beach.png");
            lbl_product->setString("Beach");
            lbl_desc->setString("Scrolling Panoramic Background");
            
            if (prestige_count >= 7) {
                lbl_price->setString("");
            }else
            {
                lbl_price->setString(StringUtils::format("Unlock at Prestige Level %s", cashmananger->convertAmountToShortString(beach_price).c_str()));
            }
            break;
        default:
            break;
    }
    
    return cell;
}

Size InAppPurchaseLayer::cellSizeForTable(TableView *table)
{
    return Size(G_SWIDTH, CELL_HEIGHT);
}

void InAppPurchaseLayer::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    log(" %zd Cell Clicked", cell->getIdx());
    
    UserDefault* userdefault = UserDefault::getInstance();
    CashManager* cashmanager = CashManager::getInstance();
    SimpleAudioEngine::getInstance()->playEffect("click.mp3");
    
    int index = (int)cell->getIdx();
    float currentShaker = cashmanager->getCurrentShaker();
    float currentCash = cashmanager->getCurrentCash();
    int prestigeCount = userdefault->getIntegerForKey("prestige_count");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo t;
#endif

    string shareString = StringUtils::format("I've popped %s kernels in Kernel King. Bet you can't pop more! Try to beat me: http://apple.co/1Th8VFr #KernelKing", cashmanager->convertAmountToShortString(currentCash).c_str());
    
    sdkbox::Product p;
    
    switch (index) {
        case 0:
            if (userdefault->getBoolForKey("Reviewed")) {
                // Send Email
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                
#else
                if (JniHelper::getStaticMethodInfo(t
                                                   , "org/cocos2dx/cpp/AppActivity"
                                                   , "sendemail"
                                                   , "(Ljava/lang/String;)V"))
                {
                    jstring StringArg1 = t.env->NewStringUTF("");
                    t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
                }
#endif
            }else
            {
                // Open Itunes
                cashmanager->setCurrentShaker(currentShaker + 1);
                cashmanager->setCurrentCash(currentCash * 0.15 + currentCash);
                userdefault->setBoolForKey("Reviewed", true);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                
#else
                if (JniHelper::getStaticMethodInfo(t
                                                   , "org/cocos2dx/cpp/AppActivity"
                                                   , "openAppRate"
                                                   , "(Ljava/lang/String;)V"))
                {
                    jstring StringArg1 = t.env->NewStringUTF("");
                    t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
                }
#endif
            }
            break;
        case 1:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        
#else
            if (JniHelper::getStaticMethodInfo(t,
                                               "org/cocos2dx/cpp/AppActivity",
                                               "shareFacebook"
                                           , "(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(shareString.c_str());
            t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
        }
#endif
            if (!userdefault->getBoolForKey("facebook"))
            {
                cashmanager->setCurrentShaker(currentShaker + 1);
                userdefault->setBoolForKey("facebook", true);
            }
            break;
        case 2:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        
#else
        if (JniHelper::getStaticMethodInfo(t
                                           , "org/cocos2dx/cpp/AppActivity"
                                           , "shareTwitter"
                                           , "(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(shareString.c_str());
            t.env->CallStaticVoidMethod(t.classID, t.methodID, StringArg1);
        }
#endif
            if (!userdefault->getBoolForKey("twitter"))
            {
                cashmanager->setCurrentShaker(currentShaker + 1);
                userdefault->setBoolForKey("twitter", true);
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            // In-App Purchase
            IAP::purchase(list_iapname[index - 3]);
            break;
        case 10:
            if (userdefault->getBoolForKey("KingKernelPurchased")) {
                userdefault->setBoolForKey("classicbox", false);
                userdefault->setBoolForKey("chefhat", false);
                userdefault->setBoolForKey("Upiggbank", false);
                userdefault->setBoolForKey("moon", false);
                userdefault->setBoolForKey("earth", false);
                userdefault->setBoolForKey("spaceship", false);
                userdefault->setBoolForKey("ufo", false);
                userdefault->setBoolForKey("dinnerplate", false);
                userdefault->setBoolForKey("trophycup", false);
                userdefault->setBoolForKey("car", false);
                userdefault->setBoolForKey("umbrella", false);
                userdefault->setBoolForKey("diamond", false);
                userdefault->setBoolForKey("prestige", false);
                userdefault->setBoolForKey("KingKernel", true);
            }else
            {
                // In-App Purchase
                IAP::purchase(list_iapname[index - 3]);
            }
            break;
        case 11:
            if (userdefault->getBoolForKey("TreadmillPurchased")) {
                if (userdefault->getBoolForKey("Treadmill")) {
                    userdefault->setBoolForKey("Treadmill", false);
                    userdefault->setBoolForKey("NewCustomBG", true);
                }else
                {
                    userdefault->setBoolForKey("Treadmill", true);
                    userdefault->setBoolForKey("NewCustomBG", true);
                }
            }else
            {
                // In-App Purchase
                IAP::purchase(list_iapname[index - 3]);
            }
            break;
        case 12:
            // In-App Purchase
            IAP::restore();
            break;
        case 13:
            userdefault->setBoolForKey("classicbox", true);
            userdefault->setBoolForKey("chefhat", false);
            userdefault->setBoolForKey("Upiggbank", false);
            userdefault->setBoolForKey("moon", false);
            userdefault->setBoolForKey("earth", false);
            userdefault->setBoolForKey("spaceship", false);
            userdefault->setBoolForKey("ufo", false);
            userdefault->setBoolForKey("dinnerplate", false);
            userdefault->setBoolForKey("trophycup", false);
            userdefault->setBoolForKey("car", false);
            userdefault->setBoolForKey("umbrella", false);
            userdefault->setBoolForKey("diamond", false);
            userdefault->setBoolForKey("prestige", false);
            userdefault->setBoolForKey("KingKernel", false);
            break;
        case 14:
            if (userdefault->getFloatForKey("chefhat_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("chefhat_price"));
                if (userdefault->getFloatForKey("chefhat_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("chefhat_price", 0);
                
                userdefault->setBoolForKey("chefhat", true);
                userdefault->setBoolForKey("classicbox", false);
                userdefault->setBoolForKey("Upiggbank", false);
                userdefault->setBoolForKey("moon", false);
                userdefault->setBoolForKey("earth", false);
                userdefault->setBoolForKey("spaceship", false);
                userdefault->setBoolForKey("ufo", false);
                userdefault->setBoolForKey("dinnerplate", false);
                userdefault->setBoolForKey("trophycup", false);
                userdefault->setBoolForKey("car", false);
                userdefault->setBoolForKey("umbrella", false);
                userdefault->setBoolForKey("diamond", false);
                userdefault->setBoolForKey("prestige", false);
                userdefault->setBoolForKey("KingKernel", false);
            }
            break;
        case 15:
            if (userdefault->getFloatForKey("Upiggybank_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("Upiggybank_price"));
                if (userdefault->getFloatForKey("Upiggybank_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("Upiggybank_price", 0);
                
                userdefault->setBoolForKey("chefhat", false);
                userdefault->setBoolForKey("classicbox", false);
                userdefault->setBoolForKey("Upiggbank", true);
                userdefault->setBoolForKey("moon", false);
                userdefault->setBoolForKey("earth", false);
                userdefault->setBoolForKey("spaceship", false);
                userdefault->setBoolForKey("ufo", false);
                userdefault->setBoolForKey("dinnerplate", false);
                userdefault->setBoolForKey("trophycup", false);
                userdefault->setBoolForKey("car", false);
                userdefault->setBoolForKey("umbrella", false);
                userdefault->setBoolForKey("diamond", false);
                userdefault->setBoolForKey("prestige", false);
                userdefault->setBoolForKey("KingKernel", false);
            }
            break;
        case 16:
            if (userdefault->getFloatForKey("moon_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("moon_price"));
                if (userdefault->getFloatForKey("moon_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("moon_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          true);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 17:
            if (userdefault->getFloatForKey("earth_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("earth_price"));
                if (userdefault->getFloatForKey("earth_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("earth_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         true);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 18:
            if (userdefault->getFloatForKey("spaceship_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("spaceship_price"));
                if (userdefault->getFloatForKey("spaceship_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("spaceship_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     true);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 19:
            if (userdefault->getFloatForKey("ufo_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("ufo_price"));
                if (userdefault->getFloatForKey("ufo_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("ufo_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           true);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 20:
            if (userdefault->getFloatForKey("dinnerplate_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("dinnerplate_price"));
                if (userdefault->getFloatForKey("dinnerplate_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("dinnerplate_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   true);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 21:
            if (userdefault->getFloatForKey("trophycup_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("trophycup_price"));
                if (userdefault->getFloatForKey("trophycup_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("trophycup_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     true);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 22:
            if (userdefault->getFloatForKey("car_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("car_price"));
                if (userdefault->getFloatForKey("car_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("car_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           true);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 23:
            if (userdefault->getFloatForKey("umbrella_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("umbrella_price"));
                if (userdefault->getFloatForKey("umbrella_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("umbrella_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      true);
                userdefault->setBoolForKey("diamond",       false);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 24:
            if (userdefault->getFloatForKey("diamond_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                cashmanager->setCurrentCash(currentCash - userdefault->getFloatForKey("diamond_price"));
                if (userdefault->getFloatForKey("diamond_price") != 0) {
                    cashmanager->setCurrentShaker(currentShaker + 1);
                }
                userdefault->setFloatForKey("diamond_price", 0);
                
                userdefault->setBoolForKey("chefhat",       false);
                userdefault->setBoolForKey("classicbox",    false);
                userdefault->setBoolForKey("Upiggbank",     false);
                userdefault->setBoolForKey("moon",          false);
                userdefault->setBoolForKey("earth",         false);
                userdefault->setBoolForKey("spaceship",     false);
                userdefault->setBoolForKey("ufo",           false);
                userdefault->setBoolForKey("dinnerplate",   false);
                userdefault->setBoolForKey("trophycup",     false);
                userdefault->setBoolForKey("car",           false);
                userdefault->setBoolForKey("umbrella",      false);
                userdefault->setBoolForKey("diamond",       true);
                userdefault->setBoolForKey("prestige",      false);
                userdefault->setBoolForKey("KingKernel",    false);
            }
            break;
        case 25:
            if (userdefault->getFloatForKey("prestige_price") > currentCash) {
                MessageBox("Not Enough Kernels", "");
            }else
            {
                userdefault->setBoolForKey("RibbonShown", true);
                cashmanager->setCurrentShaker(0);
                cashmanager->setCurrentCash(0);
                cashmanager->setCashPerHour(0);
                cashmanager->setCashPerScecond(0);
                cashmanager->setBucketSize(0);
                cashmanager->setCurrentBucket(0);
                cashmanager->setCashPerSwap(1.0f);
            }
            
            userdefault->setIntegerForKey("prestige_count", userdefault->getIntegerForKey("prestige_count") + 1);
            userdefault->setIntegerForKey("prestigemultiplier_count", userdefault->getIntegerForKey("prestigemultiplier_count") + 1);
            
            userdefault->setIntegerForKey("piggybank_count", 0);
            userdefault->setIntegerForKey("mattress_count", 0);
            userdefault->setIntegerForKey("comicbook_count", 0);
            userdefault->setIntegerForKey("savingaccount_count", 0);
            userdefault->setIntegerForKey("bitcoinaccount_count", 0);
            userdefault->setIntegerForKey("stockes_count", 0);
            userdefault->setIntegerForKey("bookie_count", 0);
            userdefault->setIntegerForKey("loanshark_count", 0);
            userdefault->setIntegerForKey("angelinvestment_count", 0);
            userdefault->setIntegerForKey("vanturecapital_count", 0);
            userdefault->setIntegerForKey("porkbelly_count", 0);
            userdefault->setIntegerForKey("hedgefund_count", 0);
            userdefault->setIntegerForKey("investmentbank_count", 0);
            userdefault->setIntegerForKey("insidertrading_count", 0);
            userdefault->setIntegerForKey("mortgage_count", 0);
            userdefault->setIntegerForKey("pyramid_count", 0);
            userdefault->setIntegerForKey("hypercube_count", 0);
            userdefault->setIntegerForKey("unholy_count", 0);
            userdefault->setIntegerForKey("honey_count", 0);
            
            userdefault->setFloatForKey("piggybank_price",      80*1.2);
            userdefault->setFloatForKey("mattress_price",       400*1.7);
            userdefault->setFloatForKey("comicbook_price",      1600*1.7);
            userdefault->setFloatForKey("savingaccount_price",  8000*1.7);
            userdefault->setFloatForKey("bitcoinaccount_price", 39000*1.7);
            userdefault->setFloatForKey("stockes_price",        156000*1.7);
            userdefault->setFloatForKey("bookie_price",         650000*1.7);
            userdefault->setFloatForKey("loanshark_price",      1620000*1.7);
            userdefault->setFloatForKey("angelinvestment_price", 3250000*1.7);
            userdefault->setFloatForKey("vanturecapital_price", 5200000*1.7);
            userdefault->setFloatForKey("porkbelly_price",      48750000*1.7);
            userdefault->setFloatForKey("hedgefund_price",      520000000*1.7);
            userdefault->setFloatForKey("investmentbank_price", 7800000000*1.7);
            userdefault->setFloatForKey("insidertrading_price", 650000000000*1.7);
            userdefault->setFloatForKey("mortgage_price",       22000000000000*1.7);
            userdefault->setFloatForKey("pyramid_price",        96500000000000*1.7);
            userdefault->setFloatForKey("hypercube_price",      1200000000000000*1.7);
            userdefault->setFloatForKey("unholy_price",         26000000000000000*1.7);
            userdefault->setFloatForKey("honey_price",          390000000000000000*1.7);
            
            userdefault->setIntegerForKey("paperroute_count", 0);
            userdefault->setIntegerForKey("lemon_count", 0);
            userdefault->setIntegerForKey("flower_count", 0);
            userdefault->setIntegerForKey("coffee_count", 0);
            userdefault->setIntegerForKey("fastfood_count", 0);
            userdefault->setIntegerForKey("casino_count", 0);
            userdefault->setIntegerForKey("cigrate_count", 0);
            userdefault->setIntegerForKey("soda_count", 0);
            userdefault->setIntegerForKey("railroad_count", 0);
            userdefault->setIntegerForKey("strip_count", 0);
            userdefault->setIntegerForKey("arctic_count", 0);
            userdefault->setIntegerForKey("candytheft_count", 0);
            userdefault->setIntegerForKey("oldlady_count", 0);
            userdefault->setIntegerForKey("clown_count", 0);
            userdefault->setIntegerForKey("nsa_count", 0);
            userdefault->setIntegerForKey("dog_count", 0);
            userdefault->setIntegerForKey("cat_count", 0);
            userdefault->setIntegerForKey("cryogenic_count", 0);
            userdefault->setIntegerForKey("banana_count", 0);
            
            userdefault->setFloatForKey("paperroute_price", 50);
            userdefault->setFloatForKey("lemon_price",      2187.5);
            userdefault->setFloatForKey("flower_price",     15000);
            userdefault->setFloatForKey("coffee_price",     105000);
            userdefault->setFloatForKey("fastfood_price",   700000);
            userdefault->setFloatForKey("casino_price",     4151250);
            userdefault->setFloatForKey("cigrate_price",    24900000);
            userdefault->setFloatForKey("soda_price",       210000000);
            userdefault->setFloatForKey("railroad_price",   1210000000);
            userdefault->setFloatForKey("strip_price",      7320000000);
            userdefault->setFloatForKey("arctic_price",     42840000000);
            userdefault->setFloatForKey("candytheft_price", 246400000000);
            userdefault->setFloatForKey("oldlady_price",    1880000000000);
            userdefault->setFloatForKey("clown_price",      11068750000000);
            userdefault->setFloatForKey("nsa_price",        64400000000000);
            userdefault->setFloatForKey("dog_price",        377865000000000);
            userdefault->setFloatForKey("cat_price",        2203200000000000);
            userdefault->setFloatForKey("cryogenic_price",  13000000000000000);
            userdefault->setFloatForKey("banana_price",     92500000000000000);
            
            userdefault->setIntegerForKey("0_count", 0);
            userdefault->setIntegerForKey("1_count", 0);
            userdefault->setIntegerForKey("2_count", 0);
            userdefault->setIntegerForKey("3_count", 0);
            userdefault->setIntegerForKey("4_count", 0);
            userdefault->setIntegerForKey("5_count", 0);
            userdefault->setIntegerForKey("6_count", 0);
            userdefault->setIntegerForKey("7_count", 0);
            userdefault->setIntegerForKey("8_count", 0);
            userdefault->setIntegerForKey("9_count", 0);
            userdefault->setIntegerForKey("10_count", 0);
            userdefault->setIntegerForKey("11_count", 0);
            userdefault->setIntegerForKey("12_count", 0);
            userdefault->setIntegerForKey("13_count", 0);
            userdefault->setIntegerForKey("14_count", 0);
            userdefault->setIntegerForKey("15_count", 0);
            
            userdefault->setFloatForKey("0_price",  200);
            userdefault->setFloatForKey("1_price",  1000);
            userdefault->setFloatForKey("2_price",  3000);
            userdefault->setFloatForKey("3_price",  9800);
            userdefault->setFloatForKey("4_price",  15000);
            userdefault->setFloatForKey("5_price",  60000);
            userdefault->setFloatForKey("6_price",  700000);
            userdefault->setFloatForKey("7_price",  8900000);
            userdefault->setFloatForKey("8_price",  45000000);
            userdefault->setFloatForKey("9_price",  700000000);
            userdefault->setFloatForKey("10_price", 10000000000);
            userdefault->setFloatForKey("11_price", 777000000000);
            userdefault->setFloatForKey("12_price", 105000000000000);
            userdefault->setFloatForKey("13_price", 882500000000000);
            userdefault->setFloatForKey("14_price", 6870000000000000);
            userdefault->setFloatForKey("15_price", 70000000000000000);
            
            userdefault->setFloatForKey("currentcash", 0);
            userdefault->setFloatForKey("currentshakers", 0);
            userdefault->setFloatForKey("currentbucket", 0);
            userdefault->setIntegerForKey("currentdate", 0);
            
            userdefault->setBoolForKey("classicbox", false);
            userdefault->setBoolForKey("chefhat", false);
            userdefault->setBoolForKey("Upiggbank", false);
            userdefault->setBoolForKey("moon", false);
            userdefault->setBoolForKey("earth", false);
            userdefault->setBoolForKey("spaceship", false);
            userdefault->setBoolForKey("ufo", false);
            userdefault->setBoolForKey("dinnerplate", false);
            userdefault->setBoolForKey("trophycup", false);
            userdefault->setBoolForKey("car", false);
            userdefault->setBoolForKey("umbrella", false);
            userdefault->setBoolForKey("diamond", false);
            
            userdefault->setFloatForKey("chefhat_price",    50000);
            userdefault->setFloatForKey("Upiggybank_price", 10000000);
            userdefault->setFloatForKey("moon_price",       500000000);
            userdefault->setFloatForKey("earth_price",      10000000000);
            userdefault->setFloatForKey("spaceship_price",  500000000000);
            userdefault->setFloatForKey("ufo_price",        10000000000000);
            userdefault->setFloatForKey("dinnerplate_price", 500000000000000);
            userdefault->setFloatForKey("trophycup_price",  500000000000000);
            userdefault->setFloatForKey("car_price",        500000000000000);
            userdefault->setFloatForKey("umbrella_price",   10000000000000000);
            userdefault->setFloatForKey("diamond_price",    100000000000000000);
            userdefault->setFloatForKey("prestige_price",   userdefault->getFloatForKey("prestige_price") * 1.5);
            
            userdefault->setIntegerForKey("CustomPopcorn", 0);
            
            userdefault->setFloatForKey("p1_price", 5);
            userdefault->setFloatForKey("p2_price", 5);
            userdefault->setFloatForKey("p3_price", 5);
            userdefault->setFloatForKey("p4_price", 5);
            userdefault->setFloatForKey("p5_price", 5);
            userdefault->setFloatForKey("p6_price", 5);
            userdefault->setFloatForKey("p7_price", 5);
            userdefault->setFloatForKey("p8_price", 5);
            userdefault->setFloatForKey("p9_price", 5);
            userdefault->setFloatForKey("p10_price", 5);
            userdefault->setFloatForKey("p11_price", 10);
            userdefault->setFloatForKey("p12_price", 10);
            userdefault->setFloatForKey("p13_price", 10);
            userdefault->setFloatForKey("p14_price", 10);
            userdefault->setFloatForKey("p15_price", 10);
            userdefault->setFloatForKey("p16_price", 10);
            userdefault->setFloatForKey("p17_price", 10);
            userdefault->setFloatForKey("p18_price", 10);
            userdefault->setFloatForKey("p19_price", 10);
            userdefault->setFloatForKey("p20_price", 10);
            userdefault->setFloatForKey("p21_price", 15);
            userdefault->setFloatForKey("p22_price", 15);
            userdefault->setFloatForKey("p23_price", 15);
            userdefault->setFloatForKey("p24_price", 15);
            userdefault->setFloatForKey("p25_price", 15);
            userdefault->setFloatForKey("p26_price", 15);
            userdefault->setFloatForKey("p27_price", 15);
            
            userdefault->setBoolForKey("p1", false);
            userdefault->setBoolForKey("p2", false);
            userdefault->setBoolForKey("p3", false);
            userdefault->setBoolForKey("p4", false);
            userdefault->setBoolForKey("p5", false);
            userdefault->setBoolForKey("p6", false);
            userdefault->setBoolForKey("p7", false);
            userdefault->setBoolForKey("p8", false);
            userdefault->setBoolForKey("p9", false);
            userdefault->setBoolForKey("p10", false);
            userdefault->setBoolForKey("p11", false);
            userdefault->setBoolForKey("p12", false);
            userdefault->setBoolForKey("p13", false);
            userdefault->setBoolForKey("p14", false);
            userdefault->setBoolForKey("p15", false);
            userdefault->setBoolForKey("p16", false);
            userdefault->setBoolForKey("p17", false);
            userdefault->setBoolForKey("p18", false);
            userdefault->setBoolForKey("p19", false);
            userdefault->setBoolForKey("p20", false);
            userdefault->setBoolForKey("p21", false);
            userdefault->setBoolForKey("p22", false);
            userdefault->setBoolForKey("p23", false);
            userdefault->setBoolForKey("p24", false);
            userdefault->setBoolForKey("p25", false);
            userdefault->setBoolForKey("p26", false);
            
            if (userdefault->getBoolForKey("KernelSale")) {
                userdefault->setFloatForKey("piggybank_price",      userdefault->getFloatForKey("piggybank_price") / 2);
                userdefault->setFloatForKey("mattress_price",       userdefault->getFloatForKey("mattress_price") / 2);
                userdefault->setFloatForKey("comicbook_price",      userdefault->getFloatForKey("comicbook_price") / 2);
                userdefault->setFloatForKey("savingaccount_price",  userdefault->getFloatForKey("savingaccount_price") / 2);
                userdefault->setFloatForKey("bitcoinaccount_price", userdefault->getFloatForKey("bitcoinaccount_price") / 2);
                userdefault->setFloatForKey("stockes_price",        userdefault->getFloatForKey("stockes_price") / 2);
                userdefault->setFloatForKey("bookie_price",         userdefault->getFloatForKey("bookie_price") / 2);
                userdefault->setFloatForKey("loanshark_price",      userdefault->getFloatForKey("loanshark_price") / 2);
                userdefault->setFloatForKey("angelinvestment_price", userdefault->getFloatForKey("angelinvestment_price") / 2);
                userdefault->setFloatForKey("vanturecapital_price", userdefault->getFloatForKey("vanturecapital_price") / 2);
                userdefault->setFloatForKey("porkbelly_price",      userdefault->getFloatForKey("porkbelly_price") / 2);
                userdefault->setFloatForKey("hedgefund_price",      userdefault->getFloatForKey("hedgefund_price") / 2);
                userdefault->setFloatForKey("investmentbank_price", userdefault->getFloatForKey("investmentbank_price") / 2);
                userdefault->setFloatForKey("insidertrading_price", userdefault->getFloatForKey("insidertrading_price") / 2);
                userdefault->setFloatForKey("mortgage_price",       userdefault->getFloatForKey("mortgage_price") / 2);
                userdefault->setFloatForKey("pyramid_price",        userdefault->getFloatForKey("pyramid_price") / 2);
                userdefault->setFloatForKey("hypercube_price",      userdefault->getFloatForKey("hypercube_price") / 2);
                userdefault->setFloatForKey("unholy_price",         userdefault->getFloatForKey("unholy_price") / 2);
                userdefault->setFloatForKey("honey_price",          userdefault->getFloatForKey("honey_price") / 2);
                
                userdefault->setFloatForKey("paperroute_price",     userdefault->getFloatForKey("paperroute_price") / 2);
                userdefault->setFloatForKey("lemon_price",          userdefault->getFloatForKey("lemon_price") / 2);
                userdefault->setFloatForKey("flower_price",         userdefault->getFloatForKey("flower_price") / 2);
                userdefault->setFloatForKey("coffee_price",         userdefault->getFloatForKey("coffee_price") / 2);
                userdefault->setFloatForKey("fastfood_price",       userdefault->getFloatForKey("fastfood_price") / 2);
                userdefault->setFloatForKey("casino_price",         userdefault->getFloatForKey("casino_price") / 2);
                userdefault->setFloatForKey("cigrate_price",        userdefault->getFloatForKey("cigrate_price") / 2);
                userdefault->setFloatForKey("soda_price",           userdefault->getFloatForKey("soda_price") / 2);
                userdefault->setFloatForKey("railroad_price",       userdefault->getFloatForKey("railroad_price") / 2);
                userdefault->setFloatForKey("strip_price",          userdefault->getFloatForKey("strip_price") / 2);
                userdefault->setFloatForKey("arctic_price",         userdefault->getFloatForKey("arctic_price") / 2);
                userdefault->setFloatForKey("candytheft_price",     userdefault->getFloatForKey("candytheft_price") / 2);
                userdefault->setFloatForKey("oldlady_price",        userdefault->getFloatForKey("oldlady_price") / 2);
                userdefault->setFloatForKey("clown_price",          userdefault->getFloatForKey("clown_price") / 2);
                userdefault->setFloatForKey("nsa_price",            userdefault->getFloatForKey("nsa_price") / 2);
                userdefault->setFloatForKey("dog_price",            userdefault->getFloatForKey("dog_price") / 2);
                userdefault->setFloatForKey("cat_price",            userdefault->getFloatForKey("cat_price") / 2);
                userdefault->setFloatForKey("cryogenic_price",      userdefault->getFloatForKey("cryogenic_price") / 2);
                userdefault->setFloatForKey("banana_price",         userdefault->getFloatForKey("banana_price") / 2);
                
                userdefault->setFloatForKey("0_price",          userdefault->getFloatForKey("0_price") / 2);
                userdefault->setFloatForKey("1_price",          userdefault->getFloatForKey("1_price") / 2);
                userdefault->setFloatForKey("2_price",          userdefault->getFloatForKey("2_price") / 2);
                userdefault->setFloatForKey("3_price",          userdefault->getFloatForKey("3_price") / 2);
                userdefault->setFloatForKey("4_price",          userdefault->getFloatForKey("4_price") / 2);
                userdefault->setFloatForKey("5_price",          userdefault->getFloatForKey("5_price") / 2);
                userdefault->setFloatForKey("6_price",          userdefault->getFloatForKey("6_price") / 2);
                userdefault->setFloatForKey("7_price",          userdefault->getFloatForKey("7_price") / 2);
                userdefault->setFloatForKey("8_price",          userdefault->getFloatForKey("8_price") / 2);
                userdefault->setFloatForKey("9_price",          userdefault->getFloatForKey("9_price") / 2);
                userdefault->setFloatForKey("10_price",         userdefault->getFloatForKey("10_price") / 2);
                userdefault->setFloatForKey("11_price",         userdefault->getFloatForKey("11_price") / 2);
                userdefault->setFloatForKey("12_price",         userdefault->getFloatForKey("12_price") / 2);
                userdefault->setFloatForKey("13_price",         userdefault->getFloatForKey("13_price") / 2);
                userdefault->setFloatForKey("14_price",         userdefault->getFloatForKey("14_price") / 2);
                userdefault->setFloatForKey("15_price",         userdefault->getFloatForKey("15_price") / 2);
            }
            break;
        case 26:
            userdefault->setIntegerForKey("CustomBG", 0);
            userdefault->setBoolForKey("NewCustomBG", true);
            break;
        case 27:
            if (userdefault->getFloatForKey("ocean_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else
            {
                userdefault->setIntegerForKey("CustomBG", 1);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
        case 28:
            if (userdefault->getFloatForKey("city_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else
            {
                userdefault->setIntegerForKey("CustomBG", 2);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
        case 29:
            if (userdefault->getFloatForKey("sky_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else
            {
                userdefault->setIntegerForKey("CustomBG", 3);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
        case 30:
            if (userdefault->getFloatForKey("universe_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else
            {
                userdefault->setIntegerForKey("CustomBG", 4);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
        case 31:
            if (userdefault->getFloatForKey("jungle_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else{
                userdefault->setIntegerForKey("CustomBG", 5);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
        case 32:
            if (userdefault->getFloatForKey("desert_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else{
                userdefault->setIntegerForKey("CustomBG", 6);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
        case 33:
            if (userdefault->getFloatForKey("beach_price") > prestigeCount) {
                MessageBox("You haven't prestiged enough to unlock this.", "");
            }else{
                userdefault->setIntegerForKey("CustomBG", 7);
                userdefault->setBoolForKey("NewCustomBG", true);
            }
            break;
            
        default:
            break;
    }
//
    cashmanager->reloadCashPerSecondAndCashPerSwap();
    
    Vec2 offset = table->getContentOffset();
    table->reloadData();
    table->setContentOffset(offset);
}

void InAppPurchaseLayer::onInitialized(bool ok)
{
    log("%s", ok?"IAP >>> Initialized":"IAP >>> Initialize Failed");
}

void InAppPurchaseLayer::onSuccess(sdkbox::Product const& p)
{
    log("IAP >>> Purchase Succesed: %s", p.name.c_str());
    
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmanager = CashManager::getInstance();
    float currentShaker = cashmanager->getCurrentShaker();
    float currentCash = cashmanager->getCurrentCash();
    float cashPerSecond = cashmanager->getCashPerSecond();
    
    if (p.name == "Kernel Blast") {
        cashmanager->setCurrentShaker(currentShaker + 1);
        if (currentCash < 600) {
            cashmanager->setCurrentCash(currentCash + 1000);
        }else
        {
            cashmanager->setCurrentCash(currentCash * 6);
        }
    }else if (p.name == "Kernel Bomb")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        if (currentCash < 1000) {
            cashmanager->setCurrentCash(currentCash + 20000);
        }else
        {
            cashmanager->setCurrentCash(currentCash * 101);
        }
    }else if (p.name == "Double Kernels Per Second")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        cashmanager->setCashPerScecond(cashPerSecond * 2);
    }else if (p.name == "Double Kernels")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        cashmanager->setCurrentCash(currentCash * 2);
        
    }else if (p.name == "Forever 20x")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        userdefault->setBoolForKey("Forever20", true);
    }else if (p.name == "Remove Ads")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        userdefault->setBoolForKey("RemoveAds", true);
        
    }else if (p.name == "Kernel Sale")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        if (!userdefault->getBoolForKey("KernelSale", false)) {
            userdefault->setFloatForKey("piggybank_price",      userdefault->getFloatForKey("piggybank_price") / 2);
            userdefault->setFloatForKey("mattress_price",       userdefault->getFloatForKey("mattress_price") / 2);
            userdefault->setFloatForKey("comicbook_price",      userdefault->getFloatForKey("comicbook_price") / 2);
            userdefault->setFloatForKey("savingaccount_price",  userdefault->getFloatForKey("savingaccount_price") / 2);
            userdefault->setFloatForKey("bitcoinaccount_price", userdefault->getFloatForKey("bitcoinaccount_price") / 2);
            userdefault->setFloatForKey("stockes_price",        userdefault->getFloatForKey("stockes_price") / 2);
            userdefault->setFloatForKey("bookie_price",         userdefault->getFloatForKey("bookie_price") / 2);
            userdefault->setFloatForKey("loanshark_price",      userdefault->getFloatForKey("loanshark_price") / 2);
            userdefault->setFloatForKey("angelinvestment_price", userdefault->getFloatForKey("angelinvestment_price") / 2);
            userdefault->setFloatForKey("vanturecapital_price", userdefault->getFloatForKey("vanturecapital_price") / 2);
            userdefault->setFloatForKey("porkbelly_price",      userdefault->getFloatForKey("porkbelly_price") / 2);
            userdefault->setFloatForKey("hedgefund_price",      userdefault->getFloatForKey("hedgefund_price") / 2);
            userdefault->setFloatForKey("investmentbank_price", userdefault->getFloatForKey("investmentbank_price") / 2);
            userdefault->setFloatForKey("insidertrading_price", userdefault->getFloatForKey("insidertrading_price") / 2);
            userdefault->setFloatForKey("mortgage_price",       userdefault->getFloatForKey("mortgage_price") / 2);
            userdefault->setFloatForKey("pyramid_price",        userdefault->getFloatForKey("pyramid_price") / 2);
            userdefault->setFloatForKey("hypercube_price",      userdefault->getFloatForKey("hypercube_price") / 2);
            userdefault->setFloatForKey("unholy_price",         userdefault->getFloatForKey("unholy_price") / 2);
            userdefault->setFloatForKey("honey_price",          userdefault->getFloatForKey("honey_price") / 2);
            
            userdefault->setFloatForKey("paperroute_price",     userdefault->getFloatForKey("paperroute_price") / 2);
            userdefault->setFloatForKey("lemon_price",          userdefault->getFloatForKey("lemon_price") / 2);
            userdefault->setFloatForKey("flower_price",         userdefault->getFloatForKey("flower_price") / 2);
            userdefault->setFloatForKey("coffee_price",         userdefault->getFloatForKey("coffee_price") / 2);
            userdefault->setFloatForKey("fastfood_price",       userdefault->getFloatForKey("fastfood_price") / 2);
            userdefault->setFloatForKey("casino_price",         userdefault->getFloatForKey("casino_price") / 2);
            userdefault->setFloatForKey("cigrate_price",        userdefault->getFloatForKey("cigrate_price") / 2);
            userdefault->setFloatForKey("soda_price",           userdefault->getFloatForKey("soda_price") / 2);
            userdefault->setFloatForKey("railroad_price",       userdefault->getFloatForKey("railroad_price") / 2);
            userdefault->setFloatForKey("strip_price",          userdefault->getFloatForKey("strip_price") / 2);
            userdefault->setFloatForKey("arctic_price",         userdefault->getFloatForKey("arctic_price") / 2);
            userdefault->setFloatForKey("candytheft_price",     userdefault->getFloatForKey("candytheft_price") / 2);
            userdefault->setFloatForKey("oldlady_price",        userdefault->getFloatForKey("oldlady_price") / 2);
            userdefault->setFloatForKey("clown_price",          userdefault->getFloatForKey("clown_price") / 2);
            userdefault->setFloatForKey("nsa_price",            userdefault->getFloatForKey("nsa_price") / 2);
            userdefault->setFloatForKey("dog_price",            userdefault->getFloatForKey("dog_price") / 2);
            userdefault->setFloatForKey("cat_price",            userdefault->getFloatForKey("cat_price") / 2);
            userdefault->setFloatForKey("cryogenic_price",      userdefault->getFloatForKey("cryogenic_price") / 2);
            userdefault->setFloatForKey("banana_price",         userdefault->getFloatForKey("banana_price") / 2);
            
            userdefault->setFloatForKey("0_price",          userdefault->getFloatForKey("0_price") / 2);
            userdefault->setFloatForKey("1_price",          userdefault->getFloatForKey("1_price") / 2);
            userdefault->setFloatForKey("2_price",          userdefault->getFloatForKey("2_price") / 2);
            userdefault->setFloatForKey("3_price",          userdefault->getFloatForKey("3_price") / 2);
            userdefault->setFloatForKey("4_price",          userdefault->getFloatForKey("4_price") / 2);
            userdefault->setFloatForKey("5_price",          userdefault->getFloatForKey("5_price") / 2);
            userdefault->setFloatForKey("6_price",          userdefault->getFloatForKey("6_price") / 2);
            userdefault->setFloatForKey("7_price",          userdefault->getFloatForKey("7_price") / 2);
            userdefault->setFloatForKey("8_price",          userdefault->getFloatForKey("8_price") / 2);
            userdefault->setFloatForKey("9_price",          userdefault->getFloatForKey("9_price") / 2);
            userdefault->setFloatForKey("10_price",         userdefault->getFloatForKey("10_price") / 2);
            userdefault->setFloatForKey("11_price",         userdefault->getFloatForKey("11_price") / 2);
            userdefault->setFloatForKey("12_price",         userdefault->getFloatForKey("12_price") / 2);
            userdefault->setFloatForKey("13_price",         userdefault->getFloatForKey("13_price") / 2);
            userdefault->setFloatForKey("14_price",         userdefault->getFloatForKey("14_price") / 2);
            userdefault->setFloatForKey("15_price",         userdefault->getFloatForKey("15_price") / 2);
        }
        userdefault->setBoolForKey("KernelSale", true);
        
    }else if (p.name == "King Kernel")
    {
        if (!userdefault->getBoolForKey("KingKernelPurchased")) {
            cashmanager->setCurrentShaker(currentShaker + 1);
            userdefault->setBoolForKey("KingKernelPurchased", true);
        }
        userdefault->setBoolForKey("classicbox", false);
        userdefault->setBoolForKey("chefhat", false);
        userdefault->setBoolForKey("Upiggbank", false);
        userdefault->setBoolForKey("moon", false);
        userdefault->setBoolForKey("earth", false);
        userdefault->setBoolForKey("spaceship", false);
        userdefault->setBoolForKey("ufo", false);
        userdefault->setBoolForKey("dinnerplate", false);
        userdefault->setBoolForKey("trophycup", false);
        userdefault->setBoolForKey("car", false);
        userdefault->setBoolForKey("umbrella", false);
        userdefault->setBoolForKey("diamond", false);
        userdefault->setBoolForKey("prestige", false);
        userdefault->setBoolForKey("KingKernel", true);
        
    }else if (p.name == "Treadmill")
    {
        if (!userdefault->getBoolForKey("TreadmillPurchased")) {
            userdefault->setBoolForKey("NewCustomBG", true);
            userdefault->setBoolForKey("Treadmill", true);
            userdefault->setBoolForKey("TreadmillPurchased", true);
            cashmanager->setCurrentShaker(currentShaker + 1);
        }
    }
    
    Vec2 offset = m_tableview->getContentOffset();
    m_tableview->reloadData();
    m_tableview->setContentOffset(offset);
}

void InAppPurchaseLayer::onFailure(sdkbox::Product const& p, const std::string &msg)
{
    log("IAP >>> Purchase Failed: %s", p.name.c_str());
}

void InAppPurchaseLayer::onCanceled(sdkbox::Product const& p)
{
    log("IAP >>> Purchase Canceled: %s", p.name.c_str());
}

void InAppPurchaseLayer::onRestored(sdkbox::Product const& p)
{
    log("IAP >>> Purchase Restored: %s", p.name.c_str());
    UserDefault *userdefault = UserDefault::getInstance();
    CashManager *cashmanager = CashManager::getInstance();
    float currentShaker = cashmanager->getCurrentShaker();    
    
    if (p.name == "Forever 20x") {
        userdefault->setBoolForKey("Forever20", true);
        cashmanager->setCurrentShaker(currentShaker + 1);
    }else if (p.name == "Kernel Sale")
    {
        cashmanager->setCurrentShaker(currentShaker + 1);
        if (!userdefault->getBoolForKey("KernelSale", false)) {
            userdefault->setFloatForKey("piggybank_price",      userdefault->getFloatForKey("piggybank_price") / 2);
            userdefault->setFloatForKey("mattress_price",       userdefault->getFloatForKey("mattress_price") / 2);
            userdefault->setFloatForKey("comicbook_price",      userdefault->getFloatForKey("comicbook_price") / 2);
            userdefault->setFloatForKey("savingaccount_price",  userdefault->getFloatForKey("savingaccount_price") / 2);
            userdefault->setFloatForKey("bitcoinaccount_price", userdefault->getFloatForKey("bitcoinaccount_price") / 2);
            userdefault->setFloatForKey("stockes_price",        userdefault->getFloatForKey("stockes_price") / 2);
            userdefault->setFloatForKey("bookie_price",         userdefault->getFloatForKey("bookie_price") / 2);
            userdefault->setFloatForKey("loanshark_price",      userdefault->getFloatForKey("loanshark_price") / 2);
            userdefault->setFloatForKey("angelinvestment_price", userdefault->getFloatForKey("angelinvestment_price") / 2);
            userdefault->setFloatForKey("vanturecapital_price", userdefault->getFloatForKey("vanturecapital_price") / 2);
            userdefault->setFloatForKey("porkbelly_price",      userdefault->getFloatForKey("porkbelly_price") / 2);
            userdefault->setFloatForKey("hedgefund_price",      userdefault->getFloatForKey("hedgefund_price") / 2);
            userdefault->setFloatForKey("investmentbank_price", userdefault->getFloatForKey("investmentbank_price") / 2);
            userdefault->setFloatForKey("insidertrading_price", userdefault->getFloatForKey("insidertrading_price") / 2);
            userdefault->setFloatForKey("mortgage_price",       userdefault->getFloatForKey("mortgage_price") / 2);
            userdefault->setFloatForKey("pyramid_price",        userdefault->getFloatForKey("pyramid_price") / 2);
            userdefault->setFloatForKey("hypercube_price",      userdefault->getFloatForKey("hypercube_price") / 2);
            userdefault->setFloatForKey("unholy_price",         userdefault->getFloatForKey("unholy_price") / 2);
            userdefault->setFloatForKey("honey_price",          userdefault->getFloatForKey("honey_price") / 2);
            
            userdefault->setFloatForKey("paperroute_price",     userdefault->getFloatForKey("paperroute_price") / 2);
            userdefault->setFloatForKey("lemon_price",          userdefault->getFloatForKey("lemon_price") / 2);
            userdefault->setFloatForKey("flower_price",         userdefault->getFloatForKey("flower_price") / 2);
            userdefault->setFloatForKey("coffee_price",         userdefault->getFloatForKey("coffee_price") / 2);
            userdefault->setFloatForKey("fastfood_price",       userdefault->getFloatForKey("fastfood_price") / 2);
            userdefault->setFloatForKey("casino_price",         userdefault->getFloatForKey("casino_price") / 2);
            userdefault->setFloatForKey("cigrate_price",        userdefault->getFloatForKey("cigrate_price") / 2);
            userdefault->setFloatForKey("soda_price",           userdefault->getFloatForKey("soda_price") / 2);
            userdefault->setFloatForKey("railroad_price",       userdefault->getFloatForKey("railroad_price") / 2);
            userdefault->setFloatForKey("strip_price",          userdefault->getFloatForKey("strip_price") / 2);
            userdefault->setFloatForKey("arctic_price",         userdefault->getFloatForKey("arctic_price") / 2);
            userdefault->setFloatForKey("candytheft_price",     userdefault->getFloatForKey("candytheft_price") / 2);
            userdefault->setFloatForKey("oldlady_price",        userdefault->getFloatForKey("oldlady_price") / 2);
            userdefault->setFloatForKey("clown_price",          userdefault->getFloatForKey("clown_price") / 2);
            userdefault->setFloatForKey("nsa_price",            userdefault->getFloatForKey("nsa_price") / 2);
            userdefault->setFloatForKey("dog_price",            userdefault->getFloatForKey("dog_price") / 2);
            userdefault->setFloatForKey("cat_price",            userdefault->getFloatForKey("cat_price") / 2);
            userdefault->setFloatForKey("cryogenic_price",      userdefault->getFloatForKey("cryogenic_price") / 2);
            userdefault->setFloatForKey("banana_price",         userdefault->getFloatForKey("banana_price") / 2);
            
            userdefault->setFloatForKey("0_price",          userdefault->getFloatForKey("0_price") / 2);
            userdefault->setFloatForKey("1_price",          userdefault->getFloatForKey("1_price") / 2);
            userdefault->setFloatForKey("2_price",          userdefault->getFloatForKey("2_price") / 2);
            userdefault->setFloatForKey("3_price",          userdefault->getFloatForKey("3_price") / 2);
            userdefault->setFloatForKey("4_price",          userdefault->getFloatForKey("4_price") / 2);
            userdefault->setFloatForKey("5_price",          userdefault->getFloatForKey("5_price") / 2);
            userdefault->setFloatForKey("6_price",          userdefault->getFloatForKey("6_price") / 2);
            userdefault->setFloatForKey("7_price",          userdefault->getFloatForKey("7_price") / 2);
            userdefault->setFloatForKey("8_price",          userdefault->getFloatForKey("8_price") / 2);
            userdefault->setFloatForKey("9_price",          userdefault->getFloatForKey("9_price") / 2);
            userdefault->setFloatForKey("10_price",         userdefault->getFloatForKey("10_price") / 2);
            userdefault->setFloatForKey("11_price",         userdefault->getFloatForKey("11_price") / 2);
            userdefault->setFloatForKey("12_price",         userdefault->getFloatForKey("12_price") / 2);
            userdefault->setFloatForKey("13_price",         userdefault->getFloatForKey("13_price") / 2);
            userdefault->setFloatForKey("14_price",         userdefault->getFloatForKey("14_price") / 2);
            userdefault->setFloatForKey("15_price",         userdefault->getFloatForKey("15_price") / 2);
        }
        userdefault->setBoolForKey("KernelSale", true);
    }else if (p.name == "King Kernel")
    {
        if (!userdefault->getBoolForKey("KingKernelPurchased")) {
            cashmanager->setCurrentShaker(currentShaker + 1);
        }else
        {
            userdefault->setBoolForKey("classicbox", false);
            userdefault->setBoolForKey("chefhat", false);
            userdefault->setBoolForKey("Upiggbank", false);
            userdefault->setBoolForKey("moon", false);
            userdefault->setBoolForKey("earth", false);
            userdefault->setBoolForKey("spaceship", false);
            userdefault->setBoolForKey("ufo", false);
            userdefault->setBoolForKey("dinnerplate", false);
            userdefault->setBoolForKey("trophycup", false);
            userdefault->setBoolForKey("car", false);
            userdefault->setBoolForKey("umbrella", false);
            userdefault->setBoolForKey("diamond", false);
            userdefault->setBoolForKey("prestige", false);
            userdefault->setBoolForKey("KingKernel", true);
        }
    }else if (p.name == "Remove Ads")
    {
        userdefault->setBoolForKey("RemoveAds", true);
        cashmanager->setCurrentShaker(currentShaker + 1);
    }else if (p.name == "Treadmill")
    {
        if (!userdefault->getBoolForKey("TreadmillPurchased")) {
            userdefault->setBoolForKey("NewCustomBG", true);
            userdefault->setBoolForKey("Treadmill", true);
            userdefault->setBoolForKey("TreadmillPurchased", true);
            cashmanager->setCurrentShaker(currentShaker + 1);
        }
    }
    
    Vec2 offset = m_tableview->getContentOffset();
    m_tableview->reloadData();
    m_tableview->setContentOffset(offset);
}

void InAppPurchaseLayer::onProductRequestSuccess(std::vector<sdkbox::Product> const &products)
{
    log("IAP >>> ProductRequest Success >> count : %lu", products.size());
}

void InAppPurchaseLayer::onProductRequestFailure(const std::string &msg)
{
    log("IAP >>> ProductRequest Failed >> message : %s", msg.c_str());
}

void InAppPurchaseLayer::onRestoreComplete(bool ok, const std::string &msg)
{
    
}
