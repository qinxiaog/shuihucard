//
//  ShengJiLayer.h
//  kapai
//
//  Created by qin on 14-1-7.
//
//

#ifndef __kapai__ShengJiLayer__
#define __kapai__ShengJiLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#include "GameData.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;

class ShengJiLayer : public CCLayer
{
    public :
	ShengJiLayer();
	bool init(HeroType hero);
	~ShengJiLayer();
    void getHeros();
    
    UILayer *m_pUiLayer;
    HeroType m_hero;
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //UILayout* layout;
public:
    UIWidget* example_root;
    void menuPauseCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    void change(int index);
    void updateHero();
    void close(CCObject *sender);
    UILabel *coinlabel;
    int getexp(float x, int n);
};

#endif /* defined(__kapai__ShengJiLayer__) */
