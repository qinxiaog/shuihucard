//
//  TipWindows.cpp
//  kapai
//
//  Created by qin on 14-1-12.
//
//

#include "TipWindows.h"
#include "BattleScene.h"
TipWindows::TipWindows(string str)
{
    init(str);
}
TipWindows::~TipWindows()
{
    
}
bool TipWindows::init(string str)
{
    if(!CCLayer::init())
    {
        return false;
    }

    fontsize=36;
    h=80;
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();
    CCSprite*   child = CCSprite::create("loginbg.png");
    child->setPosition(ccp(winSize.width/2,winSize.height/2));
    this->addChild(child,-1);
    //    char strLevel[64]="Time Out";
    //    char strContinue[64]="continue";
    //    int i=CCApplication::sharedApplication()->getCurrentLanguage();
    //    if(i==1)
    //    {
    //        strcpy(strLevel,"时间到");
    //        strcpy(strContinue,"继续游戏");
    //    }
    //    CCLabelTTF* levelLabel=CCLabelTTF::create(strLevel,"CourierNewPS-BoldItalicMT",48);
    //    levelLabel->setPosition(ccp(winsize.width/2, winsize.height/2+50));
    //    //levelLabel->setColor(ccBLACK);
    //    addChild(levelLabel);
    
    tipLabel=CCLabelTTF::create();
    tipLabel->setFontSize(48);
    tipLabel->setColor(ccBLUE);
    tipLabel->setPosition(ccp(winSize.width/2,winSize.height/2+80));
    tipLabel->setString(str.c_str());
    addChild(tipLabel);
    
    int i=CCApplication::sharedApplication()->getCurrentLanguage();
//    CCSprite *set=CCSprite::create("timeout_cn.png");
//    set->setPosition(ccp(winSize.width/2, winSize.height/2+20));
//    addChild(set);
    
//    CCSprite *styleSp=CCSprite::create("ok_cn.png");
//    styleSp->setPosition(ccp(winSize.width/2, winSize.height/2-120));
//    addChild(styleSp,2);
    CCMenuItemImage *item =CCMenuItemImage::create("ok1.png","ok2.png",this, menu_selector(TipWindows::nextCallback));
    CCMenu *menu =CCMenu::create(item,NULL);
    this->addChild(menu,1);
    menu->setPosition(ccp(winSize.width/2,winSize.height/2-120));
    
    //    CCLabelTTF* continueLabel=CCLabelTTF::create(strContinue,"CourierNewPS-BoldItalicMT",48);
    //    continueLabel->setPosition(ccp(winsize.width/2, winsize.height/2-120));
    //    addChild(continueLabel,1);
    return  true;
}
void TipWindows::back(CCObject *sender)
{
    this->removeAllChildrenWithCleanup(true);
}
void TipWindows::nextCallback(CCObject *sender)
{
    CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_BATTLE, (CCObject*)(intptr_t)0);
    this->removeAllChildrenWithCleanup(true);
}