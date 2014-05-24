//
//  GameMapLayer.cpp
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#include "GameMapLayer.h"
#include "FightLayer.h"
GameMapLayer::GameMapLayer()
{
	init();
}
GameMapLayer::~GameMapLayer()
{
	
}
bool GameMapLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    m_pUILayer = UILayer::create();
    addChild(m_pUILayer);
    

    setTouchEnabled(true);
    // build button on map root
    CCSize widgetSize =CCDirector::sharedDirector()->getWinSize();
    UIDragPanel* dragPanel = UIDragPanel::create();
    dragPanel->setTouchEnabled(true);
    dragPanel->setBounceEnabled(true);
    dragPanel->setBackGroundImageScale9Enabled(true);
    //dragPanel->setBackGroundImage("worldbg.png");
    dragPanel->setSize(widgetSize);
    CCSize backgroundSize = CCSize(640,1920);
    dragPanel->setPosition(ccp((widgetSize.width - backgroundSize.width) / 2 +
                               (backgroundSize.width - dragPanel->getRect().size.width) / 2,
                               (widgetSize.height - backgroundSize.height) / 2 +
                               (backgroundSize.height - dragPanel->getRect().size.height) / 2));
    dragPanel->setInnerContainerSize(backgroundSize);
    m_pUILayer->addWidget(dragPanel);
    UILayout* map_root = dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("GameMapLayer_1.json"));
    dragPanel->addChild(map_root);
//
    //UILayout* button_layout = dynamic_cast<UILayout*>(map_root->getChildByName("button_Panel"));
    string str[21] = {"延安府","史家村","寺庙","野猪林","沧州","郓城县","二龙山","青州","江州","梁山","祝家庄","北京城","曾头市","东平府","东京","水泊梁山","蓟州","苏州","杭州","官府"};
    for (unsigned int i = 0; i<20; ++i)
    {
        UIButton* button = (UIButton*)(map_root->getChildByTag(i));
        button->setTouchEnable(true);
        button->setFontSize(32);
        button->setTextColor(255,0,0);
        button->setText(str[i].c_str());
        button->addReleaseEvent(this, coco_releaseselector(GameMapLayer::buttonTouchEvent));
    }

//    UIImageView* imageView = UIImageView::create();
//    imageView->setTouchEnable(true);
//    imageView->setTexture("worldbg.png");
//    dragPanel->addChild(imageView);
//
//    string str[21] = {"延安府","史家村","寺庙","野猪林","沧州","郓城县","二龙山","青州","江州","梁山","祝家庄","北京城","曾头市","东平府","东京","水泊梁山","蓟州","苏州","杭州","东京"};
//    for (int i=0; i<20; i++)
//    {
//        UIButton *button = UIButton::create();
//        button->setTouchEnable(true);
//        button->loadTextures("hourse1.png", "hourse2.png", "");
//        button->setPosition(ccp(widgetSize.width / 2.0f+100*((i%3-1)),backgroundSize.height-80*i-200));
//        button->setTag(i);
//        button->addReleaseEvent(this,coco_releaseselector(GameMapLayer::buttonTouchEvent));
//        dragPanel->addChild(button);
//        
//        UILabel *label=UILabel::create();
//        label->setText(str[i].c_str());
//        label->setFontSize(32);
//        label->setColor(ccRED);
//        label->setPosition(ccp(widgetSize.width / 2.0f+100*((i%3-1)),backgroundSize.height-80*i-250));
//        dragPanel->addChild(label);
//    }
//    
//    dragPanel->setInnerContainerSize(imageView->getContentSize());
//    CCSize innerSize = dragPanel->getInnerContainerSize();
//    imageView->setPosition(ccp(innerSize.width / 2, innerSize.height / 2));
//    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
//    CCSprite* imageView = CCSprite::create("worldbg.png");
//    imageView->setPosition(ccp(winSize.width/2,960));
//    addChild(imageView);
//    
//    string str[21] = {"延安府","史家村","寺庙","野猪林","沧州","郓城县","二龙山","青州","江州","梁山","祝家庄","北京城","曾头市","东平府","东京","水泊梁山","蓟州","苏州","杭州","东京"};
//    for (int i=0; i<20; i++)
//    {
//        CCMenuItemImage* pHome = CCMenuItemImage::create("hourse1.png", "hourse1.png", this, menu_selector(GameMapLayer::buttonTouchEvent));
//        pHome->setPosition(ccp(winSize.width/2,winSize.height/2));
//        CCMenu *button = CCMenu::create(pHome,NULL);
//        button->setPosition(ccp(widgetSize.width / 2.0f+100*((i%3-1)),80*i+200));
//        pHome->setTag(i);
//        addChild(button);
//        
//        CCLabelTTF *label=CCLabelTTF::create(str[i].c_str(),"",32);
//        label->setFontSize(32);
//        label->setColor(ccRED);
//        label->setPosition(ccp(widgetSize.width / 2.0f+100*((i%3-1)),80*i+250));
//        addChild(label);
//    }
    return true;
}
void GameMapLayer::buttonTouchEvent(CCObject *sender)
{
    UIButton* pHome=(UIButton*)sender;
    int tag=pHome->getTag();
    int level=GameData::shareGameData()->mlevel;
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    if(level>=tag*5-10)
   {
    FightLayer *info=new FightLayer(tag);
    addChild(info);
    }
    else
    {
        CCSprite *bg=CCSprite::create("tipbg.png");
        bg->setPosition(ccp(winSize.width/2,winSize.height-300));
        addChild(bg,1);
        CCActionInterval *action0=CCFadeOut::create(2);
        bg->runAction(action0);
        char str[32];
        sprintf(str,"%d级开放",tag*5-10);
        CCLabelTTF* tiplabel=CCLabelTTF::create(str,"Arial",32);
        tiplabel->setPosition(ccp(winSize.width/2,winSize.height-300));
        addChild(tiplabel,100);
        CCActionInterval *action=CCFadeOut::create(2);
        tiplabel->runAction(action);
        
    }
}
void GameMapLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
void GameMapLayer::registerWithTouchDispatcher(void)
{
    CCLayer::registerWithTouchDispatcher();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, true);
}
bool GameMapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void GameMapLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
