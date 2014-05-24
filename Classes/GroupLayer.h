//
//  GroupLayer.h
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#ifndef __kapai__GroupLayer__
#define __kapai__GroupLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameData.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class GroupLayer : public CCLayer
{
    public :
	GroupLayer();
	bool init();
	~GroupLayer();
    void menuPauseCallback(CCObject *sender);
    void close();
    int selectIndex;
    void addHero(CCObject *sender);
    void changeHero(CCObject *sender);
    void onExit();
public:
    UIWidget* example_root;
    CCRect transRect;
    void draw();
    UILayer *m_pUiLayer;
    //CCControlButton *selectButton;
    UIButton *selectButton;
    CCPoint oldPositon;
    virtual void  registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
};

#endif /* defined(__kapai__GroupLayer__) */
