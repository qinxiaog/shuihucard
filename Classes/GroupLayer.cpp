//
//  GroupLayer.cpp
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#include "GroupLayer.h"
#include "BattleScene.h"
#include "HeroListLayer.h"
GroupLayer::GroupLayer()
{
	init();
}
GroupLayer::~GroupLayer()
{
	
}
bool GroupLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    setTouchEnabled(true);
    selectButton=NULL;

    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
     m_pUiLayer=UILayer::create();
    //ul->setPosition(ccp(0,winSize.height/2));
    this->addChild(m_pUiLayer);
    selectIndex=0;
    UIImageView* imagehead= UIImageView::create();
    imagehead->setTexture("herolistbg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imagehead);
//    UIWidget* example_root = GUIReader::shareReader()->widgetFromJsonFile("GroupLayer_1.json");
//    m_pUiLayer->addWidget(example_root);
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int i=1; i<7; i++)
    {

        //UIButton * btn= dynamic_cast<UIButton *>(m_pUiLayer->getWidgetByTag(i));
        
        UIButton * btn=UIButton::create();
        btn->setTextures("add.png","add.png","");
        btn->setName("button");
        btn->setTouchEnable(true);
        btn->setPosition(ccp(winSize.width/2+180*((i-1)%3-1),winSize.height/3+30+250*((6-i)/3)));
        btn->addReleaseEvent(this, coco_releaseselector(GroupLayer::menuPauseCallback));
        btn->setTag(i);
        m_pUiLayer->addWidget(btn);
    }
    for (int j=0; j<Heros.size(); j++)
    {
        HeroType hero=Heros[j];
        if(hero.pos>0)
        {
        int pos=hero.pos;
        string texturename=hero.textureName;
        UIButton * btn= dynamic_cast<UIButton *>(m_pUiLayer->getWidgetByTag(pos));
        btn->setScale(0.4);
        btn->setName(texturename.c_str());
        btn->setTextures(texturename.c_str(), texturename.c_str(),"");
        
        UILabel *label=UILabel::create();
        label->setFontSize(64);
        char str[32];
        sprintf(str,"%s",hero.name.c_str());
        label->setText(str);
        label->setColor(ccMAGENTA);
        label->setPosition(ccp(0,-btn->getContentSize().height/2));
        btn->addChild(label);
        }
    }
    UIButton * btn= UIButton::create();
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(GroupLayer::close));
    btn->setTextures("ok1.png","ok2.png","ok2.png");
    btn->setPosition(ccp(winSize.width/2,winSize.height/2-320));
    m_pUiLayer->addWidget(btn);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GroupLayer::addHero),MSG_ADD_HERO, NULL);
    //CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GroupLayer::changeHero),MSG_CHANGE_HERO, NULL);
    return true;
}
void GroupLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_ADD_HERO);
    //CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, MSG_CHANGE_HERO);
}
void GroupLayer::close()
{
    removeFromParentAndCleanup(true);
}
void GroupLayer::addHero(CCObject *sender)
{
    int index=(int)sender;
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int j=0; j<Heros.size(); j++)
    {
        HeroType hero=Heros[j];
        if(hero.index==index)
        {
            UIButton * controlButton= dynamic_cast<UIButton *>(m_pUiLayer->getWidgetByTag(selectIndex));
            hero.pos=selectIndex;
            GameData::shareGameData()->addHero(hero);
            string texturename=hero.textureName;
            controlButton->setName(texturename.c_str());
            controlButton->setTextures(texturename.c_str(), texturename.c_str(),"");
            controlButton->setScale(0.4);
        }
    }
}
void GroupLayer::changeHero(CCObject *sender)
{
    int index=(int)sender;
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for (int j=0; j<Heros.size(); j++)
    {
        HeroType hero=Heros[j];
        if(hero.index==index)
        {
            UIButton * controlButton= dynamic_cast<UIButton *>(m_pUiLayer->getWidgetByTag(selectIndex));
            hero.pos=selectIndex;
            string texturename=hero.textureName;
            controlButton->setName(texturename.c_str());
            controlButton->setTextures(texturename.c_str(), texturename.c_str(),"");
            controlButton->setScale(0.4);
        }
    }
}
void GroupLayer::menuPauseCallback(CCObject *sender)
{
    UIButton * btnpress=(UIButton*)sender;
    selectIndex=btnpress->getTag();
     if(!strcmp(btnpress->getName(),"button"))
     {
         HeroType hero;
         hero.pos=0;
         HeroListLayer *list=new HeroListLayer();
         list->init(hero,-2);
         list->autorelease();
         addChild(list,10);
     }
//
//        vector<HeroType> Heros=GameData::shareGameData()->getHeros();
//        for(int i=0;i<Heros.size();i++)
//        {
//            HeroType hero=Heros[i];
//            if(hero.pos==selectIndex&&!strcmp(btnpress->getName(),hero.textureName.c_str()))
//            {
//                HeroListLayer *list=new HeroListLayer();
//                list->init(hero,1);
//                list->autorelease();
//                addChild(list,10);
//            }
//        }
}
void GroupLayer::draw()
{
    
    ccDrawRect(ccp(transRect.origin.x-32,transRect.origin.y+32),ccp(transRect.origin.x+32,transRect.origin.y-32));
    //ccDrawRect(ccp(100,100),ccp(328,328));
    glLineWidth(10.0f );
}
void  GroupLayer::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127+1,false);
   CCLayer::registerWithTouchDispatcher();
}
bool GroupLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
    for(int i=1;i<7;i++)
    {
       UIButton * controlButton= dynamic_cast<UIButton *>(m_pUiLayer->getWidgetByTag(i));
       if(controlButton->getRect().containsPoint(touchLocation))
       {
            selectButton=controlButton;
            oldPositon=controlButton->getPosition();
       }
    }
    return true;
}
void GroupLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    if(selectButton)
    {
    CCPoint touchLocation = this->convertTouchToNodeSpace(touch);
    selectButton->setPosition(touchLocation);
    }
}
void GroupLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    bool bTurn=false;
    UIButton *transButton=NULL;
    if(selectButton)
    {
        for(int i=1;i<7;i++)
        {
            UIButton * controlButton= dynamic_cast<UIButton *>(m_pUiLayer->getWidgetByTag(i));
            CCRect selectRect=CCRect(selectButton->getPosition().x-32,selectButton->getPosition().y+32,64,64);
            transRect=CCRect(controlButton->getPosition().x-32,controlButton->getPosition().y+32,64,64);
            if(selectRect.intersectsRect(transRect)&&selectButton->getTag()!=controlButton->getTag())
            {
                selectButton->setPosition(controlButton->getPosition());
                controlButton->setPosition(oldPositon);
                int oldtag=selectButton->getTag();
                
                transButton=controlButton;
                vector<HeroType> Heros=GameData::shareGameData()->getHeros();
                HeroType selectHero;
                HeroType transHero;
                for(int i=0;i<Heros.size();i++)
                {
                    HeroType hero=Heros[i];
                    if (hero.pos>0&&!hero.textureName.compare(selectButton->getName()))
                    {
                        selectHero=hero;
                    }
                    else if(hero.pos>0&&!hero.textureName.compare(transButton->getName()))
                    {
                        transHero=hero;
                    }
                }
                if(selectHero.pos>0)
                {
                    selectHero.pos=transButton->getTag();
                    GameData::shareGameData()->updateHero(selectHero);
                }
                if(transHero.pos>0)
                {
                    transHero.pos=selectButton->getTag();
                    GameData::shareGameData()->updateHero(transHero);
                }
                selectButton->setTag(transButton->getTag());
                controlButton->setTag(oldtag);
                bTurn=true;
                break;
            }
        }
        if(!bTurn)
        {
            selectButton->setPosition(oldPositon);
        }
    }
    selectButton=NULL;
}