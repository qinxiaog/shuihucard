//
//  shop.h
//  LhTestGame
//
//  Created by lh on 13-10-25.
//
//

#ifndef __LhTestGame__shop__
#define __LhTestGame__shop__

#include <iostream>
#include "cocos-ext.h"
#include <stdio.h>
#include "Config.h"
#include "GetHeroLayer.h"
using namespace std;
using namespace CSJson;
using namespace cocos2d;
class shopLayer : public CCLayer
{
    public :
	shopLayer();
	bool init();
	~shopLayer();
    void menuCallback(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void close(CCObject *sender);
    void Store(CCObject *sender);
    CCLabelTTF *moneylabel;
    void buy(CCObject *sender);
};
#endif /* defined(__LhTestGame__shop__) */
