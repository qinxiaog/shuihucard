//
//  shop.cpp
//  Created by lh on 13-10-25.
//
//

#include "shop.h"
#include "StoreLayer.h"
shopLayer::shopLayer()
{
	init();
}
shopLayer::~shopLayer()
{
	
}
bool shopLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    CCSprite* imagehead= CCSprite::create("storebg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(imagehead);
    
    CCSprite* imagebg= CCSprite::create("coinsbg.png");
    imagebg->setPosition(ccp(winSize.width/2-50,winSize.height/2+250));
    addChild(imagebg);
    
//    UIImageView* imagehp= UIImageView::create();
//    imagehp->setTexture("yuanbao.png");
//    imagehp->setPosition(ccp(winSize.width/2-50,winSize.height-200));
//    m_pUiLayer->addWidget(imagehp);
    
    int totalmoney=CCUserDefault::sharedUserDefault()->getIntegerForKey("coin",200);
    CCUserDefault::sharedUserDefault()->flush();
    char strdia[32];
    sprintf(strdia,"%d",totalmoney);
    moneylabel=CCLabelTTF::create(strdia,"",48);
    moneylabel->setPosition(ccp(winSize.width/2-30,winSize.height/2+250));
    addChild(moneylabel);
    
//    CCMenuItemImage* pHome = CCMenuItemImage::create("chongzhi1.png", "chongzhi2.png", this, menu_selector(shopLayer::Store));
//    CCMenu *menu=CCMenu::create(pHome,NULL);
//    menu->setPosition(ccp(winSize.width-150,winSize.height/2+250));
//    menu->setTag(10);
//    addChild(menu);
    
    
    string str[2]={"36天罡星","72地煞星"};
    string strMoney[2]={"200","80"};
    for(int i=0;i<2;i++)
    {
        CCSprite* imageView = CCSprite::create("cellbg.png");
        imageView->setPosition(ccp(winSize.width/2,winSize.height/2+190*i-190/2));
        addChild(imageView);
        
        CCSprite* imagehp= CCSprite::create("yuanbao.png");
        imagehp->setPosition(ccp(winSize.width/2-50,winSize.height/2+190*i-190/2));
        addChild(imagehp);
        
        CCLabelTTF *label=CCLabelTTF::create(str[i].c_str(),"Arial",32);
        label->setColor(ccRED);
        label->setPosition(ccp(150,winSize.height/2+190*i-190/2));
        addChild(label);
    
        
        CCLabelTTF *hplabel=CCLabelTTF::create(strMoney[i].c_str(),"Arial",32);
        hplabel->setColor(ccRED);
        hplabel->setPosition(ccp(winSize.width/2+50,winSize.height/2+190*i-190/2));
        addChild(hplabel);
        
        CCMenuItemImage* pHome = CCMenuItemImage::create("zhaomu1.png", "zhaomu2.png", this, menu_selector(shopLayer::menuCallback));
        pHome->setTag(i);
        CCMenu *menu=CCMenu::create(pHome,NULL);
        menu->setPosition(ccp(winSize.width-150,winSize.height/2+190*i-190/2));
        addChild(menu,2);
    }
    CCSprite* imageView = CCSprite::create("cellbg.png");
    imageView->setPosition(ccp(winSize.width/2,winSize.height/2-190-190/2));
    addChild(imageView);
    
    CCSprite* imagehp= CCSprite::create("yuanbao.png");
    imagehp->setPosition(ccp(winSize.width/2-50,winSize.height/2-190-190/2));
    addChild(imagehp);
    
    CCLabelTTF *label=CCLabelTTF::create("2","Arial",32);
    label->setColor(ccRED);
    label->setPosition(ccp(winSize.width/2+50,winSize.height/2-190-190/2));
    addChild(label);
    
    CCSprite* imagecoin= CCSprite::create("ui_coin.png");
    imagecoin->setPosition(ccp(80,winSize.height/2-190-190/2));
    addChild(imagecoin);
    
    CCLabelTTF *hplabel=CCLabelTTF::create("20000","Arial",24);
    hplabel->setColor(ccRED);
    hplabel->setPosition(ccp(160,winSize.height/2-190-190/2));
    addChild(hplabel);
    
    CCMenuItemImage* buy = CCMenuItemImage::create("coin1.png", "coin2.png", this, menu_selector(shopLayer::buy));
    buy->setTag(3);
    CCMenu *menubuy=CCMenu::create(buy,NULL);
    menubuy->setPosition(ccp(winSize.width-150,winSize.height/2-190-190/2));
    addChild(menubuy,2);
    
    CCMenuItemImage* btn = CCMenuItemImage::create("close1.png", "close2.png", this, menu_selector(shopLayer::close));
    CCMenu *menuclose=CCMenu::create(btn,NULL);
    menuclose->setPosition(ccp(winSize.width-60,winSize.height/2+300));
    addChild(menuclose,2);
    return true;
}
void shopLayer::buy(CCObject *sender)
{
    int coin=GameData::shareGameData()->mCoin;
    int money=GameData::shareGameData()->mMoney;
    if(coin>=2)
    {
        coin-=2;
        money+=20000;
        GameData::shareGameData()->setCoin(coin);
        GameData::shareGameData()->setMoney(money);
    }
}
void shopLayer::menuCallback(CCObject *sender)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCMenuItemImage *btn=(CCMenuItemImage*)(sender);
    int tag=btn->getTag();
    int card=0;
    int needMoney=80;
    if(tag==0)
    {
        card=arc4random()%36;
        needMoney=200;
    }
    else
    {
        card=arc4random()%72+36;
    }
    int money=GameData::shareGameData()->mCoin;
    if(money>=needMoney)
    {
    money-=needMoney;
    GameData::shareGameData()->setCoin(money);
    char strdia[32];
    sprintf(strdia,"%d",money);
    moneylabel->setString(strdia);
    map<int,HeroType> HeroTypes=Config::sharedConfig()->getHerosType();
    map<int,HeroType>::iterator iterHero = HeroTypes.find(card);
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    HeroType herodata;
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
        herodata.des=herotype.des;
        
        herodata.type=card;
        herodata.level=1;
        herodata.xp=0;
        herodata.exlevel=0;
        herodata.pos=0;
        
        herodata.index=Heros.size();
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
    GetHeroLayer *layer=new GetHeroLayer();
    layer->init(herodata);
    this->addChild(layer,10);
    layer->autorelease();
    }
    else
    {
        CCSprite *bg=CCSprite::create("tipbg.png");
        bg->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(bg,1);
        CCActionInterval *action0=CCFadeOut::create(2);
        bg->runAction(action0);
        char str[32];
        sprintf(str,"元宝不够");
        CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
        tiplabel->setColor(ccRED);
        tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(tiplabel,100);
        CCActionInterval *action=CCFadeOut::create(2);
        tiplabel->runAction(action);
    }
    
}
void shopLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}
void shopLayer::Store(CCObject *sender)
{
    CCScene *pScese=CCDirector::sharedDirector()->getRunningScene();
    StoreLayer *mStoreLayer = new StoreLayer();
    mStoreLayer->setPosition(ccp(0, 0));
    mStoreLayer->autorelease();
    pScese->addChild(mStoreLayer,10);
  
}
