//
//  GameMapLayer.h
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#ifndef __kapai__GameMapLayer__
#define __kapai__GameMapLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;
class GameMapLayer : public CCLayer
{
    public :
	GameMapLayer();
	bool init();
	~GameMapLayer();
    void ReadJson();
public:
    UIWidget* example_root;
    void buttonTouchEvent(CCObject *sender);
    void onExit();
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

protected:
    UILayer* m_pUILayer;
};

#endif /* defined(__kapai__GameMapLayer__) */
