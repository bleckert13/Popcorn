//
//  PopcornShopLayer.hpp
//  Popcorn
//
//  Created by Hans on 8/3/16.
//
//

#ifndef PopcornShopLayer_hpp
#define PopcornShopLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "PluginIAP/PluginIAP.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace std;
using namespace sdkbox;

class PopcornShopLayer:public LayerColor, public TableViewDataSource, public TableViewDelegate, public sdkbox::IAPListener
{
private:
    virtual Size cellSizeForTable(TableView *table) override;
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(TableView *table) override;
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;
    
    virtual void onInitialized(bool ok) override;
    virtual void onSuccess(sdkbox::Product const& p) override;
    virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
    virtual void onCanceled(sdkbox::Product const& p) override;
    virtual void onRestored(sdkbox::Product const& p) override;
    virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
    virtual void onProductRequestFailure(const std::string &msg) override;
    void onRestoreComplete(bool ok, const std::string &msg) override;
    
    TableView* m_tableview;
    vector<string> list_name;
    vector<string> list_price;
    vector<string> list_description;
    
    Label *m_lbl_shaker;
    
public:
    virtual bool init() override;
    static Scene* createScene();
    void showContent();
    
    CREATE_FUNC(PopcornShopLayer);
    
};
#endif /* PopcornShopLayer_hpp */
