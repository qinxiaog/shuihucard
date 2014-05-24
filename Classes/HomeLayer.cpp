#include "HomeLayer.h"
#include "HeroListLayer.h"
#include "SceneGame.h"
#include "ZhuangBeiLayer.h"
#include "TipWindows.h"
#include "JiangLiLayer.h"
using namespace std;
const float PAUSE_MENU_POS_X = 460;
const float PAUSE_MENU_POS_Y = 300;

const float JOYSTICK_POS_X = 50;
const float JOYSTICK_POS_Y = 50;
const float JOYSTICK_DEAD_RADIUS = 10;
const float JOYSTICK_THRESHOLD = 0.4f;

const float BTN_A_POS_X = 430;
const float BTN_A_POS_Y = 50;

HomeLayer::HomeLayer()
{
    isBeingUsed=false;
	init();
}

bool HomeLayer::init()
{
    if(!CCLayer::init())
        return false;
  this->setKeypadEnabled(true);
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    setTouchEnabled(true);
    UILayer * ul=UILayer::create();
    //ul->setPosition(ccp(0,winSize.height/2));
    this->addChild(ul);

    UIImageView *image=UIImageView::create();
    image->setTexture("level.png");
    image->setPosition(ccp(winSize.width/2, winSize.height/2+240));
    
    ul->addWidget(image);
    mlevel=GameData::shareGameData()->mlevel;
    mxp=GameData::shareGameData()->mxp;
    char str[32];
    sprintf(str,"%d",mlevel);
    levellabel=UILabel::create();
    levellabel->setFontSize(48);
    levellabel->setText(str);
    levellabel->setPosition(ccp(image->getPosition().x+20,image->getPosition().y-10));
    ul->addWidget(levellabel);

    int totalxp=getexp(1.1,mlevel);
    UIImageView *timebg=UIImageView::create();
    timebg->setTexture("xp2.png");
    timebg->setPosition(ccp(winSize.width/2,image->getPosition().y-image->getContentSize().height/2-20));
    ul->addWidget(timebg);

    CCSprite*sp=CCSprite::create("xp1.png");
    healthBar=CCProgressTimer::create(sp);
    ul->addChild(healthBar);
    healthBar->setPosition(ccp(winSize.width/2,image->getPosition().y-image->getContentSize().height/2-20));
    healthBar->setType(kCCProgressTimerTypeBar);
    healthBar->setMidpoint(ccp(0,0.5));
    healthBar->setBarChangeRate(ccp(1,0));
    healthBar->setPercentage(((float)mxp/(float)totalxp) *100);
 
    
    CCString *exp=CCString::createWithFormat("%d/%d",mxp,totalxp);
    xpLabel=CCLabelTTF::create(exp->getCString(),"Arial", 32);
    xpLabel->setColor(ccBLUE);
    xpLabel->setPosition(healthBar->getPosition());
    ul->addChild(xpLabel);
    
    UIImageView *moneyBg=UIImageView::create();
    moneyBg->setTexture("coin1.png");
    moneyBg->setPosition(ccp(winSize.width/2-60,winSize.height/2-moneyBg->getPosition().y+100));
    
    ul->addWidget(moneyBg);
    
    UIImageView *coinBg=UIImageView::create();
    coinBg->setTexture("money1.png");
    coinBg->setPosition(ccp(winSize.width/2-60,winSize.height/2-coinBg->getPosition().y));
    
    ul->addWidget(coinBg);
    
    int money=GameData::shareGameData()->mMoney;
    CCString *strMoney=CCString::createWithFormat("%d",money);
    moneyLabel=CCLabelTTF::create();
    moneyLabel->setFontSize(32);
    moneyLabel->setPosition(ccp(120+moneyBg->getPosition().x,moneyBg->getPosition().y));
    moneyLabel->setString(strMoney->getCString());
    addChild(moneyLabel);
    
    int coin=GameData::shareGameData()->mCoin;
    CCString *strCoin=CCString::createWithFormat("%d",coin);
    coinLabel=CCLabelTTF::create();
    coinLabel->setFontSize(32);
    coinLabel->setPosition(ccp(coinBg->getPosition().x+120,coinBg->getPosition().y));
    coinLabel->setString(strCoin->getCString());
    addChild(coinLabel);

    int language=CCApplication::sharedApplication()->getCurrentLanguage();
        UIButton* textButton = UIButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("zhuangbei1.png", "zhuangbei2.png", "zhuangbei2.png");
        textButton->setPosition(ccp(textButton->getContentSize().width/2,winSize.height/2+100));
        textButton->addReleaseEvent(this, coco_releaseselector(HomeLayer::menuCallback));
        textButton->setTag(11);
        ul->addWidget(textButton);
    CCLOG("texbutton");
    UIButton* textButton1 = UIButton::create();
    textButton1->setTouchEnable(true);
    textButton1->loadTextures("yinxiong1.png", "yinxiong2.png", "");
    textButton1->setPosition(ccp(textButton1->getContentSize().width/2,winSize.height/2));
    textButton1->addReleaseEvent(this, coco_releaseselector(HomeLayer::menuCallback));
    textButton1->setTag(12);
    ul->addWidget(textButton1);
    
    UIButton* textButton2 = UIButton::create();
    textButton2->setTouchEnable(true);
    textButton2->loadTextures("login1.png", "login2.png", "");
    textButton2->setPosition(ccp(winSize.width-textButton2->getContentSize().width/2,winSize.height/2+100));
    textButton2->addReleaseEvent(this, coco_releaseselector(HomeLayer::menuCallback));
    textButton2->setTag(13);
    ul->addWidget(textButton2);
    
    UIButton* textButton3 = UIButton::create();
    textButton3->setTouchEnable(true);
    textButton3->loadTextures("levelup1.png", "levelup2.png", "");
    textButton3->setPosition(ccp(winSize.width-textButton3->getContentSize().width/2,winSize.height/2));
    textButton3->addReleaseEvent(this, coco_releaseselector(HomeLayer::menuCallback));
    textButton3->setTag(14);
    ul->addWidget(textButton3);


    CCUserDefault *TextFieldV =CCUserDefault::sharedUserDefault();
    coinNum=TextFieldV->getIntegerForKey("coin",20000);
    diamondsNum=TextFieldV->getIntegerForKey("money",200);
    CCUserDefault::sharedUserDefault()->flush();

    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HomeLayer::healthBarLogic),MSG_LEVEL_UPDATE, NULL);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("menubg.mp3",false);

    healthBarLogic(NULL);
    
	return true;
}
void HomeLayer::healthBarLogic(CCObject *sender)
{
    int level=GameData::shareGameData()->mlevel;
    int xp=GameData::shareGameData()->mxp;
    int totalxp=getexp(1.1,level);
    if(xp>=totalxp)
    {
        mxp-=totalxp;
        xp-=totalxp;
        level++;
        mlevel++;
    }

    CCString *lelstr=CCString::createWithFormat("%d",level);
    levellabel->setText(lelstr->getCString());
    healthBar->setPercentage(((float)xp/(float)totalxp) *100);

    
    CCString *exp=CCString::createWithFormat("%d/%d",xp,totalxp);
    xpLabel->setString(exp->getCString());
    //unschedule(schedule_selector(HomeLayer::healthBarLogic));
    int money=GameData::shareGameData()->mMoney;
    CCString *strMoney=CCString::createWithFormat("%d",money);
    moneyLabel->setString(strMoney->getCString());
    
    int coin=GameData::shareGameData()->mCoin;
    CCString *strCoin=CCString::createWithFormat("%d",coin);
    coinLabel->setString(strCoin->getCString());

}
int HomeLayer::getexp(float x, int n)
{
    if(n == 0)
    {
        return LEVELXP;
    }
    
    return x * getexp(x, n-1);
}
void HomeLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->end();
}
void HomeLayer::menuCallback(CCObject *sender)
{
    UIButton *btn=(UIButton*)sender;
    int tag=btn->getTag();
    HeroType hero;
    if(tag==11)
    {
        
        ZhuangBeiType zhuang;
        ZhuangBeiListLayer *zhuangbei=new ZhuangBeiListLayer();
        zhuangbei->autorelease();
        zhuangbei->init(hero,-1,zhuang);
        addChild(zhuangbei,10);
    }
    if(tag==12)
    {
        HeroListLayer *list=new HeroListLayer();
        list->init(hero,-1);
        list->autorelease();
        addChild(list,10);
    }
    if(tag==13)
    {
        OnGetMoney();
    }
    else if(tag==14)
    {
        JiangLiLayer *layer=new JiangLiLayer();
        layer->autorelease();
        addChild(layer,10);
    }
}
void HomeLayer::onExit()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_LEVEL_UPDATE);
}
void HomeLayer::OnGetMoney()
{
    struct tm *tm,tm1,tm2;
    int oldyear=CCUserDefault::sharedUserDefault()->getIntegerForKey("year");
    int oldmonth=CCUserDefault::sharedUserDefault()->getIntegerForKey("month");
    int oldday=CCUserDefault::sharedUserDefault()->getIntegerForKey("day");
    int oldwday=CCUserDefault::sharedUserDefault()->getIntegerForKey("wday");
    int oldyday=CCUserDefault::sharedUserDefault()->getIntegerForKey("yday");
    int oldhour=CCUserDefault::sharedUserDefault()->getIntegerForKey("hour");
    int oldminute=CCUserDefault::sharedUserDefault()->getIntegerForKey("minute");
    
    
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    
    tm = localtime(&now.tv_sec);
    //time_t t = time(NULL);
    int year = tm->tm_year;
    int month = tm->tm_mon;
    int day = tm->tm_mday;
    int wday = tm->tm_wday;
    int yday = tm->tm_yday;
    int hour=tm->tm_hour;
    int minute=tm->tm_min;
    time_t tt1,tt2;
    tm1.tm_year=oldyear;
    tm1.tm_mon=oldmonth;
    tm1.tm_wday=oldwday;
    tm1.tm_mday=oldday;
    tm1.tm_yday=oldyday;
    tm1.tm_hour=oldhour;
    tm1.tm_min=oldminute;
    tm1.tm_sec=0;
    tm1.tm_isdst=0;
    
    tm2.tm_year=year;
    tm2.tm_mon=month;
    tm2.tm_mday=day;
    tm2.tm_wday=wday;
    tm2.tm_yday=yday;
    tm2.tm_hour=hour;
    tm2.tm_min=minute;
    tm2.tm_sec=0;
    tm2.tm_isdst=0;
    tt1=mktime(&tm1);
    tt2=mktime(&tm2);
    float dt=(float)(difftime(tt2,tt1))/60;
    int money=dt*20;
    int coin=dt/5;
    if(money<0||coin<0)
    {
        money=0;
        coin=0;
    }
    if(money>20000||coin>200)
    {
        money=20000;
        coin=200;
    }
    int totalMoney=GameData::shareGameData()->mMoney;
    int totalCoin=GameData::shareGameData()->mCoin;
    totalMoney+=money;
    totalCoin+=coin;

    
    char strmoney[32];
    sprintf(strmoney,"%d",totalMoney);
    moneyLabel->setString(strmoney);

    sprintf(strmoney,"%d",totalCoin);
    coinLabel->setString(strmoney);
    GameData::shareGameData()->setMoney(totalMoney);
    GameData::shareGameData()->setCoin(totalCoin);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("year",year);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("month",month);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("day",day);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("wday",wday);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("yday",yday);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("hour",hour);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("minute",minute);
    CCUserDefault::sharedUserDefault()->flush();
    char str[64];
    sprintf(str,"银子:%d\n元宝:%d",money,coin);
    TipWindows *win=new TipWindows(string(str));
    addChild(win,10);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_LEVEL_UPDATE);
    //MakeRecord();
}
void HomeLayer::menuPauseCallback(CCObject *sender)
{
}
void HomeLayer::updateCoin()
{

}
HomeLayer::~HomeLayer()
{

}

void HomeLayer::onEnter()
{
    CCLayer::onEnter();
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);
}
void HomeLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127+1, false);
    CCLayer::registerWithTouchDispatcher();
}
bool HomeLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
//     if(isBeingUsed) return false;
//    CCSprite *item=(CCSprite*)getChildByTag(0);
//    CCSprite *item1=(CCSprite*)getChildByTag(1);
//    pLayer->btouch=true;
//    isBeingUsed=true;
//    CCPoint pt=pTouch->getLocationInView();
//    pt = CCDirector::sharedDirector()->convertToGL(pt);
//    if(item->boundingBox().containsPoint(pt))
//    {
//        pLayer->direction(kDirLeft);
//    }
//    else if(item1->boundingBox().containsPoint(pt))
//    {
//        pLayer->direction(kDirRight);
//    }
    
	return true;
}

void HomeLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}
void HomeLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    isBeingUsed=false;
}
void HomeLayer::update(float delta)
{

}