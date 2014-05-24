//
//  HeroLayer.cpp
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#include "HeroLayer.h"
#include "ZhuangBeiLayer.h"
#include "HeroInfoLayer.h"
#include "Config.h"
#include "ShengJiLayer.h"
#include "HeroListLayer.h"
#include "QiangHuaLayer.h"
HeroLayer::HeroLayer()
{
	init();
}
HeroLayer::~HeroLayer()
{
	
}
bool HeroLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    UILayer * ul=UILayer::create();
    //ul->setPosition(ccp(0,winSize.height/2));
    this->addChild(ul);
    

    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIImageView * imagebg=UIImageView::create();
    setTouchEnabled(true);
    imagebg->addReleaseEvent(this, coco_releaseselector(HeroLayer::getHeroInfo));
    imagebg->setTexture("herobg1.png");
    imagebg->setScaleX(winSize.width/640);
    imagebg->setScaleY(winSize.height/960);
    imagebg->setPosition(ccp(winSize.width/2, winSize.height/2));
    ul->addWidget(imagebg);
    
    pageView = UIPageView::create();
    pageView->setTouchEnable(true);
    pageView->setSize(CCSize(winSize.width,winSize.height));
    ul->addWidget(pageView);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroLayer::changeHero),MSG_CHANGE_HERO, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroLayer::changeState),MSG_CHANGE_STATE, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HeroLayer::updateHero),MSG_HERO_UPDATE, NULL);

    int language=CCApplication::sharedApplication()->getCurrentLanguage();
    UITextButton* textButton = UITextButton::create();
    textButton->setTouchEnable(true);
    textButton->loadTextures("changhero1.png", "changhero2.png", "");
    textButton->setFontSize(24);
    textButton->setPosition(ccp(winSize.width/2-150,200));
    textButton->addReleaseEvent(this, coco_releaseselector(HeroLayer::Shengji));
    textButton->setTag(11);
    ul->addWidget(textButton);
    
    UITextButton* textButton1 = UITextButton::create();
    textButton1->setTouchEnable(true);
    textButton1->loadTextures("heroup1.png", "heroup2.png", "");
    textButton1->setFontSize(24);
    textButton1->setPosition(ccp(winSize.width/2,200));
    textButton1->addReleaseEvent(this, coco_releaseselector(HeroLayer::Shengji));
    textButton1->setTag(12);
    ul->addWidget(textButton1);
    
    UITextButton* textButton2 = UITextButton::create();
    textButton2->setTouchEnable(true);
    textButton2->loadTextures("qianghua1.png", "qianghua2.png", "");
    textButton2->setFontSize(24);
    textButton2->setPosition(ccp(winSize.width/2+150,200));
    textButton2->addReleaseEvent(this, coco_releaseselector(HeroLayer::Shengji));
    textButton2->setTag(13);
    ul->addWidget(textButton2);

    getHeros();
    return true;
}
void HeroLayer::getHeroInfo(CCObject *sender)
{
    HeroInfoLayer *info=new HeroInfoLayer();
    int page=pageView->getPage();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=-1;
    HeroType hero;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
            j++;
            if(page==j)
                hero=Heros[i];
        }
    }
    info->init(hero);
    addChild(info);
}
void HeroLayer::menuCallback(CCObject *sender)
{
    UIButton * btn=(UIButton*)sender;
    int tag=btn->getTag();
    int page=pageView->getPage();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=-1;
    HeroType hero;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
            j++;
            if(page==j)
                hero=Heros[i];
        }
    }
    ZhuangBeiType zhuang=hero.zhuang[tag];
    ZhuangBeiListLayer *zhuangbei=new ZhuangBeiListLayer();
    zhuangbei->init(hero,tag,zhuang);
    addChild(zhuangbei,10);
}
void HeroLayer::changeState(CCObject *object)
{
    updateHero();
}
void HeroLayer::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_CHANGE_STATE);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_CHANGE_HERO);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_HERO_UPDATE);
}
void HeroLayer::getHeros()
{
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int index=0;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
        index++;
        string name =Heros[i].name;
        char strap[64];
        sprintf(strap,"%d",Heros[i].totalap);
        char strhp[64];
        sprintf(strhp,"%d",Heros[i].totalhp);

        UILayout* layout = UILayout::create();
        layout->setSize(CCSizeMake(winSize.width, winSize.height));
        layout->setTag(100+index);
        UIWidget*example_root = GUIReader::shareReader()->widgetFromJsonFile("HeroLayer_1.json");
        layout->addChild(example_root);
        pageView->addPage(layout);
        

        UILabel *nameLabel=dynamic_cast<UILabel *>(layout->getChildByTag(11));
        nameLabel->setFontSize(48);
        char strname[64];
        sprintf(strname,"%s %d级",name.c_str(),Heros[i].level);
        nameLabel->setText(strname);
            
        UILabel *hpLabel=dynamic_cast<UILabel *>(layout->getChildByTag(9));
        hpLabel->setText(strhp);
        
        UILabel *apLabel=dynamic_cast<UILabel *>(layout->getChildByTag(10));
        apLabel->setText(strap);
        

        
        string textureName=Heros[i].textureName;
        UIImageView * image= dynamic_cast<UIImageView *>(layout->getChildByTag(2));
        image->addReleaseEvent(this, coco_releaseselector(HeroLayer::getHeroInfo));
        image->setTexture(textureName.c_str());
        image->setScale(1.5);
        
        for(int j=0;j<6;j++)
        {

            string swordname=Heros[i].zhuang[j].textureName;
            UIButton * btn=dynamic_cast<UIButton *>(layout->getChildByTag(j+3));
            btn->setTag(j);
            btn->addReleaseEvent(this, coco_releaseselector(HeroLayer::menuCallback));
            
            UIImageView * image1=UIImageView::create();
            image1->setTexture(swordname.c_str());
            image1->setPosition(ccp(btn->getPosition().x+10,btn->getPosition().y));
            image1->setTag(20+j);
            layout->addChild(image1);
        }
      }
    }
}
void HeroLayer::changeHero(CCObject* object)
{
    updateHero();
}
void HeroLayer::Jinjie()
{
    
}
void HeroLayer::pageLeft()
{
    int index=pageView->getPage();
    index--;
    if(index<=0)
        index=0;
    pageView->scrollToPage(index);
}
void HeroLayer::pageRight()
{
    int index=pageView->getPage();
    index++;
    vector<HeroType>  heros=GameData::shareGameData()->getHeros();
    if(index>=heros.size())
        index=heros.size();
    pageView->scrollToPage(index);
}
void HeroLayer::Shengji(CCObject *sender)
{
    UIButton * btn=(UIButton*)sender;
    int tag=btn->getTag();
    int page=pageView->getPage();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=-1;
    HeroType hero;
    for (int i=0; i<Heros.size(); ++i)
    {
        if(Heros[i].pos>0)
        {
            j++;
            if(page==j)
                hero=Heros[i];
        }
    }
    if(tag==13)
    {
    QiangHuaLayer *layer=new QiangHuaLayer();
    layer->init(hero);
    layer->autorelease();
    addChild(layer,10);
    }
    if(tag==12)
    {
        ShengJiLayer *layer=new ShengJiLayer();
        layer->init(hero);
        layer->autorelease();
        addChild(layer,10);
    }
    if(tag==11)
    {
        
        HeroListLayer *layer=new HeroListLayer();
        layer->init(hero,1);
        layer->autorelease();
        addChild(layer);
    }
}
void HeroLayer::updateHero()
{
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    int j=0;
    for (int i=0; i<Heros.size(); ++i)
    {
        
        if(Heros[i].pos>0)
        {
        j++;
        UILayout* layout=(UILayout*)pageView->getChildByTag(100+j);
        string name =Heros[i].name;
  
        string textureName=Heros[i].textureName;
        UIImageView * image= dynamic_cast<UIImageView *>(layout->getChildByTag(2));
        image->setTexture(textureName.c_str());
            
            UILabel *nameLabel=dynamic_cast<UILabel *>(layout->getChildByTag(11));
            nameLabel->setFontSize(48);
            char strname[64];
            sprintf(strname,"%s %d级",name.c_str(),Heros[i].level);
            nameLabel->setText(strname);
            
            char strap[64];
            sprintf(strap,"%d",Heros[i].totalap);
            char strhp[64];
            sprintf(strhp,"%d",Heros[i].totalhp);

            UILabel *hpLabel=dynamic_cast<UILabel *>(layout->getChildByTag(9));
            hpLabel->setText(strhp);
            
            UILabel *apLabel=dynamic_cast<UILabel *>(layout->getChildByTag(10));
            apLabel->setText(strap);
        for(int a=0;a<6;a++)
        {
        string swordname=Heros[i].zhuang[a].textureName;
        UIImageView * images= dynamic_cast<UIImageView *>(layout->getChildByTag(a+20));
        images->setTexture(swordname.c_str());
        }
        }
    }
}