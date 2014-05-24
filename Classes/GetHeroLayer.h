//
//  GetHeroLayer.h
//  kapai
//
//  Created by qin on 14-3-25.
//
//

#ifndef __kapai__GetHeroLayer__
#define __kapai__GetHeroLayer__

#include <iostream>
#include "cocos-ext.h"
#include <stdio.h>
#include "Config.h"
using namespace std;
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class GetHeroLayer : public CCLayer
{
    public :
	GetHeroLayer();
	bool init(HeroType hero);
	~GetHeroLayer();
    void menuCallback(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void close(CCObject *sender);
};
#endif /* defined(__kapai__GetHeroLayer__) */
