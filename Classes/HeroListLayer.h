//
//  HeroListLayer.h
//  kapai
//
//  Created by qin on 13-12-20.
//
//

#ifndef __kapai__HeroListLayer__
#define __kapai__HeroListLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HeroLayer.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class HeroListLayer : public CCLayer
{
    public :
	HeroListLayer();
	bool init(HeroType hero,int type);
	~HeroListLayer();
    HeroType m_oldHero;
public:
    void menuCallback(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void menuAddhero(CCObject *sender);
    void close();
    int mindex;
    void Heroupdate();
    void getHeros();
};

#endif /* defined(__kapai__HeroListLayer__) */
