#include "SceneGame.h"
#include "shop.h"
const int GAME_LAYER_Z_INDEX = 10;
const int HUD_LAYER_Z_INDEX = 20;

SceneGame::SceneGame(int level)
{

  
//	mGameLayer = new mainScene();
//    mGameLayer->init();
//	mGameLayer->setPosition(ccp(0, 0));
//    mGameLayer->autorelease();
//	this->addChild(mGameLayer, GAME_LAYER_Z_INDEX);
    init(level);
    mHudLayer = new HomeLayer();
	mHudLayer->setPosition(ccp(0, 0));
    mHudLayer->autorelease();
	this->addChild(mHudLayer,1,HOMEGAG);
	//this->schedule(schedule_selector(SceneGame::broadcastInput));

	
}

bool SceneGame::init(int level)
{
    
    CCSize size= CCDirector::sharedDirector()->getWinSize();
    CCSprite *bg=CCSprite::create("homebg.png");
    bg->setPosition(ccp(size.width/2,size.height/2));
    bg->setScaleX(size.width/640);
    bg->setScaleY(size.height/960);
    addChild(bg);
    
    CCSprite *tile=CCSprite::create("tile.png");
    tile->setPosition(ccp(size.width/2,size.height-80-tile->getContentSize().height/2));
    addChild(tile);
    CCMenuItemImage *item =CCMenuItemImage::create("home1.png","home2.png",this, menu_selector(SceneGame::menuPauseCallback));
        CCMenuItemImage *item1 =CCMenuItemImage::create("group1.png","group2.png",this, menu_selector(SceneGame::menuPauseCallback));
        CCMenuItemImage *item2 =CCMenuItemImage::create("hero1.png","hero2.png",this, menu_selector(SceneGame::menuPauseCallback));
        CCMenuItemImage *item3 =CCMenuItemImage::create("war1.png","war2.png",this, menu_selector(SceneGame::menuPauseCallback));
        CCMenuItemImage *item4 =CCMenuItemImage::create("tujian1.png","tujian2.png",this, menu_selector(SceneGame::menuPauseCallback));
        CCMenuItemImage *item5 =CCMenuItemImage::create("store1.png","store2.png",this, menu_selector(SceneGame::menuPauseCallback));
    item->setTag(0);
    item1->setTag(1);
    item2->setTag(2);
    item3->setTag(3);
    item4->setTag(4);
    item5->setTag(5);
    CCMenu *menu =CCMenu::create(item,item1,item2,item3,item4,item5,NULL);
    menu->alignItemsHorizontally();
    menu->setPosition(ccp(size.width/2,item->getContentSize().height/2));
    menu->setTag(888);
    this->addChild(menu,1000);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneGame::setMenuVisible),MENUVISIBLE, NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneGame::getCoin), "buy", NULL);
	return true;
}
void SceneGame::getCoin(CCObject *sender)
{
    int totalMoney=CCUserDefault::sharedUserDefault()->getIntegerForKey("coin",200);
    GameData::shareGameData()->setCoin(totalMoney);
}
void SceneGame::setMenuVisible(CCObject *sender)
{
    CCMenu *item =(CCMenu*)getChildByTag(888);
    item->setVisible(true);
}
SceneGame::~SceneGame()
{
}
void SceneGame::menuPauseCallback(CCObject *sender)
{
    CCMenuItemImage *item=(CCMenuItemImage*)sender;
    int tag=item->getTag();
    removeChildByTag(HOMEGAG);
    removeChildByTag(HEROGAG);
    removeChildByTag(WARGAG);
    removeChildByTag(FIGHTGAG);
    removeChildByTag(HONGDONGGAG);
    removeChildByTag(STOREGAG);
    
    if(tag==0)
    {

    mHudLayer = new HomeLayer();
	mHudLayer->setPosition(ccp(0, 0));
    mHudLayer->autorelease();
	this->addChild(mHudLayer,1,HOMEGAG);
    }
    if(tag==1)
    {

        mGroupLayer = new GroupLayer();
        mGroupLayer->setPosition(ccp(0, 0));
        mGroupLayer->autorelease();
        this->addChild(mGroupLayer,1,HEROGAG);
    }
    if(tag==2)
    {

        mHeroLayer = new HeroLayer();
        mHeroLayer->setPosition(ccp(0, 0));
        mHeroLayer->autorelease();
        this->addChild(mHeroLayer,1,WARGAG);
    }
    if(tag==3)
    {
        mMap = new GameMapLayer();
        mMap->setPosition(ccp(0, 0));
        mMap->autorelease();
        this->addChild(mMap,1,FIGHTGAG);
    }
    if(tag==4)
    {
        mTujian= new TuJianLayer();
        mTujian->setPosition(ccp(0, 0));
        mTujian->autorelease();
        this->addChild(mTujian,1,HONGDONGGAG);
    }
    if(tag==5)
    {
        mStoreLayer = new shopLayer();
        mStoreLayer->setPosition(ccp(0, 0));
        mStoreLayer->autorelease();
        this->addChild(mStoreLayer,1,STOREGAG);
    }
}
void SceneGame::broadcastInput(float dt)
{

}