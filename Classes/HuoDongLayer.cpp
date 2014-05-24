//
//  HuoDongLayer.cpp
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#include "HuoDongLayer.h"
HuoDongLayer::HuoDongLayer()
{
	
}
HuoDongLayer::~HuoDongLayer()
{
	
}
bool HuoDongLayer::init(HeroType hero,int type)
{
    if(!CCLayer::init()){
        return false;
    }
    m_oldHero=hero;
    mindex=type;
    UILayer *m_pUiLayer=UILayer::create();
    addChild(m_pUiLayer,1);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIImageView* imagehead= UIImageView::create();
    imagehead->setTexture("menubg.png");
    imagehead->setPosition(ccp(winSize.width/2,winSize.height/2));
    m_pUiLayer->addWidget(imagehead);
    
    UIScrollView* scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,winSize.height-200));
    //CCSize backgroundSize =CCSize(500,200);
    scrollView->setPosition(ccp(0,0));
    m_pUiLayer->addWidget(scrollView);
    
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    for(int i=0;i<Heros.size();i++)
    {
        HeroType hero=Heros[i];
        if(hero.pos<=0||type==-1)
        {
            UIImageView* imageView = UIImageView::create();
            imageView->setTexture("cellbg.png");
            float innerWidth = scrollView->getRect().size.width;
            float innerHeight = scrollView->getRect().size.height + imageView->getRect().size.height*10;
            
            scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
            
            int imageHeight=imageView->getRect().size.height;
            imageView->setPosition(ccp(innerWidth /2,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            scrollView->addChild(imageView);
            
            
            UIImageView* imagehead= UIImageView::create();
            imagehead->setTexture(hero.textureName.c_str());
            imagehead->setScale(0.2);
            imagehead->setPosition(ccp(100,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            scrollView->addChild(imagehead);
            
            UIImageView* imagehp= UIImageView::create();
            imagehp->setTexture("heart.png");
            imagehp->setPosition(ccp(200,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            scrollView->addChild(imagehp);
            
            char str[32];
            sprintf(str,"%d",hero.ap);
            UILabel *label=UILabel::create();
            label->setText(str);
            label->setPosition(ccp(250,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            scrollView->addChild(label);
            
            
            UIImageView* imageap= UIImageView::create();
            imageap->setTexture("swordicon.png");
            imageap->setPosition(ccp(300,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            scrollView->addChild(imageap);
            
            sprintf(str,"%d",hero.hp);
            UILabel *hplabel=UILabel::create();
            hplabel->setText(str);
            hplabel->setPosition(ccp(350,scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            scrollView->addChild(hplabel);
            
            UIButton* button = UIButton::create();
            button->setTouchEnable(true);
            if(type<0)
            {
                button->loadTextures("heroup1.png", "heroup2.png", "");
                button->addReleaseEvent(this, coco_releaseselector(HuoDongLayer::menuPauseCallback));
            }
            else
            {
                button->loadTextures("changhero1.png", "changhero2.png", "");
                button->addReleaseEvent(this, coco_releaseselector(HuoDongLayer::menuCallback));
            }
            button->setPosition(ccp(winSize.width-100, scrollView->getInnerContainerSize().height-imageHeight*i-imageHeight/2));
            button->setTag(hero.index);
            scrollView->addChild(button);
        }
        
    }
    UIButton * btn= UIButton::create();
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(HuoDongLayer::close));
    btn->setTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width-100, winSize.height-150));
    m_pUiLayer->addWidget(btn);
    return true;
}
void HuoDongLayer::close()
{
    removeFromParentAndCleanup(true);
}
void HuoDongLayer::menuCallback(CCObject *sender)
{
    UIButton* button=(UIButton*)sender;
    int tag=button->getTag();
    vector<HeroType> Heros=GameData::shareGameData()->getHeros();
    
    HeroType hero;
}
void HuoDongLayer::menuPauseCallback(CCObject *sender)
{

}
void HuoDongLayer::Heroupdate(){
    
}