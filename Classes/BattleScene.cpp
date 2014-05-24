//
//  BattleScene.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "BattleScene.h"
#include "GameData.h"
#include "GameOver.h"
#include "Effect.h"
#include "Config.h"
#include "role.h"
BattleScene::BattleScene()
{
    
}
BattleScene::~BattleScene()
{
    RoleArr->release();
    ene_Arr->release();
    deadArr->release();
}
bool BattleScene::init(Value datas){
    if (!CCLayer::init()) {
        
        return false;
    }
    ene_Arr=CCArray::create();
    ene_Arr->retain();
    deadArr=CCArray::create();
    deadArr->retain();
    RoleArr=CCArray::create();
    RoleArr->retain();
    begintime=3;
    rounds=0;
    roleIndex=1;
    enemyIndex=7;
    bTurn=true;
    bGameover=false;
    msucess=false;
    fighttime=GameData::shareGameData()->speed;
    mspeed=1;
    setTouchEnabled(true);
    
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    char strbg[32];
    int number=arc4random()%3;
    sprintf(strbg,"warbg%d.png",number);
    
    CCSprite * sp= CCSprite::create(strbg);
    sp->setPosition(ccp(winSize.width/2, winSize.height/2));
    sp->setScaleX(winSize.width/640);
    sp->setScaleY(winSize.height/960);
    this->addChild(sp);
    initRole();

    money=datas["coin"].asInt();
    mxp=datas["xp"].asInt();
    card=datas["card"].asInt();
    zhuangbei=datas["sword"].asInt();
    initAttackData(datas);
    //Effect::sharedExplosion();
    char strmusic[32];
    int r=arc4random()%3;
    sprintf(strmusic,"warbg%d.mp3",r);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(strmusic,true);
    CCMenuItemImage *item =CCMenuItemImage::create("menu1.png","menu2.png",this, menu_selector(BattleScene::changeSpeed));
    item->setTag(111);
    CCMenu *menu =CCMenu::create(item,NULL);
    menu->setPosition(ccp(40,30));
    this->addChild(menu,1);
    scheduleUpdate();
    schedule(schedule_selector(BattleScene::BeginFight));
    return true;
}
void BattleScene::getJsonData(const char *data){
    CSJson::Reader reader;
    CSJson::Value root;
    CSJson::Value datas;
    if(reader.parse(data, root)){
        datas=root["data"];
        alluseValue=datas;
       
    }
}
void BattleScene::initAttackData(Value datas)
{
    mapid=GameData::shareGameData()->mapId;
    subid=GameData::shareGameData()->subMapId;

    map<int,EnemyType> cardTypes=Config::sharedConfig()->getEnemyType();
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    int level=datas["chalevel"].asInt();
    for (int i=0; i<6; i++)
    {
        char str[32];
        sprintf(str,"chaPos%d",i+1);
        int type=datas["startData"][str].asInt();
        type-=200;
        map<int,EnemyType>::iterator iterHero = cardTypes.find(type);
        if(iterHero!= cardTypes.end())
        {
        EnemyType cardType=iterHero->second;
        cardType.level=level;
//        CCSprite *bg=CCSprite::create("cardbg0.png");
//        bg->setScale(0.3);
//        addChild(bg,-1);
        role * ro=new role();
        
            
            HeroType hero;
            hero.name=cardType.name;
            hero.textureName=cardType.textureName;//英雄图片
            //printf("name====%s",cardType.textureName.c_str());
            hero.card=cardType.card;//花色
            hero.number=cardType.number;//数字
            hero.hp=cardType.hp+cardType.hp*cardType.level/5;//卡牌总血量
            hero.ap=cardType.ap+cardType.ap*cardType.level/5;//卡牌总攻击
            hero.totalap=hero.ap;
            hero.totalhp=hero.hp;
            hero.totaldefend=cardType.defend+cardType.level*cardType.defend/10;
            hero.totalmagicdefend=cardType.magicdefend+cardType.level*cardType.magicdefend/10;
            hero.skillsid=cardType.skillsid;
            hero.attackid=cardType.attackid;
        ro->init(hero,this);
        ro->pos=i+7;
        ro->autorelease();
        this->addChild(ro);
        ro->setPosition(ccp(110+210*((i)%3),winSize.height/2+210*((i)/3)+120));
        ene_Arr->addObject(ro);
        }        
    }
    chaBattleId=0;
    //runAttack();
}
void BattleScene::BeginFight(float dt)
{
    if(RoleArr->count()<=0||ene_Arr->count()<=0)
        bGameover=true;
    if(bGameover)
    {
        if(RoleArr->count()>0)
        msucess=true;
        unschedule(schedule_selector(BattleScene::BeginFight));
        return;
    }
    begintime-=dt;
    if (begintime<=0)
    {
        begintime=fighttime;
        role *r=getAttackRole(roleIndex);
        if(r&&bTurn)
        {
            r->attack();
            attack(r,7);
            bTurn=false;
        }
        else
        {
            role *enemy=getEnemyRole(enemyIndex);
            if(enemy)
            {
            enemy->attackRole(RoleArr);
            enemyattack(enemy,1);
            }
            else
            {
             begintime=-1;
            }
            bTurn=true;
            roleIndex++;
            enemyIndex++;
            
            if(enemyIndex>12)
            {
                enemyIndex=7;
                roleIndex=1;
            }
            if(roleIndex>6)
                roleIndex=1;
        }
//        CCCallFuncN *removeFunc =  CCCallFuncN::create(this, callfuncN_selector(BattleScene::updateRole));
//        CCSequence *sq=CCSequence::create(CCDelayTime::create(1),removeFunc, NULL);
//        runAction(sq);
    }

}
void BattleScene::attack(role* a,int index)
{

    CCObject *object=NULL;
    CCPoint from=a->getPosition();
    int skills=a->skillId;
    int mp=a->mp+2;
    if(mp>=4)
    {
        skills=a->skillId;
        mp=0;
    }
    else
    {
        skills=a->attackid;
    }
    if(skills<100)//单体
    {
        int attackindex=findAttackPos(a->pos, 7);//前排对面
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,8);//前排对面死
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,7);
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,9);
        }
        if (attackindex==0)
        {
            attackindex=findAttackBottomPos(a->pos,10);
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,11);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,10);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,12);//后排排对面死
        }
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            int ap=0;
            if(skills<10)
            {
                int rd=arc4random()%40+80;
                ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            }
            else
            {
                int rd=arc4random()%60+320;
                ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            }
            if(attackindex==r->pos)//优先攻击对面
            {
                r->hurt(skills,ap,from,r->getPosition());
            }
        }
    }
    if(skills>=100&&skills<=200)//全体
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            int rd=arc4random()%40+60;
            int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            r->hurt(skills,ap,from,r->getPosition());
        }
    }
    else if(skills>=200&&skills<300)//前排
    {
        bool bhead=false;
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            int rd=arc4random()%60+120;
            int ap=a->mhero.totalap*rd/100.0-r->mhero.totaldefend;
            if(r->pos<=9)
            {
                bhead=true;
                r->hurt(skills,ap,from,r->getPosition());
            }
            else if(!bhead)
            {
                r->hurt(skills,ap,from,r->getPosition());
            }
        }
    }
    else if(skills>=300&&skills<400)//后排
    {
        bool bbottom=false;
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(r->pos>=9)//前排有敌人
            {
                bbottom=true;//后排有人
            }
            
        }
        if(bbottom)
        {
            CCARRAY_FOREACH(ene_Arr, object)
            {
                role *r=(role*)object;
                int rd=arc4random()%60+120;
                int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
                if(r->pos>9)//后排
                {
                    r->hurt(skills,ap,from,r->getPosition());
                    
                }
            }
        }
        else
        {
            CCARRAY_FOREACH(ene_Arr, object)
            {
                role *r=(role*)object;
                int rd=arc4random()%60+120;
                int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
                if(r->pos<=9)//前排
                {
                    r->hurt(skills,ap,from,r->getPosition());
                    
                }
            }
        }
    }
    else if(skills>=400&&skills<500)//竖排
    {
        int attackindex=findAttackPos(a->pos, 7);//前排对面
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,8);//前排对面死
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,7);
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,9);
        }
        if (attackindex==0)
        {
            attackindex=findAttackBottomPos(a->pos,10);
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,11);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,10);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,12);//后排排对面死
        }
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(r->pos==attackindex||(attackindex+3)==r->pos)
            {
                int rd=arc4random()%40+200;
                int ap=a->mhero.totalap*rd/100.0-r->mhero.totaldefend;
                r->hurt(skills,ap,from,r->getPosition());
            }
        }
