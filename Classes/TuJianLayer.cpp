//
//  TuJianLayer.cpp
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#include "TuJianLayer.h"
#include "HeroInfoLayer.h"
#include "Config.h"
TuJianLayer::TuJianLayer()
{
	init();
}
TuJianLayer::~TuJianLayer()
{
	
}
bool TuJianLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    m_pUiLayer=UILayer::create();
    addChild(m_pUiLayer,1);
    
    UIImageView * imagebg=UIImageView::create();
    setTouchEnabled(true);
    imagebg->setTexture("herolistbg.png");
    imagebg->setPosition(ccp(winSize.width/2, winSize.height/2));
    m_pUiLayer->addWidget(imagebg);
    
    UIButton* button = UIButton::create();
    button->setTag(0);
    button->setTouchEnable(true);
    button->loadTextures("tianbutton1.png", "tianbutton2.png", "");
    button->setPosition(ccp(20+button->getRect().size.width/2,winSize.height/2+250));
    button->addReleaseEvent(this, coco_releaseselector(TuJianLayer::menuPauseCallback));
    m_pUiLayer->addWidget(button);
    
    UIButton* button1 = UIButton::create();
    button1->setTouchEnable(true);
    button1->setTag(1);
    button1->loadTextures("dibutton1.png", "dibutton2.png", "");
    button1->setPosition(ccp(20+button1->getRect().size.width+120,winSize.height/2+250));
    button1->addReleaseEvent(this, coco_releaseselector(TuJianLayer::menuPauseCallback));
    m_pUiLayer->addWidget(button1);
    
    
    scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,500));
    scrollView->setPosition(ccp(0,winSize.height/2-280));
    m_pUiLayer->addWidget(scrollView);
    menuPauseCallback(button);
    //ReadJson();
    UIButton * btn= UIButton::create();
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(TuJianLayer::close));
    btn->setTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width-60, winSize.height/2+300));
    m_pUiLayer->addWidget(btn);
    return true;
}
void TuJianLayer::close()
{
    removeFromParentAndCleanup(true);
}
void TuJianLayer::ReadJson()
{
    CCSize backgroundSize =CCSize(500,180);

    float innerWidth = scrollView->getRect().size.width;
    float innerHeight = scrollView->getRect().size.height + backgroundSize.height*12+20;
    
    scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
    
    for(int i=0;i<5;i++)
    {
    map<int,HeroType> Heros=Config::sharedConfig()->getHerosType();
    map<int,HeroType>::iterator iter = Heros.find(i);
    if(iter!= Heros.end())
    {
        HeroType herotype=iter->second;

        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures(herotype.textureName.c_str(),herotype.textureName.c_str(), "");
        button->setScale(0.3);
        button->setPosition(ccp(100*(i%5)+100, scrollView->getInnerContainerSize().height-backgroundSize.height*(i/5)-200));
        
        button->addReleaseEvent(this, coco_releaseselector(TuJianLayer::getHeroInfo));
        scrollView->addChild(button);
        button->setTag(i);
        string name=herotype.name;
        //string count=var[i]["Type1"]["Count"].toStyledString();
        UILabel *label=UILabel::create();
        label->setFontSize(32);
        label->setText(name.c_str());
        label->setPosition(ccp(100*(i%5)+100, scrollView->getInnerContainerSize().height-backgroundSize.height*(i/5)-200-button->getRect().size.height/2));
        scrollView->addChild(label);
    }
        //printf("str===%s",count.c_str());
    }
}
void TuJianLayer::menuPauseCallback(CCObject *sender)
{
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIButton* button =(UIButton*)sender;
    int tag=button->getTag();
    scrollView->removeAllChildrenAndCleanUp(true);
    CCSize backgroundSize =CCSize(500,180);
    if(tag==0)
    {
        scrollView->setInnerContainerSize(CCSizeMake(winSize.width/2,12*180+20));
        for(int i=0;i<36;i++)
        {
            map<int,HeroType> Heros=Config::sharedConfig()->getHerosType();
            map<int,HeroType>::iterator iter = Heros.find(i);
            if(iter!= Heros.end())
            {
                HeroType herotype=iter->second;
                UIImageView * imagebg=UIImageView::create();
                char strName[32];
                sprintf(strName,"head%d.png",i);
                imagebg->setTexture(strName);
                scrollView->addChild(imagebg);
                imagebg->setPosition(ccp(winSize.width/2+200*(i%3-1), scrollView->getInnerContainerSize().height-backgroundSize.height*(i/3)-100));
                
//                CCTexture2D *texture=CCTextureCache::sharedTextureCache()->addImage("headbk4.png");
//                CCSprite *bgsp=CCSprite::createWithTexture(texture);
//                bgsp->setPosition(ccp(imagebg->getPosition().x,imagebg->getPosition().y-64));
//                scrollView->add(bgsp);
                
                UIButton* button = UIButton::create();
                button->setTouchEnable(true);
                button->setTextures("headbk4.png","headbk4.png", "");
                button->setPosition(imagebg->getPosition());
                button->addReleaseEvent(this, coco_releaseselector(TuJianLayer::getHeroInfo));
                scrollView->addChild(button);

                button->setTag(i);
                string name=herotype.name;
                UILabel *label=UILabel::create();
                label->setFontName("STKaiti");
                label->setFontSize(36);
                label->setText(name.c_str());
                label->setPosition(ccp(winSize.width/2+200*(i%3-1), scrollView->getInnerContainerSize().height-backgroundSize.height*(i/3)-120-64));
                scrollView->addChild(label);
            }
        }
    }
    else if(tag==1)
    {
        scrollView->setInnerContainerSize(CCSizeMake(winSize.width/2,25*180+20));
        for(int i=36;i<=108;i++)
        {
            map<int,HeroType> Heros=Config::sharedConfig()->getHerosType();
            map<int,HeroType>::iterator iter = Heros.find(i);
            if(iter!= Heros.end())
            {

                HeroType herotype=iter->second;
                UIImageView * imagebg=UIImageView::create();
                char strName[32];
                sprintf(strName,"head%d.png",i);
                imagebg->setTexture(strName);
                scrollView->addChild(imagebg);
                imagebg->setPosition(ccp(winSize.width/2+200*(i%3-1), scrollView->getInnerContainerSize().height-backgroundSize.height*((i-36)/3)-100));
                UIButton* button = UIButton::create();
                button->setTouchEnable(true);
                button->loadTextures("headbk4.png","headbk4.png", "");
                button->setPosition(imagebg->getPosition());
                button->addReleaseEvent(this, coco_releaseselector(TuJianLayer::getHeroInfo));
                scrollView->addChild(button);
                imagebg->setPosition(button->getPosition());
                button->setTag(i);
                string name=herotype.name;
                //string count=var[i]["Type1"]["Count"].toStyledString();
                UILabel *label=UILabel::create();
                label->setFontSize(36);
                label->setFontName("STKaiti");
                label->setText(name.c_str());
                label->setPosition(ccp(winSize.width/2+200*(i%3-1), scrollView->getInnerContainerSize().height-backgroundSize.height*((i-36)/3)-120-button->getRect().size.height/2));
                scrollView->addChild(label);
            }
            //printf("str===%s",count.c_str());
        }
    }
}
void TuJianLayer::getHeroInfo(CCObject *sender)
{
    UIButton *btn=(UIButton*)sender;
    HeroInfoLayer *info=new HeroInfoLayer();
    map<int,HeroType> Heros=Config::sharedConfig()->getHerosType();
    int tag=btn->getTag();
    HeroType herodata;
    map<int,HeroType>::iterator iter = Heros.find(tag);
        if(iter!= Heros.end())
        {
            HeroType herotype=iter->second;
            herodata.exlevel=0;
            herodata.level=0;
            herodata.name=herotype.name;
            herodata.type=herotype.type;
            herodata.starname=herotype.starname;
            herodata.exname=herotype.exname;
            herodata.skillsname=herotype.skillsname;
            herodata.textureName=herotype.textureName;//英雄图片
            herodata.card=herotype.card;//花色
            herodata.number=herotype.number;//数字
            herodata.hp=herotype.hp;//卡牌总血量
            herodata.ap=herotype.ap;//卡牌总攻击
            herodata.magic=herotype.magic;
            herodata.defend=0;
            herodata.magicdefend=0;
            herodata.totaldefend=0;
            herodata.totalmagicdefend=0;
            herodata.skillsid=herotype.skillsid;
            herodata.attackid=herotype.attackid;
            herodata.totalap=herotype.ap;
            herodata.totalhp=herotype.hp;
            herodata.des=herotype.des;
        }
    info->init(herodata);
    addChild(info,10);
}