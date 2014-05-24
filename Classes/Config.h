//
//  Config.h


#ifndef MoonWarriorsx_Config_h
#define MoonWarriorsx_Config_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include <list>
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include <map>
using namespace cocos2d;
using namespace extension;
using namespace CSJson;
using namespace std;
using namespace CocosDenshion;


extern cocos2d::CCArray *play_bullet;
extern cocos2d::CCArray *enemy_bullet;
extern cocos2d::CCArray *enemy_items;
extern cocos2d::CCArray *add_Sprites;
typedef struct Enemies
{
    string showType;
    int showTime;
    int types[3];
    Enemies()
    {
        showType = "Repeate";
        showTime = 0;
        types[0] = 0;
        types[1] = 0;
        types[2] = 0;
        
    }
}EnemyInfo;



class Config : public CCObject{
private:
    map<int,EnemyType> m_enemyTypes;
    map<int,HeroType>m_HeroTypes;
    
    map<int, ZhuangBeiType>m_ZhuangTypes;
    int m_scoreValue;
    int m_life;
    bool m_isAudioOn;
    int m_money;
    Config();
public:
    ~Config();
    static Config* sharedConfig();
    map<int,EnemyType> getEnemyType();
    map<int,HeroType> getHerosType();
    map<int,ZhuangBeiType> getZhuangBei();

    int getLifeCount();
    void setMoney(int money);
    int getMoney();
    bool getAudioState();
    void setTypeCount(int type);
    void updateAudioState(bool isOn);
    int getScoreValue();
    void updateLifeCount();
    void setScoreValue(int score);
    void resetConfig();
    void ReadZhuangBei();
    void ReadEnemy();
    void ReadHero();
};


#endif
