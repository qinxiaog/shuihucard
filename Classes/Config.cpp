//
//  Config.cpp

#include "Config.h"

CCArray *play_bullet;
CCArray *enemy_bullet;
CCArray *enemy_items;
CCArray *add_Sprites;
static  Config *g_config = NULL;

/**这里用的单例做的全局参数。JS版的直接就定义了一堆全局数组，真是方便*/
Config::Config():m_scoreValue(0),m_life(3),m_isAudioOn(true)
{

    ReadEnemy();
    ReadHero();
    ReadZhuangBei();
    printf("readjson\n");
    m_money=0;
    
    
}
Config::~Config()
{
    play_bullet->release();
    enemy_bullet->release();
    enemy_items->release();
    enemy_items = NULL;
    play_bullet = NULL;
    enemy_bullet = NULL;
    CCLOG("release config");

}

Config* Config::sharedConfig()
{
    if (!g_config) {
        g_config = new Config();
    }
    return g_config;
}
void Config::ReadEnemy()
{
    CSJson::Value root;
    CSJson::Value datas;
    CSJson::Reader reader;
    unsigned  long nSize = 0;
    string path =CCFileUtils::sharedFileUtils()->fullPathForFilename("enemy.json");
    char* json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    //printf("name1==%s",json_document);
    if(reader.parse(json_document, root))
    {
        datas=root["data"];
        
        for (int i=0; i<datas.size(); i++)
        {
            EnemyType enemyType;
            int type= datas[i]["type"].asInt();
            enemyType.type =type;
            enemyType.name =datas[i]["name"].asString();
            enemyType.textureName =datas[i]["picture"].asString();
            enemyType.hp = datas[i]["hp"].asInt();
            enemyType.ap = datas[i]["ap"].asInt();
            enemyType.skillsid =datas[i]["skillsid"].asInt();
            enemyType.attackid=datas[i]["attackid"].asInt();
            enemyType.defend=datas[i]["defend"].asInt();
            enemyType.magicdefend=datas[i]["magicdefend"].asInt();
            m_enemyTypes.insert(map <int,EnemyType>::value_type(type,enemyType));
        }
    }
}
void Config::ReadHero()
{
    CSJson::Value Heroroot;
    CSJson::Value heros;
    CSJson::Reader reader;
    unsigned  long nSize = 0;
   string path =CCFileUtils::sharedFileUtils()->fullPathForFilename("hero.json");
   char* json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);

    if(reader.parse(json_document, Heroroot))
    {
        heros=Heroroot["data"];
        
        for (int i=0; i<heros.size(); i++)
        {
            HeroType enemyType;
            int type= heros[i]["type"].asInt();
            enemyType.type =type;
            enemyType.name =heros[i]["name"].asString();
            enemyType.exname =heros[i]["exname"].asString();
            enemyType.starname =heros[i]["starname"].asString();
            enemyType.textureName =heros[i]["picture"].asString();
            enemyType.skillsname =heros[i]["skillsname"].asString();
            enemyType.defend=0;
            enemyType.magicdefend=0;
            enemyType.hp = heros[i]["hp"].asInt();
            enemyType.ap = heros[i]["ap"].asInt();
            enemyType.skillsid =heros[i]["skillsid"].asInt();
            enemyType.attackid=heros[i]["attackid"].asInt();
            enemyType.magic=heros[i]["magic"].asInt();
            enemyType.des=heros[i]["des"].asString();
            enemyType.number=heros[i]["number"].asInt();
            enemyType.card=heros[i]["card"].asInt();
            //printf("des===%s",enemyType.des.c_str());
            m_HeroTypes.insert(map <int,HeroType>::value_type(type,enemyType));
        }
    }
}
void Config::ReadZhuangBei()
{
    CSJson::Value Headroot;
    CSJson::Value heads;
    CSJson::Reader reader;
    unsigned  long nSize = 0;
    string path =CCFileUtils::sharedFileUtils()->fullPathForFilename("cloth.json");
    char* json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    //printf("head%s",json_document);
    
    if(reader.parse(json_document, Headroot))
    {
        heads=Headroot["datas"];
        
        for (int i=0; i<heads.size(); i++)
        {
            ZhuangBeiType headType;
            int type= heads[i]["type"].asInt();
            headType.type =type;
            headType.name =heads[i]["name"].asString();
            headType.textureName =heads[i]["picture"].asString();
            headType.defender = heads[i]["defend"].asInt();
            headType.magicdefender = heads[i]["magic"].asInt();
            headType.star = heads[i]["star"].asInt();
            headType.hp = heads[i]["hp"].asInt();
            headType.ap = heads[i]["ap"].asInt();
            m_ZhuangTypes.insert(map <int,ZhuangBeiType>::value_type(type,headType));
        }
    }
}

map<int,EnemyType> Config::getEnemyType()
{
    return m_enemyTypes;
}
map<int,HeroType> Config::getHerosType()
{
    return m_HeroTypes;
}
map<int,ZhuangBeiType> Config::getZhuangBei()
{
    return m_ZhuangTypes;
}
int Config::getScoreValue()
{
    return m_scoreValue;
}

void Config::setScoreValue(int score)
{
    m_scoreValue += score;
}
void Config::setMoney(int money)
{
    m_money+=money;
}
int Config::getMoney()
{
    return m_money;
}
int Config::getLifeCount()
{
    return m_life;
}
void Config::updateLifeCount()
{
    m_life--;
}

bool Config::getAudioState()
{
    return m_isAudioOn;
}

void Config::updateAudioState(bool isOn)
{
    m_isAudioOn = isOn;
}

void Config::resetConfig()
{
    m_scoreValue = 0;
    m_life = 3;
//    m_isAudioOn = true;
}
