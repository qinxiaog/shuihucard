//
//  GameOver.cpp
//  diamond puzzle
//
//  Created by qin on 13-7-29.
//
//

#include "GameOver.h"
#include "BattleScene.h"
#include "SceneGame.h"
ccColor3B color = {250,0,0};
GameOver::GameOver(bool sucess)
{
    m_sucess=sucess;
    init();
}
GameOver::~GameOver()
{
    
}
bool GameOver::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    if(CCDirector::sharedDirector()->getWinSize().height>=960)
    {
        fontsize=36;
        h=80;
    }
    else
    {
        fontsize=18;
        h=40;
    }
    setTouchEnabled(true);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    CCSprite*   child = CCSprite::create("gameover.png");
    child->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(child,-1);
//    char strLevel[64]="Time Out";
//    char strContinue[64]="continue";
//    int i=CCApplication::sharedApplication()->getCurrentLanguage();
//    if(i==1)
//    {
//        strcpy(strLevel,"时间到");
//        strcpy(strContinue,"继续游戏");
//    }
//    CCLabelTTF* levelLabel=CCLabelTTF::create(strLevel,"CourierNewPS-BoldItalicMT",48);
//    levelLabel->setPosition(ccp(winsize.width/2, winsize.height/2+50));
//    //levelLabel->setColor(ccBLACK);
//    addChild(levelLabel);
    
    int i=CCApplication::sharedApplication()->getCurrentLanguage();
        
//        CCSprite *set=CCSprite::create("timeout_cn.png");
//        set->setPosition(ccp(winSize.width/2, winSize.height/2+20));
//        addChild(set);
    
//        CCSprite *styleSp=CCSprite::create("ok1.png");
//        styleSp->setPosition(ccp(winSize.width/2, winSize.height/2-120));
//        addChild(styleSp,2);
    CCMenuItemImage *item =CCMenuItemImage::create("ok1.png","ok2.png",this, menu_selector(GameOver::nextCallback));
    CCMenu *menu =CCMenu::create(item,NULL);
    this->addChild(menu,1);
    
    if(!m_sucess)
    {
        CCSprite* child = CCSprite::create("fail.png");
        child->setPosition(ccp(winSize.width/2,winSize.height/2));
        this->addChild(child,1);
    }
    menu->setPosition(ccp(winSize.width/2,winSize.height/2-210));
    SimpleAudioEngine::sharedEngine()->playEffect("gameover.mp3");
//    CCLabelTTF* continueLabel=CCLabelTTF::create(strContinue,"CourierNewPS-BoldItalicMT",48);
//    continueLabel->setPosition(ccp(winsize.width/2, winsize.height/2-120));
//    addChild(continueLabel,1);
    return  true;
}
void GameOver::setData(int xp,int money,int card,int sword)
{
     int mxp=GameData::shareGameData()->mxp+xp;
     int mmoney=GameData::shareGameData()->mMoney+money;
    GameData::shareGameData()->setData(mmoney, mxp);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    CCString *str=CCString::createWithFormat("获得银子:%d",money);
    CCLabelTTF *moneyLabel=CCLabelTTF::create();
    moneyLabel->setColor(ccBLUE);
    moneyLabel->setString(str->getCString());
    moneyLabel->setFontSize(48);
    moneyLabel->setPosition(ccp(winSize.width/2, winSize.height/2+100));
    addChild(moneyLabel);
    
    CCString *strxp=CCString::createWithFormat("获得经验:%d",xp);
    CCLabelTTF *xpLabel=CCLabelTTF::create();
    xpLabel->setColor(ccBLUE);
    xpLabel->setString(strxp->getCString());
    xpLabel->setFontSize(48);
    xpLabel->setPosition(ccp(winSize.width/2, winSize.height/2+50));
    addChild(xpLabel);
    if(card!=-1)
    {
        if(card==108)
        {
            card=arc4random()%108;
        }
        if(card==109)
            card=arc4random()%72+36;
        map<int,HeroType> HeroTypes=Config::sharedConfig()->getHerosType();
        HeroType herodata;
        map<int,HeroType>::iterator iterHero = HeroTypes.find(card);
        if(iterHero!= HeroTypes.end())
        {
            HeroType herotype=iterHero->second;
            herodata.name=herotype.name;
            herodata.textureName=herotype.textureName;//英雄图片
            CCSprite *imagebg=CCSprite::create("headbk4.png");
            imagebg->setPosition(ccp(winSize.width/2,winSize.height/2-90));
            addChild(imagebg);
            char strname[32];
            sprintf(strname,"head%d.png",card);
            CCSprite *image=CCSprite::create(strname);
            image->setPosition(ccp(winSize.width/2,winSize.height/2-90));
            //image->setScale(0.3);
            addChild(image);
        }

    }
    if(sword!=-1)
    {
        map<int,ZhuangBeiType> zhuangTypes=Config::sharedConfig()->getZhuangBei();
        ZhuangBeiType data;
        int index=sword/1000;
        map<int,ZhuangBeiType>::iterator iter=zhuangTypes.find(index);
        if(iter!= zhuangTypes.end())
        {
            ZhuangBeiType type=iter->second;
            data.index=zhuangTypes.size();
            data.name=type.name;
            data.textureName=type.textureName;//英雄图片
            CCSprite *imagebg=CCSprite::create("headbk4.png");
            imagebg->setPosition(ccp(winSize.width/2,winSize.height/2-90));
            addChild(imagebg);
            CCSprite *image=CCSprite::create(data.textureName.c_str());
            image->setPosition(ccp(winSize.width/2,winSize.height/2-90));
            addChild(image);
        }
    }
}
void GameOver::back(CCObject *sender)
{
    // CCScene *sc=[[CCDirector sharedDirector] runningScene];
    this->removeAllChildrenWithCleanup(true);
    
//    CCScene *pScene = MainMenuLayer::scene();
//    
//    CCDirector *pDirector=CCDirector::sharedDirector();
//    pDirector->replaceScene(pScene);
}
void GameOver::nextCallback(CCObject *sender)
{
    // CCScene *sc=[[CCDirector sharedDirector] runningScene];
//    GameMediator *m=GameMediator::sharedMediator();
//    int maplevel=m->getmaplevel();
//    maplevel++;
//    m->setmaplevel(maplevel);
//    this->removeAllChildrenWithCleanup(true);
//    CCScene *pScene = MainLayer::scene();
//    
//    CCDirector *pDirector=CCDirector::sharedDirector();
//    pDirector->replaceScene(pScene);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MENUVISIBLE);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_BATTLE, (CCObject*)(intptr_t)0);
    this->removeAllChildrenWithCleanup(true);
}
void GameOver::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
    
}
bool GameOver::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void GameOver::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void GameOver::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}