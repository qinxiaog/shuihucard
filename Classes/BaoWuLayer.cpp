//
//  BaoWuLayer.cpp
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#include "BaoWuLayer.h"
BaoWuLayer::BaoWuLayer()
{
	init();
}
BaoWuLayer::~BaoWuLayer()
{
	
}
bool BaoWuLayer::init()
{
    if(!CCLayer::init()){
        return false;
    }
    UILayer *m_pUiLayer=UILayer::create();
    addChild(m_pUiLayer,1);
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    UIScrollView* scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,winSize.height-200));
    CCSize backgroundSize =CCSize(500,100);
    scrollView->setPosition(ccp((winSize.width - backgroundSize.width) / 2 +
                                (backgroundSize.width - scrollView->getRect().size.width) / 2,
                                (winSize.height - backgroundSize.height) / 2 +
                                (backgroundSize.height - scrollView->getRect().size.height) / 2));
    m_pUiLayer->addWidget(scrollView);
    
    for(int i=0;i<10;i++)
    {
        UIImageView* imageView = UIImageView::create();
        imageView->setTexture("scrollbg.png");
        float innerWidth = scrollView->getRect().size.width;
        float innerHeight = scrollView->getRect().size.height + imageView->getRect().size.height*10;
        
        scrollView->setInnerContainerSize(CCSizeMake(innerWidth, innerHeight));
        
        
        imageView->setPosition(ccp(innerWidth / 2,scrollView->getInnerContainerSize().height-imageView->getRect().size.height*i));
        scrollView->addChild(imageView);
        UIButton* button = UIButton::create();
        button->setTouchEnable(true);
        button->loadTextures("fight1.png", "fight1.png", "");
        button->setPosition(ccp(innerWidth / 2, scrollView->getInnerContainerSize().height-imageView->getRect().size.height*i));
        scrollView->addChild(button);
        
        UITextButton* textButton = UITextButton::create();
        textButton->setTouchEnable(true);
        textButton->loadTextures("group1.png", "group1.png", "");
        textButton->setText("Text Button");
        textButton->setPosition(ccp(winSize.width-200,scrollView->getInnerContainerSize().height - button->getRect().size.height*i));
        scrollView->addChild(textButton);
        
        //    UIButton* button_scale9 = UIButton::create();
        //    button_scale9->setTouchEnable(true);
        //    button_scale9->setScale9Enabled(true);
        //    button_scale9->loadTextures("group1.png", "group1.png", "");
        //    button_scale9->setSize(CCSizeMake(100, button_scale9->getContentSize().height));
        //    button_scale9->setPosition(ccp(innerWidth / 2, textButton->getRelativeBottomPos() - textButton->getRect().size.height));
        //    scrollView->addChild(button_scale9);
        
        
    }
    return true;
}