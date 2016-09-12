//
//  InvestmentLayer.hpp
//  Popcorn
//
//  Created by Hans on 7/28/16.
//
//

#ifndef InvestmentLayer_hpp
#define InvestmentLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace std;

class InvestmentLayer:public LayerColor, public TableViewDataSource, public TableViewDelegate
{
private:
    virtual Size cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    
    TableViewCell* newCell(int index);
    TableViewCell* setCell(int nIndex, TableViewCell* cell);
    
    TableView* m_tableview;
    vector<string> list_name;
    vector<string> list_countkey;
    vector<string> list_pricekey;
    vector<string> list_profit;
    
public:
    virtual bool init();
    static Scene* createScene();
    void showContent();
    CREATE_FUNC(InvestmentLayer);
    
};

#endif /* InvestmentLayer_hpp */
