//
//  ZhuangBeiShengji.h
//  kapai
//
//  Created by qin on 14-1-9.
//
//

#ifndef __kapai__ZhuangBeiShengji__
#define __kapai__ZhuangBeiShengji__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#include "GameData.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;

class ZhuangBeiShengjiLayer : public CCLayer
{
    public :
	ZhuangBeiShengjiLayer();
	bool init(ZhuangBeiType type);
	~ZhuangBeiShengjiLayer();
    void getHeros();
    UILayer *m_pUiLayer;
    ZhuangBeiType m_type;
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //UILayout* layout;
    UILabel *coinlabel;
public:
    UIWidget* example_root;
    void menuPauseCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    //void change(int index);
    void updateHero();
    int getexp(float x, int n);
    void close(CCObject *sender);
};

#endif /* defined(__kapai__ZhuangBeiShengji__) */
