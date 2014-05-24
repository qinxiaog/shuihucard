//
//  StoreLayer.h
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#ifndef __kapai__StoreLayer__
#define __kapai__StoreLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
using namespace std;
using namespace CSJson;
using namespace cocos2d;
class StoreLayer : public CCLayer
{
    public :
	StoreLayer();
	bool init();
	~StoreLayer();
    void buyCallback(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void close(CCObject *sender);
    void onBuy(int type);
    void onExit();
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__kapai__StoreLayer__) */
