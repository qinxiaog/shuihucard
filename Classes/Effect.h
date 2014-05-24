//
//  Effect.h
//  MoonWarriorsx
//
//  Created by 王 磊 on 12-12-29.
//
//

#ifndef __MoonWarriorsx__Effect__
#define __MoonWarriorsx__Effect__

#include "cocos2d.h"
#include <string>
using namespace std;
USING_NS_CC;

class Effect : public cocos2d::CCNode
{
    
private:
    CCSprite *m_sprite;
    
public:
    Effect(void);
    ~Effect(void);
    int effectid;
    void init(int type);
    string firtPngName;
    string effectName;
    CCPoint pt;
    // flare effect
    void flareEffect(CCNode* parent, CCCallFunc* callback);
    float CalDirection(float xStart,float yStart, float xEnd, float yEnd);
    void explode(CCNode *parent,CCPoint from,CCPoint pos);
    void spark(CCPoint pos, CCNode *parent, float scale, float duration);
    
    void killSprite(CCNode *pSender);
    void addFont(CCNode *parent,int hp,CCPoint pt);

    
    
    static void sharedExplosion();
    static Effect* create();
    
};
#endif /* defined(__MoonWarriorsx__Effect__) */
