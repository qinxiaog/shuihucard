//
//  JiangLiLayer.cpp
//  kapai
//
//  Created by qin on 14-1-12.
//
//

#include "JiangLiLayer.h"
#include "GameData.h"

JiangLiLayer::JiangLiLayer()
{
	init();
}
JiangLiLayer::~JiangLiLayer()
{
	
}
bool JiangLiLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    int mlevel=GameData::shareGameData()->mlevel;
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UILayer *m_pUiLayer=UILayer::create();
    addChild(m_pUiLayer,1);
    
    UIImageView* imagehead= UIImageView::create();
    imagehead->setTexture("menubg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imagehead);
    
    
    UIScrollView* scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));
    
    scrollView->setPosition(ccp(0,winSize.height/2-360));
    m_pUiLayer->addWidget(scrollView);
    
    UIButton * btn= UIButton::create();
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(JiangLiLayer::close));
    btn->setTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width-60, winSize.height/2+300));
    m_pUiLayer->addWidget(btn);
    
    mlevel=GameData::shareGameData()->mlevel;
    bool support=CCUserDefault::sharedUserDefault()->getBoolForKey("support",false);
    bool level[9];
    for(int i=0;i<9;i++)
    {
        char str[64];
        sprintf(str,"level%d",i);
        level[i]=CCUserDefault::sharedUserDefault()->getBoolForKey(str,false);
    }
    CCUserDefault::sharedUserDefault()->flush();
    
    int number=10;
    if(support)
        number=9;
    for(int i=0;i<number;i++)
    {
        UIImageView* imageView = UIImageView::create();
        imageView->setTexture("cellbg.png");
        float innerWidth = scrollView->getRect().size.width;
        float innerHeight =(imageView->getRect().size.height)*number;
        
        scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
        
        int imageHeight=imageView->getRect().size.height;
        imageView->setPosition(ccp(winSize.width/2,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
        scrollView->addChild(imageView);
        
        
        UIImageView* imagehead= UIImageView::create();
        imagehead->setTexture("yuanbao.png");
        imagehead->setPosition(ccp(winSize.width/2-140,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
        scrollView->addChild(imagehead);
        
        char str[64];
        if(i<9)
        {
                sprintf(str,"%d",(i+1)*20000);
        }
        else
        {
                sprintf(str,"%d",50000);
        }
        
        UILabel *moneyLabel=UILabel::create();
        moneyLabel->setText(str);
        moneyLabel->setColor(ccBLACK);
        moneyLabel->setFontSize(32);
        moneyLabel->setPosition(ccp(winSize.width/2+100,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
        scrollView->addChild(moneyLabel);
        
       if(i<9)
       {
        sprintf(str,"%d级\n礼包",10*(i+1));
       }
       else
        {
            sprintf(str,"5星评论");
        }
        UILabel *label=UILabel::create();
        label->setFontSize(32);
        label->setText(str);
        label->setColor(ccBLUE);
        scrollView->addChild(label);
        label->setPosition(ccp(100,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
        
//        UIImageView* imagecoin= UIImageView::create();
//        imagecoin->setTexture("dollar.png");
//        imagecoin->setPosition(ccp(350,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
//        scrollView->addChild(imagecoin);
        
        if(i<9)
        {
            sprintf(str,"%d",(i+1)*100);
        }
        else
        {
            sprintf(str,"%d",500);
        }
        
        UILabel *coinLabel=UILabel::create();
        coinLabel->setText(str);
        coinLabel->setFontSize(32);
        coinLabel->setColor(ccBLACK);
        coinLabel->setPosition(ccp(winSize.width/2-70,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
        scrollView->addChild(coinLabel);
        
        UIButton* button = UIButton::create();
//        if(level[i])//已经领取
//        {
//            button->setTouchEnable(false);
//            button->loadTextures("fight1.png", "fight1.png", "");
//            button->addReleaseEvent(this, coco_releaseselector(JiangLiLayer::menuCallback));
//        }
       if(mlevel>=10*(i+1))//等级满足
        {
            button->setTouchEnable(true);
            button->loadTextures("getmoney2.png", "getmoney1.png", "");
            button->addReleaseEvent(this, coco_releaseselector(JiangLiLayer::menuPauseCallback));
        }
        else//等级不满足
        {
            button->setTouchEnable(false);
            button->loadTextures("getmoney1.png", "getmoney2.png", "");
            button->addReleaseEvent(this, coco_releaseselector(JiangLiLayer::menuCallback));
        }
        if(i==9)//等级满足
        {
            button->setTouchEnable(true);
            button->loadTextures("getmoney2.png", "getmoney1.png", "");
            button->addReleaseEvent(this, coco_releaseselector(JiangLiLayer::menuPauseCallback));
        }
        button->setPosition(ccp(winSize.width-100, scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
        button->setTag(i);
        scrollView->addChild(button);
        }
    return true;
}
void JiangLiLayer::menuCallback(CCObject *sender)
{
    
}
void JiangLiLayer::menuPauseCallback(CCObject *sender)
{
    UIButton* button=(UIButton*)sender;
    int tag=button->getTag();
    button->setTouchEnable(false);
    int money=GameData::shareGameData()->mMoney;
    int coin=GameData::shareGameData()->mCoin;
    if(tag<9)
    {
    money+=(tag+1)*20000;
    coin+=(tag+1)*100;
    char str[32];
    sprintf(str,"level%d",tag);
    CCUserDefault::sharedUserDefault()->setBoolForKey(str,true);
    }
    else
    {
        money+=50000;
        coin+=500;
        CCUserDefault::sharedUserDefault()->setBoolForKey("support",true);
        CCUserDefault::sharedUserDefault()->flush();
    }
    button->setEnabled(false);
    button->setTextures("","","");
    GameData::shareGameData()->setMoney(money);
    GameData::shareGameData()->setCoin(coin);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_LEVEL_UPDATE);
}
void JiangLiLayer::close(CCObject *sender)
{
    this->removeFromParentAndCleanup(true);
}