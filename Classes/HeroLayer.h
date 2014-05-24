//
//  HeroLayer.h
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#ifndef __kapai__HeroLayer__
#define __kapai__HeroLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#include "GameData.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;
#define MSG_CHANGE_STATE "change"
#define MSG_CHANGE_HERO "changehero"//换将
#define MSG_ZHUANG_UPDATE "zhuangupdate"//装备升级
#define MSG_HERO_UPDATE "heroupdate"//英雄升级
#define MSG_ADD_HERO "addhero"//添加英雄
#define MSG_LEVEL_UPDATE "levelupdate"//升级
class HeroLayer : public CCLayer
{
public :
	HeroLayer();
	bool init();
	~HeroLayer();
    void getHeros();
    void onExit();
    //UILayout* layout;
public:
    UIWidget* example_root;
    UIPageView* pageView;
    void menuCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    void changeState(CCObject *object);
    void updateHero();
    void Shengji(CCObject *sender);
    void changeHero(CCObject* object);
    void Jinjie();
    void pageLeft();
    void pageRight();
};
#endif /* defined(__kapai__HeroLayer__) */