//        int index=0;
//        CCARRAY_FOREACH(ene_Arr, object)
//        {
//            role *r=(role*)object;
//            index=r->pos;
//            break;
//        }
//        CCARRAY_FOREACH(ene_Arr, object)
//        {
//            role *r=(role*)object;
//            int rd=arc4random()%40+200;
//            int ap=a->mhero.totalap*rd/100.0-r->mhero.totaldefend;
//            if(index==r->pos||(index+3)==r->pos)
//            {
//                r->hurt(skills,ap,from,r->getPosition());
//            }
//        }
    }

}
void BattleScene::updateRole()
{
    CCObject *object=NULL;
    CCARRAY_FOREACH(ene_Arr, object)
    {
        role *r=(role*)object;
        if(r->curHP<=0)
        {
            ene_Arr->removeObject(r);
            //removeChildByTag(r->pos+100);
            r->removeFromParentAndCleanup(true);
        }
    }
    CCARRAY_FOREACH(RoleArr, object)
    {
        role *r=(role*)object;
        if(r->curHP<=0)
        {
            RoleArr->removeObject(r);
            //removeChildByTag(r->pos+100);
            r->removeFromParentAndCleanup(true);
        }
    }
}
void BattleScene::enemyattack(role* a,int index)
{
    CCObject *object=NULL;
    CCPoint from=a->getPosition();
    int skills=a->skillId;
    int mp=a->mp+2;
    if(mp>=4)
    {
        skills=a->skillId;
        mp=0;
    }
    else
    {
        skills=a->attackid;
    }
    if(skills<100)//单体
    {
        int attackindex=findAttackPos(a->pos, 1);//前排对面
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,2);//前排对面死
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,1);
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,3);
        }
        if (attackindex==0)
        {
            attackindex=findAttackBottomPos(a->pos,4);
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,5);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,4);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,6);//后排排对面死
        }
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            int ap=0;
            if(skills<10)
            {
            int rd=arc4random()%40+80;
            ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            }
            else
            {
                int rd=arc4random()%60+320;
                ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            }
            if(attackindex==r->pos)//优先攻击对面
            {
                r->hurt(skills,ap,from,r->getPosition());
            }
        }
    }
    if(skills>=100&&skills<=200)//全体//60-100
    {
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            int rd=arc4random()%40+60;
            int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            r->hurt(skills,ap,from,r->getPosition());
        }
    }
    else if(skills>=200&&skills<300)//前排
    {
        bool bhead=false;
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            int rd=arc4random()%60+120;
            int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
            if(r->pos<=3)
            {
                bhead=true;
                r->hurt(skills,ap,from,r->getPosition());
            }
            else if(!bhead)
            {
                r->hurt(skills,ap,from,r->getPosition());
            }
        }
    }
    else if(skills>=300&&skills<400)//后排//120-160
    {
        bool bbottom=false;
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            if(r->pos>3)
            {
                bbottom=true;//后排有人
            }
            
        }
        if(bbottom)
        {
            CCARRAY_FOREACH(RoleArr, object)
            {
                role *r=(role*)object;
                int rd=arc4random()%60+120;
                int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
                if(r->pos>3)//后排
                {
                    r->hurt(skills,ap,from,r->getPosition());
                    
                }
            }
        }
        else
        {
            CCARRAY_FOREACH(RoleArr, object)
            {
                role *r=(role*)object;
                int rd=arc4random()%60+120;
                int ap=a->mhero.totalap*rd/100.0-r->mhero.totalmagicdefend;
                if(r->pos<=3)//前排
                {
                    r->hurt(skills,ap,from,r->getPosition());
                }
            }
        }
    }
    else if(skills>=400&&skills<500)//竖排200-240
    {
        int attackindex=findAttackPos(a->pos, 1);//前排对面
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,2);//前排对面死
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,1);
        }
        if (attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,3);
        }
        if (attackindex==0)
        {
            attackindex=findAttackBottomPos(a->pos,4);
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,5);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,4);//后排排对面死
        }
        if(attackindex==0)
        {
            attackindex=findAttackLeft(a->pos,6);//后排排对面死
        }
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            if(r->pos==attackindex||(attackindex+3)==r->pos)
            {
            int rd=arc4random()%40+200;
            int ap=a->mhero.totalap*rd/100.0-r->mhero.totaldefend;
            r->hurt(skills,ap,from,r->getPosition());
            }
        }
