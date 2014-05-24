//
//  JiangLiLayer.h
//  kapai
//
//  Created by qin on 14-1-12.
//
//

#ifndef __kapai__JiangLiLayer__
#define __kapai__JiangLiLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HeroLayer.h"
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
class JiangLiLayer : public CCLayer
{
    public :
	JiangLiLayer();
	bool init();
	~JiangLiLayer();
public:
    void menuCallback(CCObject *sender);
    void menuPauseCallback(CCObject *sender);
    void close(CCObject *sender);
};


#endif /* defined(__kapai__JiangLiLayer__) */
