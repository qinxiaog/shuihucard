//
//  GetHeroLayer.cpp
//  kapai
//
//  Created by qin on 14-3-25.
//
//

#include "GetHeroLayer.h"
#include "StoreLayer.h"
GetHeroLayer::GetHeroLayer()
{
	
}
GetHeroLayer::~GetHeroLayer()
{
	
}
bool GetHeroLayer::init(HeroType hero)
{
    if(!CCLayer::init()){
        return false;
    }
    CCSize winSize= CCDirector::sharedDirector()->getWinSize();

    CCSprite *bg=CCSprite::create("herolistbg.png");
    bg->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(bg,-1);
    
    CCSprite *sphero=CCSprite::create(hero.textureName.c_str());
    sphero->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(sphero);
    
    CCLabelTTF *name=CCLabelTTF::create(hero.name.c_str(),"",48);
    name->setPosition(ccp(winSize.width/2, winSize.height/2+280));
    name->setColor(ccBLUE);
    addChild(name);
    
    CCMenuItemImage* btn = CCMenuItemImage::create("close1.png", "close2.png", this, menu_selector(GetHeroLayer::close));
    CCMenu *menuclose=CCMenu::create(btn,NULL);
    menuclose->setPosition(ccp(winSize.width-60,winSize.height/2+300));
    addChild(menuclose,2);
    return true;
}
void GetHeroLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}