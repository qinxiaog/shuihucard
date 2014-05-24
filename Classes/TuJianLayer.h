//
//  TuJianLayer.h
//  kapai
//
//  Created by qin on 13-12-21.
//
//

#ifndef __kapai__TuJianLayer__
#define __kapai__TuJianLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h>
using namespace CSJson;
using namespace cocos2d;
using namespace extension;
using namespace std;
class TuJianLayer : public CCLayer
{
    public :
	TuJianLayer();
	bool init();
	~TuJianLayer();
    void ReadJson();
public:
    UIWidget* example_root;
    UIScrollView* scrollView;
    void menuPauseCallback(CCObject *sender);
    void getHeroInfo(CCObject *sender);
    UILayer *m_pUiLayer;
    void close();
};

#endif /* defined(__kapai__TuJianLayer__) */
