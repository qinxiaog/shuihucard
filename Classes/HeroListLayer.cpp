//
//  HeroListLayer.cpp
//  kapai
//
//  Created by qin on 13-12-20.
//
//

#include "HeroListLayer.h"
#include "GameData.h"
#include "ShengJiLayer.h"
HeroListLayer::HeroListLayer()
{
	
}
HeroListLayer::~HeroListLayer()
{
	
}
bool HeroListLayer::init(HeroType hero,int type)
{
    if(!CCLayer::init()){
        return false;
    }
    m_oldHero=hero;
    mindex=type;
    getHeros();
    return true;
}
void HeroListLayer::getHeros()
{
    UILayer *m_pUiLayer=UILayer::create();
    addChild(m_pUiLayer,1);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIImageView* imagehead= UIImageView::create();
    imagehead->setTexture("herolistbg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imagehead);
    
    UIScrollView* scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));
    //CCSize backgroundSize =CCSize(500,200);
    scrollView->setPosition(ccp(0,winSize.height/2-380));
    m_pUiLayer->addWidget(scrollView);
    
    int j=-1;
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for(int i=0;i<Heros.size();i++)
    {
        HeroType hero=Heros[i];
        if(hero.pos<=0||mindex==-1)
        {
            j++;
            UIImageView* imageView = UIImageView::create();
            imageView->setTexture("cellbg.png");
            float innerWidth = scrollView->getRect().size.width;
            float innerHeight = scrollView->getRect().size.height + imageView->getRect().size.height*Heros.size();
            
            scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
            
            int imageHeight=imageView->getRect().size.height;
            imageView->setPosition(ccp(innerWidth /2,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            scrollView->addChild(imageView);
            
            UIImageView* imagebg= UIImageView::create();
            imagebg->setTexture("headbk4.png");
            imagebg->setPosition(ccp(120,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            scrollView->addChild(imagebg);
            
            UIImageView* imagehead= UIImageView::create();
            char strImage[32];
            sprintf(strImage,"head%d.png",hero.type);
            imagehead->setTexture(strImage);
            //imagehead->setScale(0.2);
            imagehead->setPosition(ccp(120,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            scrollView->addChild(imagehead);
            
            UILabel *namelabel=UILabel::create();
            char strName[32];
            sprintf(strName,"%s",hero.name.c_str());
            namelabel->setFontSize(32);
            namelabel->setText(strName);
            namelabel->setColor(ccBLACK);
            namelabel->setPosition(ccp(winSize.width/2-50,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/3));
            scrollView->addChild(namelabel);
            
            UILabel *label=UILabel::create();
            char strlevel[32];
            sprintf(strlevel,"Lv:%d",hero.level);
            label->setFontSize(32);
            label->setText(strlevel);
            label->setColor(ccBLACK);
            label->setPosition(ccp(winSize.width/2+50,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/3));
            scrollView->addChild(label);
            
            UIImageView* imagehp= UIImageView::create();
            imagehp->setTexture("heart.png");
            imagehp->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(imagehp);
            
            char str[32];
            sprintf(str,"%d",hero.hp);
            UILabel *hplabel=UILabel::create();
            hplabel->setText(str);
            hplabel->setColor(ccRED);
            hplabel->setFontSize(24);
            hplabel->setPosition(ccp(winSize.width/2-40,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(hplabel);
            
            UIImageView* imageap= UIImageView::create();
            imageap->setTexture("swordicon.png");
            imageap->setPosition(ccp(winSize.width/2+30,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(imageap);
            
            sprintf(str,"%d",hero.ap);
            UILabel *aplabel=UILabel::create();
            aplabel->setFontSize(24);
            aplabel->setText(str);
            aplabel->setColor(ccRED);
            aplabel->setPosition(ccp(winSize.width/2+90,scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight*2/3));
            scrollView->addChild(aplabel);
            
            UIButton* button = UIButton::create();
            button->setTouchEnable(true);
            if(mindex==-1)//升级
            {
                button->loadTextures("heroup1.png", "heroup2.png", "");
                button->addReleaseEvent(this, coco_releaseselector(HeroListLayer::menuPauseCallback));
            }
            else if(mindex>0)//换将
            {
                button->loadTextures("changhero1.png", "changhero2.png", "");
                button->addReleaseEvent(this, coco_releaseselector(HeroListLayer::menuCallback));
            }
            else if(mindex==-2)//英雄上阵
            {
                button->loadTextures("changhero1.png", "changhero2.png", "");
                button->addReleaseEvent(this, coco_releaseselector(HeroListLayer::menuAddhero));
            }
            button->setPosition(ccp(winSize.width-120, scrollView->getInnerContainerSize().height-imageHeight*j-imageHeight/2));
            button->setTag(hero.index);
            scrollView->addChild(button);
        }
        
    }
    UIButton * btn= UIButton::create();
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(HeroListLayer::close));
    btn->setTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width-60, winSize.height/2+300));
    m_pUiLayer->addWidget(btn);
}
void HeroListLayer::close()
{
    removeFromParentAndCleanup(true);
}
void HeroListLayer::menuAddhero(CCObject *sender)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    UIButton* button=(UIButton*)sender;
    int tag=button->getTag();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    
    HeroType hero;
    for(int j=0;j<Heros.size();j++)
    {
        if(tag==Heros[j].index)
        {
            hero=Heros[j];
        }
    }
    for(int j=0;j<Heros.size();j++)
    {
        if(Heros[j].pos>0&&hero.type==Heros[j].type)
        {

            CCSprite *bg=CCSprite::create("tipbg.png");
            bg->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(bg,1);
            CCActionInterval *action0=CCFadeOut::create(2);
            bg->runAction(action0);
            char str[32];
            sprintf(str,"相同英雄不可同时上阵");
            CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
            tiplabel->setColor(ccRED);
            tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(tiplabel,100);
            CCActionInterval *action=CCFadeOut::create(2);
            tiplabel->runAction(action);
            return;
        }
    }
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_ADD_HERO, (CCObject*)(intptr_t)hero.index);
    this->removeFromParentAndCleanup(true);
}
void HeroListLayer::menuCallback(CCObject *sender)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    UIButton* button=(UIButton*)sender;
    int tag=button->getTag();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();

    HeroType hero;
    for(int j=0;j<Heros.size();j++)
    {
        if(tag==Heros[j].index)
        {
            hero=Heros[j];
        }
    }
    for(int j=0;j<Heros.size();j++)
    {
        if(Heros[j].pos>0&&hero.type==Heros[j].type)
        {
            
            CCSprite *bg=CCSprite::create("tipbg.png");
            bg->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(bg,1);
            CCActionInterval *action0=CCFadeOut::create(2);
            bg->runAction(action0);
            char str[32];
            sprintf(str,"相同英雄不可同时上阵");
            CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
            tiplabel->setColor(ccRED);
            tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
            addChild(tiplabel,100);
            CCActionInterval *action=CCFadeOut::create(2);
            tiplabel->runAction(action);
            return;
        }
    }
    GameData::shareGameData()->changeHero(m_oldHero,hero);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_CHANGE_HERO, (CCObject*)(intptr_t)hero.index);
    this->removeFromParentAndCleanup(true);
}
void HeroListLayer::menuPauseCallback(CCObject *sender)
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroListLayer::Heroupdate),MSG_HERO_UPDATE, NULL);
    UIButton* button=(UIButton*)sender;
    int tag=button->getTag();
    
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for(int i=0;i<Heros.size();i++)
    {
        HeroType hero=Heros[i];
        if(tag==hero.index)
        {
            ShengJiLayer *layer=new ShengJiLayer();
            layer->init(hero);
            layer->autorelease();
            addChild(layer,10);
        }
    }
}
void HeroListLayer::Heroupdate()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_HERO_UPDATE);
    removeAllChildrenWithCleanup(true);
    getHeros();
    
}