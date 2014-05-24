#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

#include "cocos2d.h"


#include "HomeLayer.h"
#include "GroupLayer.h"
#include "HeroLayer.h"
#include "GameMapLayer.h"
#include "TuJianLayer.h"
#include "shop.h"
using namespace cocos2d;
#define HOMEGAG   101
#define HEROGAG   102
#define WARGAG   103
#define FIGHTGAG   104
#define HONGDONGGAG   104
#define STOREGAG   105

#define YINGXIONGTAG 201
#define ZHUANGBETAG 202
#define BAOWUTAG 203
#define BAOGUOTAG 204
#define TUJIANTAG 205
#define SETTAG 206

#define DENGLUTAG 301
#define EVERYDAYTAG 302
#define UPDATETAG 303
#define MENUVISIBLE "menuvisible"
class SceneGame : public CCScene
{
public :
	SceneGame(int level);
	bool init(int level);
	~SceneGame();

private :
	HomeLayer* mHudLayer;
	//mainScene* mGameLayer;
    GroupLayer* mGroupLayer;
    HeroLayer* mHeroLayer;
    GameMapLayer *mMap;
    TuJianLayer *mTujian;
    shopLayer *mStoreLayer;
    cocos2d::CCSprite *m_map1;
    cocos2d::CCSprite *m_map2;
	void broadcastInput(float dt);
    int mlevel;
    int scrollwidth;
    void setMenuVisible(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void getCoin(CCObject *sender);
    
};

#endif