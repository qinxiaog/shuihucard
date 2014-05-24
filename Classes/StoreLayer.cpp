//
//  StoreLayer.cpp
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#include "StoreLayer.h"
#include "GameData.h"
StoreLayer::StoreLayer()
{
	init();
}
StoreLayer::~StoreLayer()
{
	
}
bool StoreLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    if(!CCLayer::init()){
        return false;
    }
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    CCSprite* imagehead= CCSprite::create("storebg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(imagehead);
    
    string str[6]={"1000","2500","7000","15000","30000","80000"};
    string strMoney[6]={"0.99","1.99","4.99","9.99","19.99","49.99"};
    for(int i=0;i<6;i++)
    {
            CCSprite* imageView = CCSprite::create("cellbg.png");           
            int imageHeight=100;
            imageView->setScaleY(0.5);
            imageView->setPosition(ccp(winSize.width/2,winSize.height/2-imageHeight*i-imageHeight/2+280));
           addChild(imageView);
        
            CCSprite* imagehp= CCSprite::create("yuanbao.png");
            imagehp->setPosition(ccp(winSize.width/2-200,winSize.height/2-imageHeight*i-imageHeight/2+280));
            addChild(imagehp);
            
            CCLabelTTF *label=CCLabelTTF::create(str[i].c_str(),"Arial",32);
            label->setColor(ccRED);
            label->setPosition(ccp(winSize.width/2-100,winSize.height/2-imageHeight*i-imageHeight/2+280));
            addChild(label);
            
            
            CCSprite* imageap= CCSprite::create("icon_coin.png");
            imageap->setPosition(ccp(winSize.width/2,winSize.height/2-imageHeight*i-imageHeight/2+280));
            addChild(imageap);
            
            CCLabelTTF *hplabel=CCLabelTTF::create(strMoney[i].c_str(),"Arial",32);
            hplabel->setColor(ccRED);
            hplabel->setPosition(ccp(winSize.width/2+50,winSize.height/2-imageHeight*i-imageHeight/2+280));
            addChild(hplabel);
        
        CCMenuItemImage* pHome = CCMenuItemImage::create("chongzhi1.png", "chongzhi2.png", this, menu_selector(StoreLayer::buyCallback));
        CCMenu *menu=CCMenu::create(pHome,NULL);
        pHome->setTag(i);
        menu->setPosition(ccp(winSize.width-120,winSize.height/2-imageHeight*i-imageHeight/2+280));
        addChild(menu,2);
        }
    CCMenuItemImage* btn = CCMenuItemImage::create("close1.png", "close2.png", this, menu_selector(StoreLayer::close));
    CCMenu *menuclose=CCMenu::create(btn,NULL);
    menuclose->setPosition(ccp(winSize.width-60,winSize.height/2+300));
    addChild(menuclose,2);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(StoreLayer::onBuy), "buy", NULL);
    return true;
}
void StoreLayer::onBuy(int type)
{
    int totalMoney=CCUserDefault::sharedUserDefault()->getIntegerForKey("coin",200);
    GameData::shareGameData()->setCoin(totalMoney);
}
void StoreLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,"buy");
}
void StoreLayer::buyCallback(CCObject *sender)
{
        CCMenuItemImage *item=(CCMenuItemImage*)sender;
        int tag=item->getTag();
        printf("button===%d",tag);
    if(tag>0&&tag<6)
    {

    }
}
void StoreLayer::close(CCObject *sender)
{
    removeAllChildrenWithCleanup(true);
    removeFromParentAndCleanup(true);
}
void StoreLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127,true);
    
}
bool StoreLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void StoreLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void StoreLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}