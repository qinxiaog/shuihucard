//
//  BaoWuLayer.h
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#ifndef __kapai__BaoWuLayer__
#define __kapai__BaoWuLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;
class BaoWuLayer : public CCLayer
{
    public :
	BaoWuLayer();
	bool init();
	~BaoWuLayer();
    void ReadJson();
public:
    UIWidget* example_root;
    void menuPauseCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
};

#endif /* defined(__kapai__BaoWuLayer__) */