//        CCARRAY_FOREACH(RoleArr, object)
//        {
//            role *r=(role*)object;
//
//            if(index==r->pos||(index+3)==r->pos)
//            {
//                r->hurt(skills,ap,from,r->getPosition());
//            }
//        }
    }
}
role *BattleScene::getAttackRole(int index)
{
    CCObject *object=NULL;
    CCARRAY_FOREACH(RoleArr, object)
    {
        role *r=(role*)object;
        if(index==r->pos)
        {
            return r;
        }
    }
    return NULL;
}
role *BattleScene::getEnemyRole(int index)
{
    CCObject *object=NULL;
    CCARRAY_FOREACH(ene_Arr, object)
    {
        role *r=(role*)object;
        if(index==r->pos)
        {
            return r;
        }
    }
    return NULL;
}
int BattleScene::findAttackPos(int pos,int index)
{
    CCObject *object=NULL;
    if(pos<=3)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            
            if(index==r->pos&&index==pos+6)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=9)
        {
        return findAttackPos(pos,index);
        }
    }
    else if(pos>3&&pos<=6)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(index==r->pos&&index==pos+3)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=9)
        {
        return findAttackPos(pos,index);
        }
    }
    else if(pos>=7&&pos<=9)
    {
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            
            if(index==r->pos&&index==pos-6)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=3)
        {
            return findAttackPos(pos,index);
        }
    }
    else if(pos>9&&pos<=12)
    {
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            if(index==r->pos&&index==pos-9)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=3)
        {
            return findAttackPos(pos,index);
        }
    }
    return 0;
}
int BattleScene::findAttackBottomPos(int pos,int index)
{
    CCObject *object=NULL;
    if(pos<=3)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            
            if(index==r->pos&&index==pos+9)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=12)
          return  findAttackBottomPos(pos,index);
    }
    else if(pos>3&&pos<=6)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(index==r->pos&&index==pos+6)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=12)
          return  findAttackBottomPos(pos,index);
    }
    else if(pos>=7&&pos<=9)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            
            if(index==r->pos&&index==pos-3)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=6)
          return  findAttackBottomPos(pos,index);
    }
    else if(pos>9&&pos<=12)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(index==r->pos&&index==pos-6)//优先攻击前排对面
            {
                return index;
            }
        }
        index++;
        if(index<=6)
          return  findAttackBottomPos(pos,index);
    }
    return 0;
}
int BattleScene::findAttackLeft(int pos,int index)
{
    CCObject *object=NULL;
    if(pos<=3)
    {
        
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            
            if(index==r->pos)//优先攻击前排左边
            {
                return index;
            }
        }
    }
    else if(pos>3&&pos<=6)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(index==r->pos)//后排优先攻击前排左边
            {
                return index;
            }
        }
    }
    else if(pos>=7&&pos<=9)
    {
        
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            
            if(index==r->pos)//优先攻击前排左边
            {
                return index;
            }
        }
    }
    else if(pos>9&&pos<=12)
    {
        CCARRAY_FOREACH(RoleArr, object)
        {
            role *r=(role*)object;
            if(index==r->pos)//后排优先攻击前排左边
            {
                return index;
            }
        }
    }
    return 0;
}
int BattleScene::findAttackRight(int pos,int index)
{
    CCObject *object=NULL;
    int attackindex=index;
    if(pos<=3)
    {
        
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            
            if(attackindex==r->pos)//优先攻击前排
            {
                return attackindex;
            }
        }
        attackindex++;
        if(attackindex<=9)
          return  findAttackRight(pos,attackindex);
    }
    else if(pos>3&&pos<=6)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(index==r->pos)//后排优先攻击前排
            {
                return index;
            }
        }
        index++;
        if(index<=9)
          return  findAttackRight(pos,index);
    }
    else if(pos>=7&&pos<9)
    {
        
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            
            if(attackindex==r->pos)//优先攻击前排
            {
                return attackindex;
            }
        }
        attackindex++;
        if(attackindex<=3)
          return  findAttackRight(pos,attackindex);
    }
    else if(pos>9&&pos<=12)
    {
        CCARRAY_FOREACH(ene_Arr, object)
        {
            role *r=(role*)object;
            if(index==r->pos)//后排优先攻击前排
            {
                return index;
            }
        }
        index++;
        if(index<=3)
          return  findAttackRight(pos,index);
    }
    return 0;
}
void BattleScene::bulletUpdate(float dt)
{

}
void BattleScene::addFont(int hp,CCPoint pt)
{
    CCLabelAtlas* label2 = new CCLabelAtlas();
    label2->initWithString("0123456789", "fonts.png",21,30,'0');
    addChild(label2, 2, 2);
    label2->setPosition(pt);
    char str[32];
    sprintf(str, "%d",hp);
    label2->setString(str);
    CCActionInterval* fade = CCFadeOut::create(1.0f);
    CCActionInterval* fade2 = CCFadeOut::create(1.0f);
    CCSequence* seq = CCSequence::create(fade,NULL);
    //CCAction* repeat = CCRepeat::create( seq );
    label2->runAction(seq);
    CCSprite *addSprite=new CCSprite();
    addSprite->initWithFile("hurt.png");
    addChild(addSprite);
    addSprite->setPosition(ccp(pt.x-20,pt.y));
    addSprite->setAnchorPoint(ccp(0,0));
    CCSequence* seq2 = CCSequence::create(fade2,NULL);
    addSprite->runAction(seq2);
    
    addSprite->release();
    label2->release();
}
void BattleScene::enemyUpdate(float dt)
{
    CCObject *object=NULL;
    CCARRAY_FOREACH(RoleArr, object)
    {
        role *r=(role*)object;
			if (r->curHP<=0)
            {
                RoleArr->removeObject(r);
				r->removeFromParentAndCleanup(true);
                
			}
	}
    object=NULL;
    CCARRAY_FOREACH(ene_Arr, object)
    {
        role *r=(role*)object;
        if (r->curHP<=0)
        {
            ene_Arr->removeObject(r);
            r->removeFromParentAndCleanup(true);
        }
	}
}
void BattleScene::update(float dt)
{
   if(bGameover)
   {
    return;
   }
    if(RoleArr->count()<=0||ene_Arr->count()<=0)
    {
        bGameover=true;
        if(RoleArr->count()>0)
        {
        msucess=true;
        int i=arc4random()%20;
          if(i!=0)
          {
            card=-1;
          }
          else if(card>0)
          {
              map<int,HeroType> HeroTypes=Config::sharedConfig()->getHerosType();
              vector<HeroType> Heros=GameData::shareGameData()->getHeros();
              HeroType herodata;

              map<int,HeroType>::iterator iterHero = HeroTypes.find(card);
              if(iterHero!= HeroTypes.end())
              {
                  HeroType herotype=iterHero->second;
                  herodata.name=herotype.name;
                  herodata.textureName=herotype.textureName;//英雄图片
                  herodata.card=herotype.card;//花色
                  herodata.number=herotype.number;//数字
                  herodata.hp=herotype.hp;//卡牌总血量
                  herodata.ap=herotype.ap;//卡牌总攻击
                  herodata.skillsid=herotype.skillsid;
                  herodata.attackid=herotype.attackid;

                  herodata.type=card;
                  herodata.level=1;
                  herodata.xp=0;
                  herodata.exlevel=0;
                  herodata.pos=0;
                  
                  
                  herodata.zhuang[0].type=0;//头盔
                  herodata.zhuang[1].type=0;//盔甲
                  herodata.zhuang[2].type=0;//武器
                  herodata.zhuang[3].type=0;//宝物
                  herodata.zhuang[4].type=0;//鞋子
                  herodata.zhuang[5].type=0;//坐骑
                  herodata.zhuang[0].level=0;//头盔
                  herodata.zhuang[1].level=0;//盔甲
                  herodata.zhuang[2].level=0;//武器
                  herodata.zhuang[3].level=0;//宝物
                  herodata.zhuang[4].level=0;//鞋子
                  herodata.zhuang[5].level=0;//坐骑
              }
              GameData::shareGameData()->addKapai(herodata);
          }
          int j=arc4random()%10;
          if(j!=0)
          {
            zhuangbei=-1;
          }
          else
          {
              map<int,ZhuangBeiType> zhuangTypes=Config::sharedConfig()->getZhuangBei();
              vector<ZhuangBeiType> zhuangs=GameData::shareGameData()->getZhuangbei();
              ZhuangBeiType data;
              //printf("zhuang====%d",zhuangbei);
              int index=zhuangbei/1000;
              map<int,ZhuangBeiType>::iterator iter=zhuangTypes.find(index);
              if(iter!= zhuangTypes.end())
              {
                  ZhuangBeiType type=iter->second;
                  data.name=type.name;
                  data.textureName=type.textureName;//英雄图片
                  data.hp=type.hp;//卡牌总血量
                  data.ap=type.ap;//卡牌总攻击
                  data.star=type.star;//星级
                  data.defender=type.defender;
                  data.magicdefender=type.magicdefender;
                  
                  data.level=1;;//等级
                  data.exlevel=0;//品介
                  data.type=index;
                  data.index=zhuangs.size();//索引
                  data.user=0;//英雄装备
                  GameData::shareGameData()->addZhuangBei(data);
              }
              
          }
            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
            GameOver *over=new GameOver(msucess);
            over->setData(mxp,money,card,zhuangbei);
            addChild(over,10);
            
        }
        else
        {
            msucess=false;
            GameOver *over=new GameOver(msucess);
            addChild(over,10);
        }
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(BattleScene::removeself),MSG_BATTLE, NULL);
    }
       
    bulletUpdate(dt);
    //enemyUpdate(dt);
    
}
void BattleScene::removeself()
{

    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_BATTLE);
    removeFromParentAndCleanup(true);
}
//void BattleScene::draw()
//{
//    ccDrawRect(mrect.origin,ccp(mrect.origin.x+mrect.size.width,mrect.origin.y+mrect.size.height));
//    glLineWidth(10.0f );
//    //ccDrawRect(mrect1.origin,ccp(mrect1.origin.x+120,mrect1.origin.y+180));
//    //glLineWidth(10.0f );
//}
void BattleScene::moreAttack(){
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    //my_r->getAnimation()->stop();
    char attack[50]="";
    sprintf(attack, "%sattack",my_r->resName.c_str());
    my_r->playArm(attack);
}
void BattleScene::moreEneHurt(){
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
  // my_r->getAnimation()->stop();
    char attack[50]="";
    sprintf(attack, "%sstand",my_r->resName.c_str());
    my_r->playArm(attack);
    for (int i=0; i<ene_Arr->count(); i++) {
        role * ene_r=(role *)ene_Arr->objectAtIndex(i);
     //   ene_r->getAnimation()->stop();
        char attacked[50]="";
        sprintf(attacked, "%swound",ene_r->resName.c_str());
      //  ene_r->getAnimation()->stop();
        ene_r->playArm(attacked);
        
        if(i==ene_Arr->count()-1){
        }
        
    }

}
void BattleScene::moreWhetherDead(){

    
}


