//
//  HeroInfoLayer.cpp
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#include "HeroInfoLayer.h"
HeroInfoLayer::HeroInfoLayer()
{
	
}
HeroInfoLayer::~HeroInfoLayer()
{
	
}
bool HeroInfoLayer::init(HeroType hero)
{
    if(!CCLayer::init()){
        return false;
    }
    m_hero=hero;
    layer=NULL;
    CCSize size= CCDirector::sharedDirector()->getWinSize();
    CCSprite *bg=CCSprite::create("herolistbg.png");
    bg->setPosition(ccp(size.width/2,size.height/2));
    addChild(bg);
    setTouchEnabled(true);
    m_pUiLayer=UILayer::create();
    this->addChild(m_pUiLayer);
    
    CCSize winSize =CCDirector::sharedDirector()->getWinSize();
    scrollView = UIScrollView::create();
    scrollView->setTouchEnable(true);
    scrollView->setBounceEnabled(true);
    scrollView->setSize(CCSize(winSize.width,600));
    scrollView->setPosition(ccp(0,winSize.height/2-360));
    scrollView->setInnerContainerSize(CCSizeMake(winSize.width,1920));
    m_pUiLayer->addWidget(scrollView);
    
    UIWidget* example_root = GUIReader::shareReader()->widgetFromJsonFile("HeroInfoLayer_1.json");
    scrollView->addChild(example_root);
//    for(int i=21;i<24;i++)
//    {
//        UIButton* btn=(UIButton*)example_root->getChildByTag(i);
//        btn->setTouchEnabled(true);
//        btn->addReleaseEvent(this, coco_releaseselector(HeroInfoLayer::menuPauseCallback));
//    }
    UIImageView *image=(UIImageView*)example_root->getChildByTag(3);
    image->setTexture(hero.textureName.c_str());
    
    char strLevel[32];
    sprintf(strLevel,"%s+%d",hero.name.c_str(),hero.exlevel);
    UILabel *nameLabel=UILabel::create();
    nameLabel->setPosition(ccp(winSize.width-200,1920-50));
    nameLabel->setFontSize(48);
    nameLabel->setText(strLevel);
    scrollView->addChild(nameLabel);
    
    int star=5;
    if(hero.type>=36&&hero.type!=108)
        star=4;
    for(int i=0;i<star;i++)
    {
        UIImageView *image=UIImageView::create();
        image->setTexture("star.png");
        image->setPosition(ccp(winSize.width-25*i-60,1920-100));
        scrollView->addChild(image);
//        UILabel *label=UILabel::create();
//        label->setText("★");
//        label->setColor(ccYELLOW);
//        label->setFontSize(16);
//        label->setPosition(ccp(winSize.width-20*i-100,1920-100));
//        scrollView->addChild(label);
    }
    
    sprintf(strLevel,"%d",hero.exlevel);
    UILabel *exLevelLabel=(UILabel*)example_root->getChildByTag(32);
    exLevelLabel->setColor(ccYELLOW);
    exLevelLabel->setFontSize(32);
    exLevelLabel->setText(strLevel);
    
    sprintf(strLevel,"%d",hero.level);
    UILabel *LevelLabel=(UILabel*)example_root->getChildByTag(33);
    LevelLabel->setFontSize(32);
    LevelLabel->setText(strLevel);
    
    sprintf(strLevel,"%d",hero.totalhp);
    UILabel *hpLevelLabel=(UILabel*)example_root->getChildByTag(34);
    hpLevelLabel->setFontSize(32);
    hpLevelLabel->setText(strLevel);
    
    sprintf(strLevel,"%d",hero.totalap);
    UILabel *apLevelLabel=(UILabel*)example_root->getChildByTag(35);
    apLevelLabel->setFontSize(32);
    apLevelLabel->setText(strLevel);
    
    sprintf(strLevel,"%d",hero.totaldefend);
    UILabel *defendLabel=(UILabel*)example_root->getChildByTag(36);
    defendLabel->setFontSize(32);
    defendLabel->setText(strLevel);
    
    sprintf(strLevel,"%d",hero.totalmagicdefend);
    UILabel *magicLabel=(UILabel*)example_root->getChildByTag(37);
    magicLabel->setFontSize(32);
    magicLabel->setText(strLevel);
    
    UIImageView *skillsimage=(UIImageView*)example_root->getChildByTag(51);
    UILabel *skillsLabel=UILabel::create();
    skillsLabel->setFontSize(48);
    skillsLabel->setText("技能");
    skillsLabel->setPosition(ccp(skillsimage->getPosition().x+10,skillsimage->getPosition().y-10));
    scrollView->addChild(skillsLabel);
    
    UIImageView *qianghuaimage=(UIImageView*)example_root->getChildByTag(52);
    UILabel *qianghuaLabel=UILabel::create();
    qianghuaLabel->setFontSize(48);
    qianghuaLabel->setText("强化");
    qianghuaLabel->setPosition(ccp(qianghuaimage->getPosition().x+10,qianghuaimage->getPosition().y-10));
    scrollView->addChild(qianghuaLabel);
    
    UIImageView *jianjieimage=(UIImageView*)example_root->getChildByTag(53);
    UILabel *jianjieLabel=UILabel::create();
    jianjieLabel->setFontSize(48);
    jianjieLabel->setText("简介");
    jianjieLabel->setPosition(ccp(jianjieimage->getPosition().x+10,jianjieimage->getPosition().y-10));
    scrollView->addChild(jianjieLabel);
    
    char str[2048];
    int skills=hero.skillsid;
    if(skills<100)
    sprintf(str,"普通攻击:对单体造成80％-120％伤害\n必杀技:%s 对单体造成320％-380％攻击伤害",hero.skillsname.c_str());
    else if(skills>=100&&skills<=200)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对全体造成60％-100％攻击伤害",hero.skillsname.c_str());
    else if(skills>=200&&skills<300)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对前排造成120％-160％攻击伤害",hero.skillsname.c_str());
    else if(skills>=300&&skills<400)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对后排造成120％-160％攻击伤害",hero.skillsname.c_str());
    else if(skills>=400&&skills<500)
        sprintf(str,"普通攻击:对单体造成造成80％-120％伤害\n必杀技:%s 对竖排造成200％-240％攻击伤害",hero.skillsname.c_str());
    UITextArea *label=(UITextArea*)example_root->getChildByTag(41);
    label->setTextAreaSize(CCSize(540,300));
    label->setColor(ccYELLOW);
    label->setText(str);
    label->setFontSize(32);
    label->setPosition(ccp(winSize.width/2,label->getPosition().y-20));
    
    UITextArea *label2=(UITextArea*)example_root->getChildByTag(42);
    int number=(108-hero.type)/10+20;
    int number1=hero.type/10+20;
    sprintf(str,"绰号:%s 生命加成%d％  英雄+2激活\n星座:%s 攻击加成%d％  英雄+5激活",hero.exname.c_str(),number,hero.starname.c_str(),number1);
    label2->setText(str);
    label2->setColor(ccYELLOW);
    label2->setTextAreaSize(CCSize(540,400));
    label2->setFontSize(32);
    label2->setPosition(ccp(winSize.width/2,700));
    
   UITextArea *label3=(UITextArea*)example_root->getChildByTag(43);
    label3->setFontSize(32);
    label3->setTextAreaSize(CCSize(540,800));
    label3->setText(hero.des.c_str());
    label3->setColor(ccYELLOW);
    label3->setPosition(ccp(winSize.width/2,200));
    
//    UIButton * btn= UIButton::create();
//    btn->setTouchEnable(true);
//    btn->addReleaseEvent(this, coco_releaseselector(HeroInfoLayer::close));
//    btn->setTextures("close1.png","close2.png","close2.png");
//    btn->setPosition(ccp(winSize.width-60, winSize.height/2+300));
//    m_pUiLayer->addWidget(btn);
    
    CCMenuItemImage* pHome = CCMenuItemImage::create("close1.png", "close2.png", this, menu_selector(HeroInfoLayer::close));
    CCMenu *menu=CCMenu::create(pHome,NULL);
    menu->setPosition(ccp(winSize.width-60,winSize.height/2+300));
    addChild(menu,2);

    return true;
}
void HeroInfoLayer::menuPauseCallback(CCObject *sender)
{

}
void HeroInfoLayer::close(CCObject *sender)
{
    removeFromParentAndCleanup(true);
}
void HeroInfoLayer::setData(HeroType hero)
{
    string name=hero.name;
    
}
void HeroInfoLayer::updateText(int tag)
{
    
}