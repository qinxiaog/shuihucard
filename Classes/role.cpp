//
//  role.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-25.
//
//

#include "role.h"
#include "Effect.h"
#include "BattleScene.h"
bool role::init(HeroType hero,BattleScene* layer)
{
    if(!CCSprite::init()){
        return false;
    }
    player=layer;
    mhero=hero;
    changeHp=0;
    resName=hero.textureName;
    level=hero.level;
    chaId=0;
    mp=2;
    ap=20;
    skillId=hero.skillsid;
    attackid=hero.attackid;
    pos=hero.pos;
    resNum=0;
    curHP=hero.hp;
    totalHp=hero.hp;
    dir=0;
    attackcount=0;

    initArm(resName.c_str());
    setScale(0.45);
//    CCSprite *bg=CCSprite::create("cardbg0.png");
//    bg->setPosition(ccp(getContentSize().width/2,getContentSize().height/2));
//    //bg->setAnchorPoint(ccp(0,0));
//    bg->setScale(0.6);
//    addChild(bg,-1);
    CCSprite *barbg=CCSprite::create("barbg.png");
    addChild(barbg);
    barbg->setPosition(ccp(getContentSize().width/2,getContentSize().height/2-190));
    barbg->setScaleX(1.5);
    CCSprite *hebar=CCSprite::create("healthbar.png");
    healthBar = CCProgressTimer::create(hebar);
    healthBar->setType(kCCProgressTimerTypeBar);
    healthBar->setPercentage(100);
    healthBar->setMidpoint(ccp(0.0,1.0));
    healthBar->setBarChangeRate(ccp(1,0));
    healthBar->setPosition(ccp(getContentSize().width/2,getContentSize().height/2-190));
    healthBar->setScaleX(1.5);
    addChild(healthBar,1);
    
    schedule(schedule_selector(role::healthBarLogic));
    //printf("role==%d,%d,%s\n",hero.totalap,skillId,resName.c_str());
    return true;
    
}
void role::healthBarLogic()
{
    healthBar->setPercentage(((float)curHP/(float)totalHp) *100);
}
void role::remove()
{
    removeFromParentAndCleanup(true);
}
void role::setHp()
{
}
void role::whetherDead(){
    
}
Bullet* role::attack()
{
    int skills=skillId;
    mp+=2;
    if(mp>=4)
    {
        skills=skillId;
        mp=0;
    }
    else
    {
        skills=attackid;
    }
    CCActionInterval* rotate1 =CCRotateTo::create(0.1,30);
    
    CCEaseBounceInOut* bounce1 =CCEaseBounceInOut::create(rotate1);
    CCScaleBy *scal=CCScaleBy::create(0.1,1.2);
    
    CCRotateTo* rotate2 =CCRotateTo::create(0.1,0);
    CCScaleTo *scal2=CCScaleTo::create(0.1,0.45);
    
    CCEaseBounceInOut* bounce2 = CCEaseBounceInOut::create(rotate2);
    
    CCSequence* rotateSequence = CCSequence::create(bounce1,scal,bounce2,scal2,NULL);
    runAction(rotateSequence);

    playMusic(skills);
}
void role::playMusic(int skills)
{
    if(skills<10)//单体
    {
        SimpleAudioEngine::sharedEngine()->playEffect("attack1.mp3");
    }
    if(skills>10&&skills<100)//单体
    {
        SimpleAudioEngine::sharedEngine()->playEffect("attack0.mp3");
    }
    if(skills>=100&&skills<=200)//全体
    {
       SimpleAudioEngine::sharedEngine()->playEffect("attack2.mp3");
    }
    else if(skills>=200&&skills<300)//前排
    {
      SimpleAudioEngine::sharedEngine()->playEffect("attack3.mp3");
    }
    else if(skills>=300&&skills<400)//后排
    {
     SimpleAudioEngine::sharedEngine()->playEffect("attack4.mp3");
    }
    else if(skills>=400&&skills<500)//竖排
    {
       SimpleAudioEngine::sharedEngine()->playEffect("attack5.mp3");
    }
    
}
int role::findattackpos(int index)
{
    ///int index=7;
    if(pos<7)
    {
        CCObject *object=NULL;
        CCARRAY_FOREACH(attackarray, object)
            {
                role *r=(role*)object;

                if(index==r->pos&&(index==r->pos+3||index==r->pos+6))//优先攻击前排对面
                {
                    index=pos+3;
                    return index;
                    //r->hurt(ap,r->getPosition());
                }
                else
                {
                    if(index==9)//优先攻击前排
                    {
                        CCARRAY_FOREACH(attackarray, object)
                        {
                            index--;
                            if(index==r->pos)
                            {
                                return index;
                            }
                        }
                        index=10;
                    }
                    else if(index>9)
                    {
                        if(index==r->pos&&(index==r->pos+9||index==r->pos+6))
                        {
                            return index;
                        }
                        
                    }
                    else if(index>=12)
                    {
                        CCARRAY_FOREACH(attackarray, object)
                        {
                            index--;
                            if(index==r->pos)
                            {
                                return index;
                            }
                        }
                    }
                    
                }
            }
        index++;
        findattackpos(index);
    }
    return index;
}
Bullet* role::attackRole(CCArray *array)
{
    attackarray=array;
    int skills=skillId;
    mp+=2;
    if(mp>=4)
    {
        skills=skillId;
        mp=0;
    }
    else
    {
        skills=attackid;
    }
    //printf("index===%d\n",index);
    attackcount++;
    CCRect rect = CCRectZero;
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCRect mBulletCollisionRect=CCRect(60,0,120,180);
    DirectState mDirState=UP;
    //    CCRotateBy *rotaBy1 = CCRotateBy::create(1, 30);
    //    runAction(CCSequence::create(rotaBy1,NULL));
    CCActionInterval* rotate1 =CCRotateTo::create(0.1,30);
    
    CCEaseBounceInOut* bounce1 =CCEaseBounceInOut::create(rotate1);
    CCScaleBy *scal=CCScaleBy::create(0.1,1.2);
    
    CCRotateTo* rotate2 =CCRotateTo::create(0.1,0);
    CCScaleTo *scal2=CCScaleTo::create(0.1,0.45);
    
    CCEaseBounceInOut* bounce2 = CCEaseBounceInOut::create(rotate2);
    
    CCSequence* rotateSequence = CCSequence::create(bounce1,scal,bounce2,scal2,NULL);
    runAction(rotateSequence);
    
    playMusic(skills);
//	Bullet* bptr = new Bullet(true,mhero.magic,
//                              1,mhero.totalap, rect,mDirState);
//    return bptr;
}
void role::hurt(int skills,int hp,CCPoint from,CCPoint pt)
{
    curHP-=hp;
    changeHp=hp;
    this->pt=pt;
    hurtEffect(skills,from,pt);
    CCCallFuncN *removeFunc =  CCCallFuncN::create(this, callfuncN_selector(role::addFont));
    float  time=GameData::shareGameData()->speed/5.0;
    CCSequence *sq=CCSequence::create(CCDelayTime::create(time),removeFunc, NULL);
    runAction(sq);
    //addFont(hp,pt);
}
void role::addFont(CCObject *object)
{
    CCLabelAtlas* label2 = new CCLabelAtlas();
    label2->initWithString("0123456789", "fonts.png",42,60,'0');
    this->getParent()->addChild(label2, 2, 2);
   
    char str[32];
    sprintf(str, "%d",changeHp);
    label2->setString(str);
    label2->setPosition(ccp(pt.x-strlen(str)*21,pt.y-15));
    float time=GameData::shareGameData()->speed/10.0;
    CCActionInterval* fade = CCFadeOut::create(time);

    CCActionInterval* delay = CCDelayTime::create(time);
    CCSequence* seq = CCSequence::create(delay,fade,NULL);
    //CCAction* repeat = CCRepeat::create( seq );
    label2->runAction(seq);
    label2->autorelease();
    player->updateRole();
}
void role::hurtEffect(int skills,CCPoint from,CCPoint pt)
{
    Effect *effect = Effect::create();
    int index=1;
    switch (skills)
    {
        case 1:
            index=1;
            break;
        case 2:
            index=2;
            break;
        case 401:
            index=3;
            break;
        case 4:
            index=4;
            break;
        case 101:
            index=5;
            break;
        case 201:
            index=6;
            break;
        case 11:
            index=7;
            break;
        case 301:
            index=8;
            break;
        case 303:
            index=6;
            break;
        case 302:
            index=10;
            break;
        case 202:
            index=11;
            break;
        case 5:
            index=12;
            break;
        case 13:
            index=13;
            break;
        case 102:
            index=14;
            break;
        case 203:
            index=15;
            break;
        case 104:
            index=16;
            break;
        case 3:
            index=17;
            break;
        default:
            break;
    }
    if(effect)
    {
    effect->init(index);
    effect->explode(this->getParent(),from,pt);
    }
}
bool role::isDead(){
    if(curHP<=0){
        return true;
    }
    return false;
}
void role::initArm(const char *armName)
{
    initWithFile(armName);

    //setScale(0.6);
}
void role::playArm(const char *playName)
{
   
}
void role::addBlood(){
    CCSprite * blood= CCSprite::create();
    CCSprite * blood_bg=CCSprite::create();
    blood_bg->addChild(blood);
    
    
    
    
}
void role::setBloodChange(float changeBlood){
    curHP=curHP+changeBlood;
}