void BattleScene::runAttack(){
    
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    CCLog("%d",my_r->skillId);
    role * ene_r=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
    if(my_r->skillId==610101)
    {
        if (ene_r->dir==2)
        {
            my_r->setPosition(ccp(ene_r->getPosition().x-120, ene_r->getPosition().y));

        }else
        {
            my_r->setPosition(ccp(ene_r->getPosition().x+120, ene_r->getPosition().y));
        }
                my_r->setZOrder(my_r->getZOrder()+1);
       // my_r->getAnimation()->stop();
        char attack[50]="";
        sprintf(attack, "%sattack",my_r->resName.c_str());
        my_r->playArm(attack);
    }
    else if(my_r->skillId==2)
    {
       // my_r->getAnimation()->stop();
        char attack[50]="";
        sprintf(attack, "%sattack",my_r->resName.c_str());
        my_r->playArm(attack);
    }
    
}

void BattleScene::eneHurt(CCArmature * arm,MovementEventType type,const char * name){
    if (type == COMPLETE)
    {
    role * ene_r=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
    char attacked[50]="";
    char my_setNor[50]="";
    role * my_r=(role *)GameData::shareGameData()->roleDic->objectForKey(chaBattleId);
    if(my_r->skillId==610101){
        
        //ene_r->getAnimation()->stop();
        my_r->setPosition(my_r->oldpos);
        sprintf(attacked, "%swound",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        ene_r->setBloodChange(1000.0f);

    }else if(my_r->skillId==2){
       // ene_r->getAnimation()->stop();
        my_r->setPosition(my_r->oldpos);
        sprintf(attacked, "%swound",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        ene_r->setBloodChange(1000.0f);
    }
   // my_r->getAnimation()->stop();
    sprintf(my_setNor, "%sstand",my_r->resName.c_str());
    my_r->playArm(my_setNor);
        //getAnimation()->play(attacked);
    }
    
    
}
void BattleScene::whetherDead(CCArmature * arm,MovementEventType type,const char * name){
    if (type == COMPLETE)
    {
    role * ene_r=(role *)GameData::shareGameData()->roleDic->objectForKey(eneBattleId);
    char attacked[50]="";
    if(ene_r->isDead()){
        //ene_r->getAnimation()->stop();
        sprintf(attacked, "%sdeath",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        
        
        GameData::shareGameData()->roleDic->removeObjectForKey(eneBattleId);
        //initAttackData(alluseValue);
    }else{
       // ene_r->getAnimation()->stop();
        sprintf(attacked, "%sstand",ene_r->resName.c_str());
        ene_r->playArm(attacked);
        //initAttackData(alluseValue);
    }
    
    
    }
    
    
}
void BattleScene::changeSpeed(CCObject *sender)
{
    CCMenuItemImage *item=(CCMenuItemImage*)sender;
    mspeed++;
    if(mspeed>3)
    {
        mspeed=1;
        fighttime=3;
    }
    if(mspeed==1)
    {
        fighttime=3;
        CCSprite *sp=CCSprite::create("menu1.png");
        item->setNormalImage(sp);
        CCSprite *sp2=CCSprite::create("menu1.png");
        item->setSelectedImage(sp2);
        GameData::shareGameData()->speed=3;
    }
    else if(mspeed==2)
    {
        fighttime=2;
        CCSprite *sp=CCSprite::create("menu2.png");
        item->setNormalImage(sp);
        CCSprite *sp2=CCSprite::create("menu2.png");
        item->setSelectedImage(sp2);
        GameData::shareGameData()->speed=2;
    }
    else if(mspeed==3)
    {
        fighttime=1;
        CCSprite *sp=CCSprite::create("menu3.png");
        item->setNormalImage(sp);
        CCSprite *sp2=CCSprite::create("menu3.png");
        item->setSelectedImage(sp2);
        GameData::shareGameData()->speed=1;
    }
}

//startData
void BattleScene::initRole()
{
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int i=0; i<Heros.size(); i++)
    {
        HeroType hero=Heros[i];
        if(hero.pos>0)
        {
//        CCSprite *bg=CCSprite::create("cardbg0.png");
//        //bg->setAnchorPoint(ccp(0,0));
//        bg->setScale(0.3);
//        addChild(bg,0);
        
        
        role * ro=new role();
        ro->pos=hero.pos;
        ro->resNum=1;
        ro->curHP=hero.totalhp;
        ro->totalHp=hero.totalhp;
        ro->skillId=hero.skillsid;
        ro->attackid=hero.attackid;
        
        ro->init(hero,this);

        ro->setPosition(ccp(110+210*((ro->pos-1)%3),winSize.height/2-210*((ro->pos-1)/3)-100));
        ro->autorelease();
        this->addChild(ro);
//        bg->setTag(ro->pos+100);
//        bg->setPosition(ro->getPosition());
        RoleArr->addObject(ro);
        }
    }
}
void BattleScene::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127,true);
}
bool BattleScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void BattleScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void BattleScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
