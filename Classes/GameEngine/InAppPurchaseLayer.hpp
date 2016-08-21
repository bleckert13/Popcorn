//
//  InAppPurchaseLayer.hpp
//  Popcorn
//
//  Created by Monkey on 8/1/16.
//
//

#ifndef InAppPurchaseLayer_hpp
#define InAppPurchaseLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "PluginIAP/PluginIAP.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace sdkbox;
using namespace std;

class InAppPurchaseLayer:public LayerColor, public TableViewDataSource, public TableViewDelegate, public sdkbox::IAPListener
{
private:
    virtual Size cellSizeForTable(TableView *table) override;
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;
    
    TableViewCell* newCell(int index);
    TableViewCell* setCell(int nIndex, TableViewCell* cell);
    
    TableView* m_tableview;
    vector<string> list_name;
    vector<string> list_countkey;
    vector<string> list_description;
    vector<string> list_iapname;
    
    float chefhat_price;
    float upiggybank_price;
    float moon_price;
    float earth_price;
    float spaceship_price;
    float ufo_price;
    float dinnerplate_price;
    float trophycup_price;
    float car_price;
    float umbrella_price;
    float diamond_price;
    float prestige_price;
    float ocean_price;
    float city_price;
    float sky_price;
    float universe_price;
    float jungle_price;
    float desert_price;
    float beach_price;
    int prestige_count;
    
    virtual void onInitialized(bool ok) override;
    virtual void onSuccess(sdkbox::Product const& p) override;
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    virtual void onCanceled(sdkbox::Product const& p) override;
    virtual void onRestored(sdkbox::Product const& p) override;
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    virtual void onProductRequestFailure(const std::string &msg) override;
    void onRestoreComplete(bool ok, const std::string &msg) override;
    
public:
    virtual bool init() override;
    static Scene* createScene();
    void showContent();
    CREATE_FUNC(InAppPurchaseLayer);
    
};
#endif /* InAppPurchaseLayer_hpp */
