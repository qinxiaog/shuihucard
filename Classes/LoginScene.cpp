//
//  LoginScene.cpp
//  LhTestGame
//www.9miao.com
//  Created by lh on 13-10-24.
//
//

#include "LoginScene.h"
#include "GameData.h"
#include "SceneGame.h"
#define TAG_CHAT_BG 1
CCScene * LoginScene::scene(){
    CCScene * m_scene=CCScene::create();
    CCLayer * m_layer=LoginScene::create();
    m_scene->addChild(m_layer);
    return m_scene;
}

bool LoginScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    m_iCurMsgIndex=0;
    setTouchEnabled(true);
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    /* 背景 */
    CCSprite* bgSp = CCSprite::create("storybg.png");
    bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    bgSp->setScaleX(winSize.width/640);
    bgSp->setScaleY(winSize.height/960);
    this->addChild(bgSp,0,0);
    
    /* 对话框 */
    CCSprite* chatBg = CCSprite::create("chatbg.png");
    chatBg->setPosition(ccp(winSize.width/2, chatBg->getContentSize().height / 2));
    this->addChild(chatBg,1,TAG_CHAT_BG);
    readJson();
    showNextMsg();
   
    return true;
    
}
void LoginScene::readJson()
{
    CCLOG("login :readjson");
    CSJson::Reader reader;
    unsigned  long nSize = 0;
    string path =CCFileUtils::sharedFileUtils()->fullPathForFilename("story.json");
    char* json_document=(char*)CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb",&nSize);
    reader.parse(json_document, root);
}
void LoginScene::showNextMsg()
{
    
    Value datas;
    datas=root["datas"];
    int size = datas.size();
	if(m_iCurMsgIndex > size) {
		return;
	}
	if(m_iCurMsgIndex == size)
    {
        string path=CCFileUtils::sharedFileUtils()->getWritablePath();
        path.append("myhero.json");//保存战斗英雄
            CSJson::Value root;
            CSJson::Value person;
            
            person["level"] = 1;//等级
            person["exlevel"] = 0;//品介
            person["type"] = 3;//类型
            person["xp"] = 0;//经验
            person["pos"]=1;//位置
            person["index"]=0;//卡牌索引
            person["zhuang0"]=300000;//头盔
            person["zhuang1"]=400000;//盔甲
            person["zhuang2"]=500000;//武器
            person["zhuang3"]=600000;//宝物
            person["zhuang4"]=700000;//鞋子
            person["zhuang5"]=800000;//坐骑
            root.append(person);
        person["level"] = 1;
        person["exlevel"] = 0;//品介
        person["type"] =108;
        person["xp"] = 0;
        person["pos"]=2;
        person["index"]=1;
        person["zhuang0"]=300000;
        person["zhuang1"]=400000;
        person["zhuang2"]=500000;
        person["zhuang3"]=600000;
        person["zhuang4"]=700000;
        person["zhuang5"]=800000;
        root.append(person);

            CSJson::FastWriter fw ;
            std::string json_file = fw.write(root);
            //创建一个文件指针
            //路径、模式
            FILE* file = fopen(path.c_str(), "wb");
            if (file)
            {
                fputs(json_file.c_str(),file);
                fclose(file);
            }
        SaveZhuangBei();//保存装备
        //SaveKaPai();//保存卡牌
        CCScene *pScene = new SceneGame(0);
        CCDirector::sharedDirector()->replaceScene(pScene);
		//SceneManager::sharedSceneManager()->changeScene(SceneManager::en_TollgateScene, true);
		return;
	}    
        string name = datas[m_iCurMsgIndex]["name"].asString();
        string msg= datas[m_iCurMsgIndex]["msg"].asString();
        string strpic=datas[m_iCurMsgIndex]["picture"].asString();

	CCSprite* chatBG = (CCSprite*)this->getChildByTag(TAG_CHAT_BG);
	chatBG->removeAllChildrenWithCleanup(true);
	CCSize bgSize = chatBG->getContentSize();
    
	/* 对话信息 */
	//StoryMsg* storyMsg = (StoryMsg*)m_storyMsgList->objectAtIndex(m_iCurMsgIndex);
    
	/* 人物名字 */
	CCLabelTTF* nameLab = CCLabelTTF::create(name.c_str(),"Arial", 32);
	nameLab->setPosition(ccp(bgSize.width * 0.2f, bgSize.height * 0.9f));
    nameLab->setColor(ccRED);
	chatBG->addChild(nameLab,1);
    
	/* 对话内容 */
	CCLabelTTF* msgLab = CCLabelTTF::create(msg.c_str(),"Arial", 32,CCSize(300,0), kCCTextAlignmentLeft);
	msgLab->setPosition(ccp(bgSize.width/2-120, bgSize.height * 0.4f));
    msgLab->setColor(ccBLUE);
	//msgLab->setDimensions(CCSizeMake(bgSize.width * 0.55f, 0));
	//msgLab->setAnchorPoint(ccp(0, 0.5f));
	chatBG->addChild(msgLab,1);
    
	/* 人物图片 */
	CCSprite* actorSp = CCSprite::create(strpic.c_str());
	CCSize actorSize = actorSp->getContentSize();
	actorSp->setPosition(ccp(bgSize.width - actorSize.width / 2, actorSize.height / 2));
	chatBG->addChild(actorSp,1);
    
	m_iCurMsgIndex++;
}
void LoginScene::SaveZhuangBei()
{
    string path=CCFileUtils::sharedFileUtils()->getWritablePath();
    path.append("myzhuangbei.json");
    CSJson::Value root;
    CSJson::Value person;

    person["level"] = 1;//等级
    person["exlevel"] = 0;//品介
    person["type"] =301;//类型
    person["index"]=0;//卡牌索引
    person["user"] =-1;//哪个英雄装备
    root.append(person);
    
    person["level"] = 1;
    person["exlevel"] = 0;//品介
    person["type"] =401;
    person["index"]=1;
    person["user"] =-1;//哪个英雄装备
    root.append(person);
    
    person["level"] = 1;
    person["exlevel"] = 0;//品介
    person["type"] =501;//公孙胜武器七星剑
    person["index"]=2;
    person["user"] =-1;//哪个英雄装备
    root.append(person);
    
    person["level"] =1;
    person["exlevel"] = 0;//品介
    person["type"] =601;
    person["index"]=3;
    person["user"] =-1;//哪个英雄装备
    root.append(person);
    
    person["level"] = 1;
    person["exlevel"] = 0;//品介
    person["type"] =701;
    person["index"]=4;
    person["user"] =-1;//哪个英雄装备
    root.append(person);
    
    CSJson::FastWriter fw ;
    std::string json_file = fw.write(root);
    //创建一个文件指针
    //路径、模式
    FILE* file = fopen(path.c_str(), "wb");
    if (file)
    {
        fputs(json_file.c_str(),file);
        fclose(file);
    }
}
void LoginScene::SaveKaPai()
{
        string path=CCFileUtils::sharedFileUtils()->getWritablePath();
        path.append("mykapai.json");
        CSJson::Value root;
        CSJson::Value person;
    person["level"] = 1;
    person["exlevel"] = 0;//品介
    person["type"] = 2;
    person["xp"] = 0;
    person["pos"]=0;
    person["index"]=2;
    person["zhuang0"]=303000;
    person["zhuang1"]=401000;
    person["zhuang2"]=501000;
    person["zhuang3"]=603000;
    person["zhuang4"]=701000;
    person["zhuang5"]=802000;
    root.append(person);
    
    CSJson::FastWriter fw ;
    std::string json_file = fw.write(root);
    //创建一个文件指针
    //路径、模式
    FILE* file = fopen(path.c_str(), "wb");
    if (file)
    {
        fputs(json_file.c_str(),file);
        fclose(file);
    }
}
void LoginScene::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-127-1, false);
    CCLayer::registerWithTouchDispatcher();
}
bool LoginScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void LoginScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}
void LoginScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    showNextMsg();
}
