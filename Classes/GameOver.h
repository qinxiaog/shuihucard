//
//  GameOver.h
//  diamond puzzle
//
//  Created by qin on 13-7-29.
//
//

#ifndef __diamond_puzzle__GameOver__
#define __diamond_puzzle__GameOver__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#include "GameData.h"
using namespace cocos2d;
using namespace extension;
class GameOver:public CCLayer
{
public:
    CCLabelTTF* scorelabel;
    CCLabelTTF* totallabel;
public:
    GameOver(bool sucess);
    ~GameOver();
    bool init();
    int fontsize;
    int h;
    bool m_sucess;
    void nextCallback(CCObject *sender);
    void back(CCObject *sender);
    void setData(int xp,int money,int card,int sword);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};
#endif /* defined(__diamond_puzzle__GameOver__) */
