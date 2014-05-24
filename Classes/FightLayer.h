//
//  FightLayer.h
//  kapai
//
//  Created by qin on 14-4-6.
//
//

#ifndef __kapai__FightLayer__
#define __kapai__FightLayer__

#include "cocos-ext.h"
#include <stdio.h>
#include "Config.h"
#include "GetHeroLayer.h"
using namespace std;
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class FightLayer : public CCLayer,public CCTableViewDelegate,CCTableViewDataSource
{
    
public :
	FightLayer(int level);
	bool init(int level);
	~FightLayer();
public:
    EnemyType cardType;
    Value datas;
    int mlevel;
    void readJson();
    float scrollHeight;
    float imageHeight;
    char* map_document;
    void menuPauseCallback(CCObject *sender);
    void close(CCObject *sender);
    void onExit();
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    
    //CCTableViewDelegate继承自CCScrollViewDelegate
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
    //点击哪个cell
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    //每个cell的size
    virtual CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    //生成cell
    virtual CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    //cell的数量
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    //按下去的时候，就是高亮显示，这里可以设置高亮状态
    virtual void tableCellHighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    //松开的时候，取消高亮状态
    virtual void tableCellUnhighlight(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    //void scrollBar(CCTableView* table);
};
#endif /* defined(__kapai__FightLayer__) */
