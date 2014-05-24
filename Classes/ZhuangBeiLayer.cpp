//
//  ZhuangBeiLayer.cpp
//  kapai
//
//  Created by qin on 13-12-20.
//
//

#include "ZhuangBeiLayer.h"
#include "GameData.h"
#include "HeroLayer.h"
#include "ZhuangBeiShengji.h"
ZhuangBeiListLayer::ZhuangBeiListLayer()
{
	
}
ZhuangBeiListLayer::~ZhuangBeiListLayer()
{
	
}
bool ZhuangBeiListLayer::init(HeroType hero,int type,ZhuangBeiType zhuang)
{
    if(!CCLayer::init()){
        return false;
    }
    m_hero=hero;
    m_type=type;
    m_zhuangtype=zhuang;
    setData(hero,type,zhuang);
    return true;
}
void ZhuangBeiListLayer::setData(HeroType hero,int type,ZhuangBeiType zhuangtype)
{
    UILayer*m_pUiLayer=UILayer::create();
    addChild(m_pUiLayer,0);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIImageView * imagebg=UIImageView::create();
    setTouchEnabled(true);
    imagebg->setTexture("herobg.png");
    imagebg->setPosition(ccp(winSize.width/2, winSize.height/2));
    m_pUiLayer->addWidget(imagebg);
    

    
    UIScrollView*scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));

    scrollView->setPosition(ccp(0,winSize.height/2-360));
    m_pUiLayer->addWidget(scrollView);
    

    vector<ZhuangBeiType> zhuangBeis=GameData::shareGameData()->getZhuangbei();
    int j=0;
    for(int i=0;i<zhuangBeis.size();i++)
    {
        ZhuangBeiType zhuang=zhuangBeis[i];
         int t=(type+3)*100;
        printf("zhuangtype==%d,%d,%d",zhuang.type,t,m_type);
       
        if((zhuang.type>=t&&zhuang.type<(t+100))||type==-1)
        {
            j++;
            UIImageView* imageView = UIImageView::create();
            imageView->setTexture("cellbg.png");
            int imageHeight=imageView->getRect().size.height;
            float innerWidth = scrollView->getRect().size.width;
            float innerHeight = scrollView->getRect().size.height +imageHeight*zhuangBeis.size();
            scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
            
            
            imageView->setPosition(ccp(innerWidth / 2,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/2));
            scrollView->addChild(imageView);
            
            UIImageView* imagebg= UIImageView::create();
            imagebg->setTexture("addbutton.png");
            imagebg->setPosition(ccp(120,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/2));
            scrollView->addChild(imagebg);
            
            UIImageView* imageHead = UIImageView::create();
            imageHead->setTexture(zhuang.textureName.c_str());
            imageHead->setPosition(ccp(120,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/2));
            scrollView->addChild(imageHead);
            
            UILabel *label=UILabel::create();
            char strlevel[32];
            sprintf(strlevel,"Lv:%d",zhuang.level);
            label->setFontSize(24);
            label->setText(strlevel);
            label->setColor(ccBLUE);
            label->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight-60));
            scrollView->addChild(label);
            
            UILabel *namelabel=UILabel::create();
            namelabel->setFontSize(24);
            namelabel->setText(zhuang.name.c_str());
            namelabel->setColor(ccBLUE);
            namelabel->setPosition(ccp(winSize.width/2,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight-60));
            scrollView->addChild(namelabel);
            
            if(zhuang.hp>0)
            {
                UIImageView* imageattack = UIImageView::create();
                imageattack->setTexture("heart.png");
                imageattack->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(imageattack);
                UILabel *label=UILabel::create();
                label->setPosition(ccp(winSize.width/2-40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(label);
                char str[32];
                int hp=zhuang.hp+(40+10*zhuang.star)*zhuang.level;
                sprintf(str,"%d",hp);
                label->setFontSize(24);
                label->setColor(ccBLACK);
                label->setText(str);
            }
            if(zhuang.ap>0)
            {
            UIImageView* imageattack = UIImageView::create();
            imageattack->setTexture("swordicon.png");
            imageattack->setPosition(ccp(winSize.width/2+40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
            scrollView->addChild(imageattack);
            UILabel *label=UILabel::create();
            label->setPosition(ccp(winSize.width/2+100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
            scrollView->addChild(label);
            char str[32];
            int ap=zhuang.ap+(10+2*zhuang.star)*zhuang.level;
            sprintf(str,"%d",ap);
            label->setColor(ccBLACK);
            label->setFontSize(24);
            label->setText(str);
                
            }

            if(zhuang.defender>0)
            {
                UIImageView* imageattack = UIImageView::create();
                imageattack->setTexture("fang.png");
                imageattack->setPosition(ccp(winSize.width/2-100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(imageattack);
                UILabel *label=UILabel::create();
                label->setPosition(ccp(winSize.width/2-40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(label);
                char str[32];
                int defender=zhuang.defender+(6+1*zhuang.star)*zhuang.level;
                sprintf(str,"%d",defender);
                label->setColor(ccBLACK);
                label->setFontSize(24);
                label->setText(str);
            }
            if(zhuang.magicdefender>0)
            {
                UIImageView* imageattack = UIImageView::create();
                imageattack->setTexture("mofang.png");
                imageattack->setPosition(ccp(winSize.width/2+40,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(imageattack);
                UILabel *label=UILabel::create();
                label->setPosition(ccp(winSize.width/2+100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
                scrollView->addChild(label);
                char str[32];
                int magicdefender=zhuang.magicdefender+(6+1*zhuang.star)*zhuang.level;
                sprintf(str,"%d",magicdefender);
                label->setFontSize(24);
                label->setColor(ccBLACK);
                label->setText(str);
            }
            for(int i=0;i<zhuang.star;i++)
            {
                UIImageView* imageattack = UIImageView::create();
                imageattack->setTexture("star.png");
                imageattack->setPosition(ccp(winSize.width/2+i*20+100,scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight-60));
                scrollView->addChild(imageattack);
            }

            UIButton* button = UIButton::create();
            button->setTouchEnable(true);
            button->setTag(zhuang.index);
            //string texturename=zhuang.textureName;
            if(type==-1)
            {
            button->loadTextures("heroup1.png", "heroup2.png", "");
            button->addReleaseEvent(this, coco_releaseselector(ZhuangBeiListLayer::Shengji));
            }
            else
            {
                button->loadTextures("zhuangbei1.png", "zhuangbei2.png", "");
                button->addReleaseEvent(this, coco_releaseselector(ZhuangBeiListLayer::menuPauseCallback));
            }
            
            button->setPosition(ccp(winSize.width-120, scrollView->getInnerContainerSize().height-imageHeight*j+imageHeight/3));
            scrollView->addChild(button);
        }
    }
    UIButton * btn= UIButton::create();
    btn->setTouchEnable(true);
    btn->addReleaseEvent(this, coco_releaseselector(ZhuangBeiListLayer::close));
    btn->setTextures("close1.png","close2.png","close2.png");
    btn->setPosition(ccp(winSize.width-60, winSize.height/2+300));
    m_pUiLayer->addWidget(btn);
}
int ZhuangBeiListLayer::getexp(int ap,float x, int n)
{
    if(n == 0)
    {
        return ap;
    }
    
    return x * getexp(ap,x, n-1);
}
void ZhuangBeiListLayer::Zhuangupdate()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,MSG_ZHUANG_UPDATE);
    removeAllChildrenWithCleanup(true);
    setData(m_hero,m_type,m_zhuangtype);
}
void ZhuangBeiListLayer::menuPauseCallback(CCObject *sender)
{
    UIButton* button=(UIButton*)sender;
    int index=button->getTag();
    vector<ZhuangBeiType> zhuangBeis=GameData::shareGameData()->getZhuangbei();
    for(int i=0;i<zhuangBeis.size();i++)
    {
        ZhuangBeiType zhuang=zhuangBeis[i];
        if(index==zhuang.index)
        {
            GameData::shareGameData()->changeZhuangBei(m_hero,zhuang,m_type);
            CCNotificationCenter::sharedNotificationCenter()->postNotification(MSG_CHANGE_STATE, (CCObject*)(intptr_t)index);
            this->removeFromParentAndCleanup(true);
        }
    }
}
void ZhuangBeiListLayer::Shengji(CCObject *sender)
{
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ZhuangBeiListLayer::Zhuangupdate),MSG_ZHUANG_UPDATE, NULL);
    UIButton* button=(UIButton*)sender;
    int index=button->getTag();
    vector<ZhuangBeiType> zhuangBeis=GameData::shareGameData()->getZhuangbei();
    for(int i=0;i<zhuangBeis.size();i++)
    {
        ZhuangBeiType zhuang=zhuangBeis[i];
        if(index==zhuang.index)
        {
            ZhuangBeiShengjiLayer *layer=new ZhuangBeiShengjiLayer();
            layer->init(zhuang);
            addChild(layer,10);
        }
    }

    
}
void ZhuangBeiListLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}
