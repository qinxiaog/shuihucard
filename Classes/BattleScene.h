//
//  BattleScene.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__BattleScene__
#define __LhTestGame__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "role.h"
#include <list>
#include "SimpleAudioEngine.h"
#include "Config.h"
#define MSG_BATTLE "battle"
using namespace cocos2d;
using namespace extension;
using namespace CSJson;
using namespace std;
using namespace CocosDenshion;
class BattleScene:public CCLayer
{
public:
    virtual bool init(Value datas);
    CCArray *deadArr;
    CCNode * pNode;
    role * ene_role;
    role * my_role;
    int chaBattleId;
    int eneBattleId;
    CCArray * ene_Arr;
    CCArray * RoleArr;
public:
    BattleScene();
    ~BattleScene();
    list<Bullet*> mBullets;
    static CCScene * scene(Value datas);
    void runAttack();
    void moreAttack();
    void moreEneHurt();
    void moreWhetherDead();
    CSJson::Value alluseValue;
    void eneHurt(CCArmature * arm,MovementEventType type,const char * name);
    void whetherDead(CCArmature * arm,MovementEventType type,const char * name);
    int rounds;
    void getJsonData(const char * data);
    void initAttackData(Value datas);
    void initRole();
    //CREATE_FUNC(BattleScene);
    void BeginFight(float dt);
    void update(float dt);
    void bulletUpdate(float dt);
    void enemyUpdate(float dt);
    //void draw();
    int findAttackPos(int pos,int index);
    int findAttackLeft(int pos,int index);
    int findAttackRight(int pos,int index);
    int findAttackBottomPos(int pos,int index);
    role *getAttackRole(int index);
    role *getEnemyRole(int index);
    void addFont(int hp,CCPoint pt);
    void removeself();
    void enemyattack(role* a,int index);
    void attack(role*role,int index);
    void updateRole();
public:
    int mapid;
    int subid;
    float begintime;
    int fighttime;
    bool bGameover;
    bool bTurn;
    int roleIndex;
    int oldRoleIndex;
    int enemyIndex;
    CCRect mrect;
    CCRect mrect1;
    bool msucess;
    int money;
    int mxp;
    int card;
    int zhuangbei;
    int mspeed;
    void changeSpeed(CCObject *sender);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
};
#endif /* defined(__LhTestGame__BattleScene__) */
