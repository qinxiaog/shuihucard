//
//  FightLayer.cpp
//  kapai
//
//  Created by qin on 14-4-6.
//
//

#include "FightLayer.h"
#include "BattleScene.h"
FightLayer::FightLayer(int level)
{
	init(level);
}
FightLayer::~FightLayer()
{
	
}
bool FightLayer::init(int level)
{
    if(!CCLayer::init()){
        return false;
    }
    mlevel=level;
    setTouchEnabled(true);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* imagehead= CCSprite::create("zhanyi.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(imagehead);
    
    readJson();
    
    CCSize visibSize=CCDirector::sharedDirector()->getVisibleSize();
    CCTableView *tableView=CCTableView::create(this, CCSizeMake(visibSize.width,600));
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setPosition(ccp(0,winSize.height/2-360));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(tableView,1);
    //tableView->reloadData();
    

    
    CCMenuItemImage* pHome = CCMenuItemImage::create("close1.png", "close2.png", this, menu_selector(FightLayer::close));
    CCMenu *menu=CCMenu::create(pHome,NULL);
    menu->setPosition(ccp(winSize.width-60,winSize.height/2+300));
    addChild(menu,2);
//    CCScale9Sprite *sprite9 = CCScale9Sprite::create("close1.png");
//    CCControlButton* btn= CCControlButton::create(sprite9);
//    btn->addTargetWithActionForControlEvents(this, cccontrol_selector(FightLayer::close),CCControlEventTouchDown);
//    btn->setPreferredSize(CCSizeMake(sprite9->getContentSize().width,sprite9->getContentSize().height));
//    btn->setPosition(ccp(winSize.width-60, winSize.height/2+350));
//    addChild(btn);
    return true;
}
void FightLayer::readJson()
{
    CSJson::Reader reader;
    CSJson::Value root;
    unsigned  long nSize = 0;
    char str[32];
    sprintf(str,"map_%d.json",mlevel);
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    string path =CCFileUtils::sharedFileUtils()->fullPathForFilename(str);
    map_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    if(reader.parse(map_document, root))
    {
        datas=root["data"];
    }
}
unsigned int FightLayer::numberOfCellsInTableView(CCTableView *table)
{
    
    return datas.size();

}

CCTableViewCell* FightLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCTableViewCell *cell = table->dequeueCell();
    string tile=datas[idx]["name"].asString();
    int card=datas[idx]["card"].asInt();
    int sword=datas[idx]["sword"].asInt();
    int xp=datas[idx]["xp"].asInt();
    int money=datas[idx]["coin"].asInt();
    if (!cell)
    {
        
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *bgSprite = CCSprite::create("cellbg.png");
        bgSprite->setAnchorPoint(CCPointZero);
        bgSprite->setPosition(CCPointZero);
        bgSprite->setTag(789);
        cell->addChild(bgSprite);
        

        CCLabelTTF *pLabel = CCLabelTTF::create(tile.c_str(), "Arial", 32.0);
        pLabel->setColor(ccRED);
        pLabel->setPosition(ccp(winSize.width/2,120));
        pLabel->setTag(400);
        cell->addChild(pLabel);

        char str[32];
        sprintf(str,"经验:%d\n银子:%d",xp,money);
        CCLabelTTF *coinLabel=CCLabelTTF::create(str, "Arial", 24.0);
        coinLabel->setTag(401);
        coinLabel->setColor(ccBLACK);
        coinLabel->setPosition(ccp(120,100));
        cell->addChild(coinLabel);
        
        CCLabelTTF *cardLabel=CCLabelTTF::create("","Arial", 32.0);
        cardLabel->setTag(402);
        cardLabel->setColor(ccBLUE);
        cardLabel->setPosition(ccp(winSize.width/2,60));
        cell->addChild(cardLabel);
    }
    else
    {
        
        CCLabelTTF *pLabel = (CCLabelTTF*)cell->getChildByTag(400);
        pLabel->setString(tile.c_str());
        
        char str[32];
        sprintf(str,"经验:%d\n银子:%d",xp,money);
        CCLabelTTF *pcoinLabel = (CCLabelTTF*)cell->getChildByTag(401);
        pcoinLabel->setString(str);
        
        CCLabelTTF *pcardLabel = (CCLabelTTF*)cell->getChildByTag(402);
        
        map<int,HeroType> HeroTypes=Config::sharedConfig()->getHerosType();
        HeroType herodata;
        herodata.type=card;
        map<int,HeroType>::iterator iterHero = HeroTypes.find(card);
        if(iterHero!= HeroTypes.end())
        {
            HeroType herotype=iterHero->second;
            herodata.name=herotype.name;
            
            char strname[32];
            sprintf(strname,"随机掉落:%s",herotype.name.c_str());
            pcardLabel->setString(strname);
        }
        if(card==108)
        {
            pcardLabel->setString("随机掉落108将之一");
        }
        else if(card==109)
        {
            pcardLabel->setString("随机掉落72地煞星之一");
        }
        
        map<int,ZhuangBeiType> zhuangTypes=Config::sharedConfig()->getZhuangBei();
        ZhuangBeiType data;
        int index=sword/1000;
        map<int,ZhuangBeiType>::iterator iter=zhuangTypes.find(index);
        if(iter!= zhuangTypes.end())
        {
            ZhuangBeiType type=iter->second;
            char strname[32];
            sprintf(strname,"随机掉落:%s",type.name.c_str());
            CCLabelTTF *pcard = (CCLabelTTF*)cell->getChildByTag(402);
            pcard->setString(strname);
        }
        if(card==-1&&sword==-1)
        {
            CCLabelTTF *pcard = (CCLabelTTF*)cell->getChildByTag(402);
            pcard->setString("");
        }
    }
    return cell;
}
CCSize FightLayer::cellSizeForTable(CCTableView *table)
{
    CCSize visibSize=CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(visibSize.width, 193);
}

void FightLayer::tableCellHighlight(CCTableView *table, CCTableViewCell *cell)
{

}

void FightLayer::tableCellUnhighlight(CCTableView *table, CCTableViewCell *cell)
{
    
}
void FightLayer::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
    
}
void FightLayer::scrollViewDidZoom(cocos2d::extension::CCScrollView* view)
{
    
}
void FightLayer::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{    
    int tag=cell->getIdx();
    Value data=datas[tag];
    //CCScene *pScene =BattleScene::scene(data);
    CCScene *pScene =CCDirector::sharedDirector()->getRunningScene();

    BattleScene *layer=new BattleScene();
    layer->init(data);
    layer->autorelease();
    pScene->addChild(layer,10);
    

    CCMenu *menu =(CCMenu*)layer->getParent()->getChildByTag(888);
    menu->setVisible(false);
}
void FightLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
void FightLayer::registerWithTouchDispatcher(void)
{
   CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
    
}
bool FightLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void FightLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void FightLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void FightLayer::close(CCObject *sender)
{
    removeAllChildrenWithCleanup(true);
    removeFromParentAndCleanup(true);
}
void FightLayer::menuPauseCallback(CCObject *sender)
{
    CCMenuItemImage* pHome =(CCMenuItemImage*) sender;
    int tag=pHome->getTag();
    Value data=datas[tag];
 

    BattleScene *layer=new BattleScene();
    layer->init(data);
    layer->autorelease();
    addChild(layer,10);
}