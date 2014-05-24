//
//  role.h
//  LhTestGame
//
//  Created by lh on 13-10-25.
//
//

#ifndef __LhTestGame__role__
#define __LhTestGame__role__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Bullet.h"
#include "Config.h"

using namespace cocos2d;
using namespace extension;
class BattleScene;
class role:public CCSprite
{
public:
    int battleId;
    std::string resName;
    int chaId;
    CCArray *attackarray;
    int skillId;
    int attackid;
    int effectid;
    int teji;
    int mp;
    int pos;
    int resNum;
    int curHP;
    int changeHp;
    int totalHp;
    int ap;
    int dir;
    float chenzhang;
    CCPoint pt;
    int level;
    CCPoint oldpos;
    HeroType mhero;
    BattleScene *player;
    bool init(HeroType hero,BattleScene *layer);
    bool isDead();
    void whetherDead();
    void initArm(const char * armName);
    void playArm(const char * playName);
    void addBlood();
    void setBloodChange(float changeBlood);
    int attackcount;
    CCProgressTimer *healthBar;
    void healthBarLogic();
    //CREATE_FUNC(role);
public:
    Bullet* attack();
    Bullet* attackRole(CCArray *array);
    void hurt(int skills,int hp,CCPoint from,CCPoint pt);
    void hurtEffect(int skills,CCPoint from,CCPoint pt);
    bool killSprite(CCNode *pSender);
    void setHp();
    void addFont(CCObject *object);
    int findattackpos(int pos);
    void remove();
    void playMusic(int skills);
};
#endif /* defined(__LhTestGame__role__) */
