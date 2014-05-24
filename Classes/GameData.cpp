//
//  GameData.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "GameData.h"
#include "Config.h"
#define MAXVALUE 10000
#define MINVALUE -1
#define SIZE 14
#define NUMBER 5
static GameData * game=NULL;

GameData::GameData()
{
    roleDic=CCDictionary::create();
    roleDic->retain();
    dic=CCDictionary::create();
    dic->retain();
    subMapId=0;
    mapId=0;
    speed=3;
    mlevel=CCUserDefault::sharedUserDefault()->getIntegerForKey("level",1);
    mxp=CCUserDefault::sharedUserDefault()->getIntegerForKey("xp",1);
    mMoney=CCUserDefault::sharedUserDefault()->getIntegerForKey("money",20000);
    mCoin=CCUserDefault::sharedUserDefault()->getIntegerForKey("coin",200);
    CCUserDefault::sharedUserDefault()->flush();
    readZhuangbei();
    readJson();
    
    //readKapai();
}
GameData::~GameData(){
    
}
GameData * GameData::shareGameData(){
    if(!game){
        game=new GameData();
    }
    return game;
}
void GameData::readJson()
{
    CSJson::Value root;
    
    CSJson::Reader reader;
    unsigned  long nSize = 0;
    string path=CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("myhero.json");
    char* json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    if(json_document==NULL)
    {
        saveDefault();
        json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    }
    //printf("json==%s",json_document);
   if(reader.parse(json_document, root))
   {
    int size = root.size();
    map<int,HeroType> HeroTypes=Config::sharedConfig()->getHerosType();
    map<int,ZhuangBeiType> ZhuangTypes=Config::sharedConfig()->getZhuangBei();
    for (int i=0; i<size; ++i)
    {
        HeroType herodata;
        herodata.level=root[i]["level"].asInt();//等级
        herodata.exlevel=root[i]["exlevel"].asInt();//强化等级
        herodata.type=root[i]["type"].asInt();//类型
        herodata.xp=root[i]["xp"].asInt();//经验
        herodata.pos=root[i]["pos"].asInt();//位置
        herodata.index=root[i]["index"].asInt();//索引
        map<int,HeroType>::iterator iterHero = HeroTypes.find(herodata.type);
        if(iterHero!= HeroTypes.end())
        {
            HeroType herotype=iterHero->second;
            herodata.name=herotype.name;
            herodata.textureName=herotype.textureName;//英雄图片
            herodata.card=herotype.card;//花色
            herodata.number=herotype.number;//数字
            herodata.exname=herotype.exname;//绰号
            herodata.starname=herotype.starname;//星座
 
            
            herodata.hp=(herotype.hp+herotype.hp*herodata.level/10)*(1+herodata.exlevel/10.0);//卡牌总血量
            herodata.ap=(herotype.ap+herotype.ap*herodata.level/10)*(1+herodata.exlevel/10.0);//卡牌总攻击
            herodata.defend=herotype.defend;
            herodata.magicdefend=herotype.magicdefend;
            herodata.skillsid=herotype.skillsid;
            herodata.attackid=herotype.attackid;
            herodata.totalmagicdefend=0;
            herodata.totaldefend=0;
            herodata.totalap=herodata.ap;
            herodata.totalhp=herodata.hp;
            herodata.des=herotype.des;
            herodata.skillsname=herotype.skillsname;
            
            
            for(int j=0;j<6;j++)
            {
                char str[32];
                sprintf(str,"zhuang%d",j);
                int head=root[i][str].asInt();//头盔类型等级
                char strIndex[32];
                sprintf(strIndex,"index%d",j);
                int index=root[i][strIndex].asInt();//头盔类型等级
                
                int headlevel=head%100;
                int type=head/1000;
                map<int,ZhuangBeiType>::iterator iter = ZhuangTypes.find(type);
                if(iter!= ZhuangTypes.end())
                {
                    ZhuangBeiType headtype=iter->second;
                    herodata.zhuang[j].index=index;
                    herodata.zhuang[j].type=type;//类型
                    herodata.zhuang[j].level=headlevel;//等级
                    herodata.zhuang[j].star=headtype.star;//星级
                    herodata.zhuang[j].name=headtype.name;
                    herodata.zhuang[j].textureName=headtype.textureName;//图片
                    herodata.zhuang[j].defender=headtype.defender+headtype.defender*headlevel/10;
                    herodata.zhuang[j].magicdefender=headtype.magicdefender+headtype.magicdefender*headlevel/10;
                    herodata.zhuang[j].hp=headtype.hp+headtype.hp*headlevel/10;
                    herodata.zhuang[j].ap=headtype.ap+headtype.ap*headlevel/10;
                    herodata.totalap+=herodata.zhuang[i].ap;
                    herodata.totalhp+=herodata.zhuang[i].hp;
                    herodata.totaldefend+=herodata.zhuang[i].defender;
                    herodata.totalmagicdefend+=herodata.zhuang[i].magicdefender;
                }
                else
                {
                    herodata.zhuang[j].type=0;//类型
                    herodata.zhuang[j].level=0;//等级
                    herodata.zhuang[j].star=0;//星级
                    herodata.zhuang[j].defender=0;
                    herodata.zhuang[j].magicdefender=0;
                    herodata.zhuang[j].hp=0;
                    herodata.zhuang[j].ap=0;
                }
            }
            if(herodata.exlevel>=2)
            {
                float number=((108-herodata.type)/10+20)/100+1.0;
                herodata.totalhp*=number;
            }
            else if(herodata.exlevel>=5)
            {
                float number1=(herodata.type/10+20)%100+1;
                herodata.totalap*=number1;
            }
        }
        m_Heros.push_back(herodata);
    }
   }
}
void GameData::saveDefault()
{
    string path=CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("myhero.json");//保存战斗英雄
    CSJson::Value root;
    CSJson::Value person;
    
    person["level"] = 1;//等级
    person["exlevel"] = 0;//品介
    person["type"] = 3;//类型
    person["xp"] = 0;//经验
    person["pos"]=1;//位置
    person["index"]=0;//卡牌索引
    person["zhuang0"]=300000;//头盔
    person["zhuang1"]=400000;//盔甲
    person["zhuang2"]=500000;//武器
    person["zhuang3"]=600000;//宝物
    person["zhuang4"]=700000;//鞋子
    person["zhuang5"]=800000;//坐骑
    person["index0"]=-1;//头盔
    person["index1"]=-1;//盔甲
    person["index2"]=-1;//武器
    person["index3"]=-1;//宝物
    person["index4"]=-1;//鞋子
    person["index5"]=-1;//坐骑
    root.append(person);
    person["level"] = 1;
    person["exlevel"] = 0;//品介
    person["type"] =108;
    person["xp"] = 0;
    person["pos"]=2;
    person["index"]=1;
    person["zhuang0"]=300000;
    person["zhuang1"]=400000;
    person["zhuang2"]=500000;
    person["zhuang3"]=600000;
    person["zhuang4"]=700000;
    person["zhuang5"]=800000;
    person["index0"]=-1;//头盔
    person["index1"]=-1;//盔甲
    person["index2"]=-1;//武器
    person["index3"]=-1;//宝物
    person["index4"]=-1;//鞋子
    person["index5"]=-1;//坐骑
    root.append(person);
    CSJson::FastWriter fw ;
    std::string json_file = fw.write(root);
    //创建一个文件指针
    //路径、模式
    FILE* file = fopen(path.c_str(), "wb");
    if (file)
    {
        fputs(json_file.c_str(),file);
        fclose(file);
    }
}
bool GameData::changeZhuangBei(HeroType herodata,ZhuangBeiType zhuang,int i)
{//英雄换装

    for (vector<HeroType>::iterator iterhero = m_Heros.begin(); iterhero != m_Heros.end();iterhero++)
    {
        //printf("index===%d,%d",iterhero->zhuang[i].index,zhuang.index);
        if(iterhero->zhuang[i].index==zhuang.index)
        {
            (*iterhero).zhuang[i].user=-1;
            (*iterhero).zhuang[i].type=0;//类型
            (*iterhero).zhuang[i].level=0;//等级
            (*iterhero).zhuang[i].star=0;//星级
            (*iterhero).zhuang[i].index=0;//星级
            (*iterhero).zhuang[i].name="";
            (*iterhero).zhuang[i].textureName="addbutton.png";//图片
            (*iterhero).zhuang[i].defender=0;
            (*iterhero).zhuang[i].magicdefender=0;
        }
    }
    for (vector<HeroType>::iterator iterhero = m_Heros.begin(); iterhero != m_Heros.end();iterhero++)
    {
        if(iterhero->index==herodata.index)
        {
            (*iterhero).zhuang[i]=zhuang;
            (*iterhero).zhuang[i].user=iterhero->index;
            (*iterhero).zhuang[i].type=zhuang.type;//类型
            (*iterhero).zhuang[i].level=zhuang.level;//等级
            (*iterhero).zhuang[i].star=zhuang.star;//星级
            (*iterhero).zhuang[i].index=zhuang.index;//星级
            (*iterhero).zhuang[i].name=zhuang.name;
            (*iterhero).zhuang[i].textureName=zhuang.textureName;//图片
            (*iterhero).zhuang[i].defender=zhuang.defender+zhuang.defender*zhuang.level/10;
            (*iterhero).zhuang[i].magicdefender=zhuang.magicdefender+zhuang.magicdefender*zhuang.level/10;
        }
    }
    vector<ZhuangBeiType>::iterator iter;
    for(iter= m_ZhuangBeis.begin(); iter!= m_ZhuangBeis.end();iter++)
    {
        if(iter->index==zhuang.index)
        {
            iter->user=herodata.index;
        }
    }
    updateHeros();
    saveHero();
    saveZhuangBei();
}
bool GameData::addZhuangBei(ZhuangBeiType zhuang)
{
    
    if(m_ZhuangBeis.size()<=200)
    {
        m_ZhuangBeis.push_back(zhuang);
        saveZhuangBei();
        return true;
    }
    return false;
}
bool GameData::addHero(HeroType hero)//添加上场英雄
{
    vector<HeroType>::iterator iter;
	for (iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    {
        if(hero.index==iter->index)//
        {
            iter->pos=hero.pos;
        }
    }
    updateHeros();
    saveHero();
    return true;
}
bool GameData::addKapai(HeroType hero)//添加卡牌英雄
{
    hero.index=m_Heros.size();
    m_Heros.push_back(hero);
    saveHero();
    return true;
}
void GameData::updateHero(HeroType hero)//英雄刷新位置
{
    vector<HeroType>::iterator iter;
	for (iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    {
        if(hero.index==iter->index)//类型相同的不能一起
        {
            iter->pos=hero.pos;
        }
    }
    updateHeros();
    saveHero();
}
void GameData::setHero(HeroType hero)//英雄升级
{
    vector<HeroType>::iterator iter;
	for (iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    {
        if(hero.index==iter->index)//类型相同的不能一起
        {
            iter->level+=1;
        }
    }
    updateHeros();
    saveHero();
}
void GameData::removeKapai(HeroType hero)//删除卡牌
{
	for (vector<HeroType>::iterator iter = m_Heros.begin();iter != m_Heros.end();)
    {
        printf("index===%d,%d",iter->index,hero.index);
        if(hero.index==iter->index)//
        {
            m_Heros.erase(iter);
            break;
        }
        iter++;
    }
    for (int i=0;i<m_Heros.size();i++)
    {
        m_Heros[i].index=i;
    }
    updateHeros();
    saveHero();
}
void GameData::QianghuaHero(HeroType kapai,HeroType hero)//英雄强化
{
	for (vector<HeroType>::iterator iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    {
        if(hero.index==iter->index)//类型相同的不能一起
        {
            iter->exlevel+=1;
        }
    }

}
void GameData::changeHero(HeroType oldhero,HeroType changehero)
{
    int changeindex=0;
    int oldindex=0;
    for(int j=0;j<m_Heros.size();j++)
    {
        if(changehero.index==m_Heros[j].index)
        {
            changeindex=j;
        }
        if(oldhero.index==m_Heros[j].index)
        {
            oldindex=j;
        }

    }

        m_Heros[changeindex]=oldhero;
        m_Heros[changeindex].pos=0;
    for(int i=0;i<6;i++)
    {
        m_Heros[changeindex].zhuang[i].user=0;
        m_Heros[changeindex].zhuang[i].type=0;//类型
        m_Heros[changeindex].zhuang[i].level=0;//等级
        m_Heros[changeindex].zhuang[i].star=0;//星级
        m_Heros[changeindex].zhuang[i].index=0;//星级
        m_Heros[changeindex].zhuang[i].name="";
        m_Heros[changeindex].zhuang[i].textureName="addbutton.png";//图片
        m_Heros[changeindex].zhuang[i].defender=0;
        m_Heros[changeindex].zhuang[i].magicdefender=0;
    }

        m_Heros[oldindex]=changehero;
        m_Heros[oldindex].pos=oldhero.pos;
    for(int i=0;i<6;i++)
    {
        m_Heros[oldindex].zhuang[i].user=oldhero.index;
        m_Heros[oldindex].zhuang[i].type=oldhero.zhuang[i].type;//类型
        m_Heros[oldindex].zhuang[i].level=oldhero.zhuang[i].level;//等级
        m_Heros[oldindex].zhuang[i].star=oldhero.zhuang[i].star;//星级
        m_Heros[oldindex].zhuang[i].index=oldhero.zhuang[i].index;//星级
        m_Heros[oldindex].zhuang[i].name=oldhero.zhuang[i].name;
        m_Heros[oldindex].zhuang[i].textureName=oldhero.zhuang[i].textureName;//图片
        m_Heros[oldindex].zhuang[i].defender=oldhero.zhuang[i].defender;
        m_Heros[oldindex].zhuang[i].magicdefender=oldhero.zhuang[i].magicdefender;
        m_Heros[oldindex].zhuang[i].ap=oldhero.zhuang[i].ap;
        m_Heros[oldindex].zhuang[i].hp=oldhero.zhuang[i].hp;
    }
    updateHeros();
    saveHero();
}
void GameData::changePos()
{
    
}
bool GameData::setHero(HeroType hero,HeroType kapai)//换英雄
{

    vector<HeroType>::iterator iter;
    vector<HeroType>::iterator iterkapai;
    //kapai.pos=hero.pos;
	for (iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    { 
        if(hero.index==iter->index)
        {
            *iter=kapai;
            for(int j=0;j<6;j++)
            {
                    (*iter).zhuang[j].user=hero.index;
                    (*iter).zhuang[j].type=hero.type;//类型
                    (*iter).zhuang[j].level=hero.zhuang[j].level;//等级
                    (*iter).zhuang[j].star=hero.zhuang[j].star;//星级
                    (*iter).zhuang[j].name=hero.zhuang[j].name;
                    (*iter).zhuang[j].textureName=hero.zhuang[j].textureName;//图片
                    (*iter).zhuang[j].defender=hero.zhuang[j].defender;
                    (*iter).zhuang[j].magicdefender=hero.zhuang[j].magicdefender;
                    (*iter).zhuang[j].hp=hero.zhuang[j].hp;
                    (*iter).zhuang[j].ap=hero.zhuang[j].ap;
            }
            iter->pos=hero.pos;
        }
    }
    updateHeros();
    saveHero();
    //saveKaPai();
    return false;
}
void GameData::readZhuangbei()
{
    CSJson::Value root;
    
    CSJson::Reader reader;
    unsigned  long nSize = 0;
    string path=CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("myzhuangbei.json");
    char* json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    if(json_document==NULL)
        return;
    map<int,ZhuangBeiType> ZhuangTypes=Config::sharedConfig()->getZhuangBei();
    if(reader.parse(json_document, root))
    {
        int size=root.size();
        for (int i=0; i<size; ++i)
        {
            ZhuangBeiType zhuang;
            int level=root[i]["level"].asInt();//等级
            int type=root[i]["type"].asInt();//类型
            zhuang.exlevel=root[i]["exlevel"].asInt();//经验
            zhuang.index=root[i]["index"].asInt();//索引
            zhuang.type=type;
            zhuang.level=level;
            zhuang.ap=0;
            zhuang.hp=0;
            zhuang.user=root[i]["user"].asInt();
            zhuang.magicdefender=0;
            zhuang.defender=0;
            map<int,ZhuangBeiType>::iterator iter = ZhuangTypes.find(type);
            if(iter!= ZhuangTypes.end())
            {
            ZhuangBeiType headtype=iter->second;
            zhuang.star=headtype.star;//星级
            zhuang.name=headtype.name;
            zhuang.hp=headtype.hp+headtype.hp*level/10;
            zhuang.ap=headtype.ap+headtype.ap*level/10;
            zhuang.textureName=headtype.textureName;//图片
            zhuang.defender=headtype.defender+headtype.defender*level/10;
            zhuang.magicdefender=headtype.magicdefender+headtype.magicdefender*level/10;
            m_ZhuangBeis.push_back(zhuang);
            }
           
        }
    }
}
void GameData::updateZhuang(ZhuangBeiType zhuang)
{
    vector<ZhuangBeiType>::iterator iter;
	for (iter = m_ZhuangBeis.begin(); iter != m_ZhuangBeis.end();iter++)
    {
        if(zhuang.index==iter->index)
        {
            iter->level+=1;
            if(zhuang.user>=0)
            {
                vector<HeroType>::iterator iterhero;
                for (iterhero = m_Heros.begin(); iterhero != m_Heros.end();iterhero++)
                {
                    for(int i=0;i<6;i++)
                    {
                       if(iterhero->zhuang[i].index==zhuang.index)
                      {
                          iterhero->zhuang[i].level+=1;
                      }
                    }
                }
            }
        }
    }
    saveZhuangBei();
    updateHeros();
}
void GameData::updateHeros()
{
    map<int,HeroType> HeroTypes=Config::sharedConfig()->getHerosType();
    map<int,ZhuangBeiType> ZhuangTypes=Config::sharedConfig()->getZhuangBei();
    vector<HeroType>::iterator iter;
    for (iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    {
        map<int,HeroType>::iterator iterHero = HeroTypes.find(iter->type);
        if(iterHero!= HeroTypes.end())
        {
            HeroType herotype=iterHero->second;
            iter->hp=(herotype.hp+herotype.hp*iter->level/10)*(1+iter->exlevel/10.0);//卡牌总血量
            iter->ap=(herotype.ap+herotype.ap*iter->level/10)*(1+iter->exlevel/10.0);//卡牌总攻击
            iter->totalap=iter->ap;
            iter->totalhp=iter->hp;
            iter->totalmagicdefend=0;
            iter->totaldefend=0;
            for(int j=0;j<6;j++)
            {
                if(iter->zhuang[j].user>=0)
                {
                int level=iter->zhuang[j].level;
                int type=iter->zhuang[j].type;
                map<int,ZhuangBeiType>::iterator iterZhuang = ZhuangTypes.find(type);
                if(iterZhuang!= ZhuangTypes.end())
                {
                    ZhuangBeiType headtype=iterZhuang->second;
                    iter->zhuang[j].defender=headtype.defender+headtype.defender*level/10;
                    iter->zhuang[j].magicdefender=headtype.magicdefender+headtype.magicdefender*level/10;
                    iter->zhuang[j].hp=headtype.hp+headtype.hp*level/10;
                    iter->zhuang[j].ap=headtype.ap+headtype.ap*level/10;
                    iter->totalap+=iter->zhuang[j].ap;
                    iter->totalhp+=iter->zhuang[j].hp;
                    iter->totaldefend+=iter->zhuang[j].defender;
                    iter->totalmagicdefend+=iter->zhuang[j].magicdefender;

                }
                }
            }
        }

    }
}
void GameData::saveZhuangBei()
{
    string path=CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("myzhuangbei.json");
    CSJson::Value root;
    CSJson::Value person;
    vector<ZhuangBeiType>::iterator iter;
	for (iter = m_ZhuangBeis.begin(); iter != m_ZhuangBeis.end();iter++)
    {
        person["level"] =iter->level;//等级
        person["exlevel"] =iter->exlevel;//品介
        person["type"] =iter->type;//类型
        person["index"] =iter->index;//索引
        person["user"] =iter->user;//英雄装备
        root.append(person);
    }
    CSJson::FastWriter fw ;
    std::string json_file = fw.write(root);
    //CCLOG("wanna save file path = %s",path.c_str());
    //创建一个文件指针
    //路径、模式
    FILE* file = fopen(path.c_str(), "wb");
    if (file)
    {
        fputs(json_file.c_str(),file);
        fclose(file);
    }
}
void GameData::saveHero()
{
    string path=CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("myhero.json");
    CSJson::Value root;
    CSJson::Value person;
    vector<HeroType>::iterator iter;
	for (iter = m_Heros.begin(); iter != m_Heros.end();iter++)
    {
    person["level"] =iter->level;//等级
    person["exlevel"] =iter->exlevel;//品介
    person["type"] =iter->type;//类型
    person["xp"] =iter->xp;//经验
    person["pos"]=iter->pos;//位置
    person["index"]=iter->index;//位置
    person["zhuang0"]=iter->zhuang[0].type*1000+iter->zhuang[0].level;//头盔
    person["zhuang1"]=iter->zhuang[1].type*1000+iter->zhuang[1].level;//盔甲
    person["zhuang2"]=iter->zhuang[2].type*1000+iter->zhuang[2].level;//武器
    person["zhuang3"]=iter->zhuang[3].type*1000+iter->zhuang[3].level;//宝物
    person["zhuang4"]=iter->zhuang[4].type*1000+iter->zhuang[4].level;//鞋子
    person["zhuang5"]=iter->zhuang[5].type*1000+iter->zhuang[5].level;//坐骑
    person["index0"]=iter->zhuang[0].index;//头盔
    person["index1"]=iter->zhuang[1].index;//盔甲
    person["index2"]=iter->zhuang[2].index;//武器
    person["index3"]=iter->zhuang[3].index;//宝物
    person["index4"]=iter->zhuang[4].index;//鞋子
    person["index5"]=iter->zhuang[5].index;//坐骑
    root.append(person);
    }
    CSJson::FastWriter fw ;
    std::string json_file = fw.write(root);
    //CCLOG("wanna save file path = %s",path.c_str());
    //创建一个文件指针
    //路径、模式
    FILE* file = fopen(path.c_str(), "wb");
    if (file)
    {
        fputs(json_file.c_str(),file);
        fclose(file);
    }
}
vector<ZhuangBeiType> GameData::getZhuangbei()
{
    return m_ZhuangBeis;
}
vector<HeroType> GameData::getHeros()
{
    return m_Heros;
}
 void GameData::setMoney(int money)
{
    mMoney=money;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("money", money);
    CCUserDefault::sharedUserDefault()->flush();
}
void GameData::setCoin(int coin)
{
    mCoin=coin;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("coin", coin);
    CCUserDefault::sharedUserDefault()->flush();
}
void GameData::setData(int money,int xp)
{
    mMoney=money;
    mxp=xp;
    int totalxp=getexp(1.1,mlevel);
    if(mxp>=totalxp)
    {
        mxp-=totalxp;
        mlevel++;
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey("level", mlevel);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("money", money);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("xp", xp);
    CCUserDefault::sharedUserDefault()->flush();
}
int GameData::getexp(float x, int n)
{
    if(n == 0)
    {
        return LEVELXP;
    }
    
    return x * getexp(x, n-1);
}
bool GameData::IsSort(int arr[], int length)
{
    int playcard[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        playcard[i] = i;
    }
    int count = 0;
    int max = MINVALUE;
    int min = MAXVALUE;
    int hashTab[SIZE] = {0};
    for (char i = 0; i < length; i++)
    {
        if (0 == arr[i])
        {
            count++;
            continue;
        }
        if (max < arr[i])
        {
            max = arr[i];
        }
        if (min > arr[i])
        {
            min = arr[i];
        }
        hashTab[arr[i]]++;
    }
    for (char i = 0; i < length; i++) //扑克牌有重复，直接返回false
    {
        if (hashTab[arr[i]] > 1)
        {
            return false;
        }
    }
    
    if (0 == count && max - min == 4)  //1、没有大小王，最大值与最小值相差4，扑克牌才能连续
    {
        return true;
    }
    else if (1 == count && ((max - min == 4) || (max - min == 3)))  //2、一个大小王，最大值与最小值相差4或者3，扑克牌都能连续
    {
        return true;
    }
    else if ((2 == count && ((max - min == 4) || (max - min == 3)
                             || (max - min == 2))))                              //3、两个大小王，最大值与最小值相差4或者3或者2，扑克牌都能连续
    {
        return true;
    }
    
    return false;
}