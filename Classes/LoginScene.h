//
//  LoginScene.h
//  LhTestGame
//
//  Created by lh on 13-10-24.
//
//

#ifndef __LhTestGame__LoginScene__
#define __LhTestGame__LoginScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
using namespace extension;
using namespace CSJson;
class LoginScene:public CCLayer{
public:
    bool init();
    static CCScene * scene();
    CREATE_FUNC(LoginScene);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
private:
	CCArray* m_storyMsgList;
    CSJson::Value root;
	int m_iCurMsgIndex;
    void readJson();
	void showNextMsg();
    void SaveZhuangBei();
    void SaveKaPai();
};
#endif /* defined(__LhTestGame__LoginScene__) */
