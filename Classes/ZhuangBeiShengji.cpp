//
//  ZhuangBeiShengji.cpp
//  kapai
//
//  Created by qin on 14-1-9.
//
//

#include "ZhuangBeiShengji.h"
#include "ZhuangBeiLayer.h"
#include "HeroInfoLayer.h"
#include "Config.h"
#include "HeroLayer.h"
#define MONEYXP   200
ZhuangBeiShengjiLayer::ZhuangBeiShengjiLayer()
{
	
}
ZhuangBeiShengjiLayer::~ZhuangBeiShengjiLayer()
{
	
}
bool ZhuangBeiShengjiLayer::init(ZhuangBeiType type)
{
    if(!CCLayer::init()){
        return false;
    }
    m_type=type;
    setTouchEnabled(true);
    m_pUiLayer=UILayer::create();
    //ul->setPosition(ccp(0,winSize.height/2));
    this->addChild(m_pUiLayer);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIImageView* imageView = UIImageView::create();
    imageView->setTexture("herolistbg.png");
    imageView->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imageView);
    
    UIImageView* coinImage = UIImageView::create();
    coinImage->setTexture("coins.png");
    coinImage->setPosition(ccp(120,winSize.height/2));
    m_pUiLayer->addWidget(coinImage);
    
    coinlabel = UILabel::create();
    coinlabel->setPosition(ccp(120,winSize.height/2-coinImage->getContentSize().height));
    coinlabel->setFontSize(32);
    coinlabel->setColor(ccYELLOW);
    char str[64];
    sprintf(str,"银两:%d",150+15*m_type.level);
    coinlabel->setText(str);
    m_pUiLayer->addWidget(coinlabel);
    
    UIImageView* imagebg = UIImageView::create();
    imagebg->setTexture("addbutton.png");
    imagebg->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imagebg);
    
//    UIWidget*example_root = GUIReader::shareReader()->widgetFromJsonFile("ShenjiLayer_1.json");
//    example_root->setTouchEnabled(true);
//    m_pUiLayer->addWidget(example_root);
    

    
    //UIImageView* imageCard = (UIImageView*)m_pUiLayer->getWidgetByTag(2);
    UIImageView* imageCard=UIImageView::create();
    imageCard->setTexture(m_type.textureName.c_str());
    imageCard->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imageCard);
    
    //UIButton *btn=(UIButton*)m_pUiLayer->getWidgetByTag(6);
    UIButton *btn=UIButton::create();
    btn->setTouchEnabled(true);
    btn->setPosition(ccp(winSize.width/2, winSize.height/2-300));
    btn->setTextures("heroup1.png", "heroup2.png", "heroup2.png");
    btn->addReleaseEvent(this, coco_releaseselector(ZhuangBeiShengjiLayer::menuPauseCallback));
    m_pUiLayer->addWidget(btn);
    
    UIButton *btnclose=UIButton::create();
    btnclose->setTouchEnabled(true);
    btnclose->setTextures("close1.png","close2.png","close2.png");
    btnclose->setPosition(ccp(winSize.width-60, winSize.height/2+300));
    btnclose->addReleaseEvent(this, coco_releaseselector(ZhuangBeiShengjiLayer::close));
    m_pUiLayer->addWidget(btnclose);
    
    //UILabel *label = (UILabel*)m_pUiLayer->getWidgetByTag(8);
    UILabel *label=UILabel::create();
    label->setFontSize(32);
    label->setColor(ccYELLOW);
    label->setTag(11);
    sprintf(str,"等级LV %d-->LV %d",m_type.level,m_type.level+1);
    label->setText(str);
    label->setPosition(ccp(winSize.width/2, winSize.height/2-200));
    m_pUiLayer->addWidget(label);
    
    getHeros();
    return true;
}
void ZhuangBeiShengjiLayer::getHeroInfo(CCObject *sender)
{
    HeroInfoLayer *info=new HeroInfoLayer();
    addChild(info);
}
void ZhuangBeiShengjiLayer::menuPauseCallback(CCObject *sender)
{
    UIButton * btn=(UIButton*)sender;
    int tag=btn->getTag();
    int money=getexp(1.1,m_type.level);
    
    int totalmoney=CCUserDefault::sharedUserDefault()->getIntegerForKey("money",20000);
    CCUserDefault::sharedUserDefault()->flush();
     CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    vector<ZhuangBeiType> Zhuangs=GameData::shareGameData()->getZhuangbei();
    for (int i=0; i<Zhuangs.size(); ++i)
    {
        ZhuangBeiType zhuang=Zhuangs[i];
        if(zhuang.index==m_type.index)
        {
            int level=GameData::shareGameData()->mlevel;
            if(zhuang.level>=level)
            {
                CCSprite *bg=CCSprite::create("tipbg.png");
                bg->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(bg,1);
                CCActionInterval *action0=CCFadeOut::create(2);
                bg->runAction(action0);
                char str[64];
                sprintf(str,"装备等级不能大于主角等级");
                CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
                tiplabel->setColor(ccRED);
                tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(tiplabel,100);
                CCActionInterval *action=CCFadeOut::create(2);
                tiplabel->runAction(action);
                return;
            }
            int needmoney=80*zhuang.level+getexp(1.1, zhuang.level);
            //int needmoney=0;
            if(totalmoney>=needmoney)
            {
            zhuang.level+=1;
            m_type.level+=1;
            //UILabel *label = (UILabel*)m_pUiLayer->getWidgetByTag(8);
            UILabel *label = (UILabel*)m_pUiLayer->getWidgetByTag(11);
            char str[64];
            sprintf(str,"等级LV %d-->LV %d",zhuang.level,zhuang.level+1);
            label->setText(str);
            sprintf(str,"银两:%d",money);
            coinlabel->setText(str);
            GameData::shareGameData()->updateZhuang(zhuang);
            }
            else
            {
                CCSprite *bg=CCSprite::create("tipbg.png");
                bg->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(bg,1);
                CCActionInterval *action0=CCFadeOut::create(2);
                bg->runAction(action0);
                char str[32];
                sprintf(str,"金币不够");
                CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
                tiplabel->setColor(ccRED);
                tiplabel->setPosition(ccp(winSize.width/2,winSize.height/2));
                addChild(tiplabel,100);
                CCActionInterval *action=CCFadeOut::create(2);
                tiplabel->runAction(action);
                
            }
            
        }
    }
}
int ZhuangBeiShengjiLayer::getexp(float x, int n)
{
    if(n == 0)
    {
        return LEVELXP;
    }
    
    return x * getexp(x, n-1);
}
void ZhuangBeiShengjiLayer::close(CCObject *sender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_ZHUANG_UPDATE, (CCObject*)(intptr_t)0);
    removeFromParentAndCleanup(true);
}
void ZhuangBeiShengjiLayer::getHeros()
{
    
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int i=0; i<Heros.size(); ++i)
    {
        UIImageView* image=(UIImageView*)m_pUiLayer->getChildByTag(4);
        if(m_type.type==Heros[i].type)
        {
            image->setTexture(Heros[i].textureName.c_str());
            image->setScale(0.1);
        }
    }
}
void ZhuangBeiShengjiLayer::updateHero()
{

}
void ZhuangBeiShengjiLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127-1, false);
    CCLayer::registerWithTouchDispatcher();
}
bool ZhuangBeiShengjiLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}

void ZhuangBeiShengjiLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void ZhuangBeiShengjiLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}