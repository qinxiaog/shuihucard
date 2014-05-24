//
//  HuoDongLayer.h
//  kapai
//
//  Created by qin on 13-12-19.
//
//

#ifndef __kapai__HuoDongLayer__
#define __kapai__HuoDongLayer__

#include <iostream>

#endif /* defined(__kapai__HuoDongLayer__) */
#include "cocos-ext.h"
#include "Config.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class HuoDongLayer : public CCLayer
{
    public :
	HuoDongLayer();
	bool init(HeroType hero,int type);
	~HuoDongLayer();
    HeroType m_oldHero;
public:
    void menuCallback(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void close();
    int mindex;
    void Heroupdate();
};