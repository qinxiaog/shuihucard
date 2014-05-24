//
//  ZhuangBeiLayer.h
//  kapai
//
//  Created by qin on 13-12-20.
//
//

#ifndef __kapai__ZhuangBeiLayer__
#define __kapai__ZhuangBeiLayer__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class ZhuangBeiListLayer : public CCLayer
{
    public :
	ZhuangBeiListLayer();
	bool init(HeroType hero,int type,ZhuangBeiType zhuang);
	~ZhuangBeiListLayer();
//    UILayer *m_pUiLayer;
//    UIScrollView* scrollView;
    void Zhuangupdate();
    ZhuangBeiType m_zhuangtype;
    //void onExit();
public:
    HeroType m_hero;
    int m_type;
    void setData(HeroType hero,int type,ZhuangBeiType zhuangtype);
    void menuPauseCallback(CCObject *sender);
    void Shengji(CCObject *sender);
    void close(CCObject *sender);
    int getexp(int ap,float x, int n);
};
#endif /* defined(__kapai__ZhuangBeiLayer__) */
