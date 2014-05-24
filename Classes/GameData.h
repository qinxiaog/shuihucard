//
//  GameData.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__GameData__
#define __LhTestGame__GameData__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
#define LEVELXP 300
class Config;
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;
typedef struct
{
    int ap;//攻击
    int type;
    int level;
    int star;
    string textureName;
    string name;
    int index;
}SwordType;
typedef struct
{
    int defender;//防御
    int magicdefender;//魔防
    int type;
    int hp;
    int level;
    int star;
    string textureName;
    string name;
    int index;
}ClothType;
typedef struct
{
    int magicdefender;//魔防
    int defender;//物防
    int type;
    int hp;
    int level;
    int star;
    string textureName;
    string name;
    int index;
}HeadType;
typedef struct
{
    int type;
    int hp;
    int ap;
    int level;
    int star;
    string textureName;
    string name;
    int index;
}HorseType;
typedef struct
{
    int type;
    int defender;
    int level;
    int star;
    string textureName;
    string name;
    int index;
}JieZhiType;
typedef struct
{
    int type;
    int ap;
    int level;
    int star;
    string textureName;
    string name;
    int index;
}BaowuType;
typedef struct
{
    int type;
    int index;
    int level;
    int exlevel;
    int defender;
    int magicdefender;
    int ap;
    int hp;
    int star;
    string name;
    string textureName;
    int user;
    int money;
}ZhuangBeiType;

typedef struct
{
    int type;//类型
    string textureName;//图片
    string name;
    string exname;
    string starname;
    string skillsname;
    int index;
    int pos;//位置
    int hp;//卡牌的血
    int ap;//卡牌攻击
    int totalhp;//总的血量
    int totalap;//总的攻击
    int defend;
    int magicdefend;
    int totalmagicdefend;//总魔防
    int totaldefend;//总的防御
    int attackid;//攻击方式
    int skillsid;//技能
    int level;
    int exlevel;//品质
    int xp;//经验
    int card;//黑1，红2，梅3，方4
    int number;//2 j11 Q12 k13 A14 王14,大王15
    int swordid;//武器id;
    int baowuid;//宝贝;
    int magic;//是否魔法攻击
    ZhuangBeiType zhuang[6];
    string des;
}HeroType;
typedef struct {
    int type;
    string textureName;
    string name;
    string exname;
    string starname;
    string skillsname;
    int hp;
    int ap;
    int attackid;
    int skillsid;
    int level;
    int card;//花色
    int number;//数字
    int magic;
    string des;
    int defend;
    int magicdefend;
}EnemyType;
class GameData{
public:
    GameData();
    ~GameData();
    vector<HeroType> m_Heros;
    vector<ZhuangBeiType> m_ZhuangBeis;
    int mlevel;
    int mxp;
    int mMoney;
    int mCoin;
    CCDictionary * dic;
    std::string scoredata;
    int userID;
    int charId;
    int mapId;
    int subMapId;
    int speed;
    std::string  str;
    static GameData * shareGameData();
    CCDictionary * roleDic;
public:
    void readJson();
    void saveHero();
    void saveDefault();
    vector<HeroType> getHeros();
    vector<ZhuangBeiType> getZhuangbei();
    
    bool addHero(HeroType hero);
    bool setHero(HeroType hero,HeroType kapai);
    void removeKapai(HeroType hero);
    void updateHero(HeroType hero);

    void QianghuaHero(HeroType kapai,HeroType hero);
    void setHero(HeroType hero);
    bool addKapai(HeroType hero);
    void changeHero(HeroType oldhero,HeroType changehero);
    void changePos();

    bool changeZhuangBei(HeroType herodata,ZhuangBeiType zhuang,int index);
    bool addZhuangBei(ZhuangBeiType zhuang);
    void updateZhuang(ZhuangBeiType zhuang);
    void updateHeros();
    void saveZhuangBei();

    void readZhuangbei();

    bool IsSort(int arr[], int length);
    void setMoney(int money);
    void setCoin(int coin);
    void setData(int money,int xp);
    int getexp(float x, int n);
};
#endif /* defined(__LhTestGame__GameData__) */
