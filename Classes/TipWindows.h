//
//  TipWindows.h
//  kapai
//
//  Created by qin on 14-1-12.
//
//

#ifndef __kapai__TipWindows__
#define __kapai__TipWindows__

#include "cocos2d.h"
#include <stdio.h>
using namespace cocos2d;
using namespace std;
class TipWindows:public CCLayer
{
public:
    CCLabelTTF* scorelabel;
    CCLabelTTF* totallabel;
public:
    TipWindows(string str);
    ~TipWindows();
    CCLabelTTF *tipLabel;
    bool init(string str);
    int fontsize;
    int h;
    bool m_sucess;
    void nextCallback(CCObject *sender);
    void back(CCObject *sender);
};

#endif /* defined(__kapai__TipWindows__) */
