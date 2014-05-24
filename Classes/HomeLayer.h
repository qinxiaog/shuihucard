#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;

class HomeLayer : public CCLayer
{
public :
	HomeLayer();
	bool init();
	~HomeLayer();
    bool isBeingUsed;
    CCMenuItemImage *item;
    CCMenuItemImage *item1;
    CCMenuItemImage *item2;
    CCMenuItemImage *item3;
    void updateControl();
    void update(float delta);
    virtual void onEnter();
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    CCProgressTimer *healthBar;
    void healthBarLogic(CCObject *sender);
    CCLabelTTF *barLabel;
    CCLabelTTF *xpLabel;
    CCLabelTTF *moneyLabel;
    CCLabelTTF *coinLabel;
    void menuPauseCallback(CCObject *sender);
    void menuCallback(CCObject *sender);
    int getexp(float x, int n);
    int mlevel;
    int mxp;
    void keyBackClicked();
private :
    void onExit();
    int coinNum;
    int diamondsNum;
    CCLabelTTF *_coins;
    CCLabelTTF *_zuanshi;
    UILabel *levellabel;
    void updateCoin();
    void OnGetMoney();
};

#endif