//
//  Effect.cpp
//  MoonWarriorsx
//
//

#include "Effect.h"
#include <string>
#include <cmath>
USING_NS_CC;
using namespace std;
const float PAI = 3.141592f;
Effect::Effect()
{
}

Effect::~Effect()
{
}

Effect* Effect::create()
{
    Effect* effect = new Effect();
    if (effect) {
        effect->autorelease();
        return effect;
    }else{
        delete effect;
        effect = NULL;
        return NULL;
    }
}
void Effect::init(int type)
{
    effectid=type;
    switch (type)
    {
        case 1:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect1.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1000.png";
            effectName="effect1";
            char str[64] = {0};
            for (int i = 0; i <6; ++i)
            {
                sprintf(str, "100%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 2:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect2.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="2000.png";
            effectName="effect2";
            char str[64] = {0};
            for (int i = 0; i <2; ++i)
            {
                sprintf(str, "200%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 3:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect3.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="3000.png";
            effectName="effect3";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str, "300%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 4:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect4.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="4000.png";
            effectName="effect4";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str, "400%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 5:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect5.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="5000.png";
            effectName="effect5";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str,"500%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 6:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect6.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="6000.png";
            effectName="effect6";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str,"600%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 7:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect7.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="7000.png";
            effectName="effect7";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str,"700%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 8:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect8.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="8000.png";
            effectName="effect8";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str,"800%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 9:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect9.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="9000.png";
            effectName="effect9";
            char str[64] = {0};
            for (int i = 0; i <9; ++i)
            {
                sprintf(str,"900%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 10:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect10.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="10000.png";
            effectName="effect10";
            char str[64] = {0};
            for (int i = 0; i <10; ++i)
            {
                sprintf(str,"1000%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 11:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect11.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1100.png";
            effectName="effect11";
            char str[64] = {0};
            for (int i = 0; i <9; ++i)
            {
                sprintf(str,"110%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 12:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect12.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1200.png";
            effectName="effect12";
            char str[64] = {0};
            for (int i = 0; i <4; ++i)
            {
                sprintf(str,"120%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 13:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect13.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1300.png";
            effectName="effect13";
            char str[64] = {0};
            for (int i = 0; i <1; ++i)
            {
                sprintf(str,"130%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 14:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect14.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1400.png";
            effectName="effect14";
            char str[64] = {0};
            for (int i = 0; i <6; ++i)
            {
                sprintf(str,"140%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 15:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect15.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1500.png";
            effectName="effect15";
            char str[64] = {0};
            for (int i = 0; i <7; ++i)
            {
                sprintf(str,"150%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 16:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect16.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1600.png";
            effectName="effect16";
            char str[64] = {0};
            for (int i = 0; i <9; ++i)
            {
                sprintf(str,"160%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        case 17:
        {
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect17.plist");
            CCArray *animFrames = CCArray::create();
            firtPngName="1700.png";
            effectName="effect17";
            char str[64] = {0};
            for (int i = 0; i <8; ++i)
            {
                sprintf(str,"170%d.png", i);
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
            // 帧动画命名
            CCAnimationCache::sharedAnimationCache()->addAnimation(animation,effectName.c_str());
            break;
        }
        default:
            break;
    }

}
void Effect::flareEffect(CCNode *parent, CCCallFunc *callback)
{


}

void Effect::explode(CCNode *parent,CCPoint from, CCPoint pos)
{
    pt=pos;
    // 第一帧
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(firtPngName.c_str());
    CCSprite *explosion = CCSprite::createWithSpriteFrame(pFrame);
    parent->addChild(explosion);
    if(effectid==1||effectid==10||effectid==11||effectid==12||effectid==14||effectid==15||effectid==16||effectid==17)
    {
    explosion->setPosition(pos);
        // 完成之后的回调
        CCCallFuncN *removeFunc =  CCCallFuncN::create(explosion, callfuncN_selector(Effect::killSprite));
        // 爆炸动画
        CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName(effectName.c_str());
        explosion->runAction(CCSequence::create(CCAnimate::create(animation),removeFunc, NULL));
    }
    else
    {
       explosion->setPosition(from);
        float angle=CalDirection(from.x, from.y, pos.x, pos.y);
        explosion->setRotation(angle);
        // 完成之后的回调
        CCCallFuncN *removeFunc =  CCCallFuncN::create(explosion, callfuncN_selector(Effect::killSprite));
        CCActionInterval * moveTo = CCMoveTo::create(0.5,pos);
        // 爆炸动画
        CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName(effectName.c_str());
        explosion->runAction(CCSequence::create(CCAnimate::create(animation),moveTo,removeFunc, NULL));
    }    

    
}
float Effect::CalDirection(float xStart,float yStart, float xEnd, float yEnd)
{
	double accDir=0;
	float vecX = xEnd - xStart;
	float vecY = yEnd - yStart;
    
	// ‘⁄X÷·…œ£¨90°„ªÚ270°„
	if(abs(vecX) < 0.00001f)
	{
		if(vecY > 0)
		{
			accDir = 0;
		}
		else if(vecY < 0)
		{
			accDir = PAI;
		}
	}
	else
	{
		// º∆À„º”ÀŸ∑ΩœÚ£®ª°∂»£©
		accDir = atan(vecY / vecX);
        
		if(vecX >=0)
		{
			// µ⁄“ª£¨ÀƒœÛœﬁ
			accDir = PAI*0.5 - accDir;
		}
		else
		{
			// µ⁄∂˛£¨»˝œÛœﬁ
			accDir = PAI*1.5 - accDir;
		}
	}
    
	return (float)(accDir * 180.0f / PAI);
}
void Effect::addFont(CCNode *parent,int hp,CCPoint pt)
{
    CCLabelAtlas* label2 = new CCLabelAtlas();
    label2->initWithString("0123456789", "fonts.png",30,36,'0');
    this->getParent()->addChild(label2, 2, 2);
    label2->setPosition(pt);
    char str[32];
    sprintf(str, "%d",hp);
    label2->setString(str);
    CCActionInterval* fade = CCFadeOut::create(1.0f);
    CCActionInterval* fade2 = CCFadeOut::create(1.0f);
    CCSequence* seq = CCSequence::create(fade,NULL);
    //CCAction* repeat = CCRepeat::create( seq );
    label2->runAction(seq);
    CCSprite *addSprite=new CCSprite();
    addSprite->initWithFile("hurt.png");
    this->getParent()->addChild(addSprite);
    addSprite->setPosition(ccp(pt.x-20,pt.y));
    addSprite->setAnchorPoint(ccp(0,0));
    CCSequence* seq2 = CCSequence::create(fade2,NULL);
    addSprite->runAction(seq2);
    
    addSprite->release();
    label2->release();
}
// 闪光动画
void Effect::spark(CCPoint pos, CCNode *parent, float scale, float duration)
{

}

//动画加入缓存
void Effect::sharedExplosion()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect2.plist");
    CCArray *animFrames = CCArray::create();
    
    char str[64] = {0};
    for (int i = 0; i <12; ++i) {
        sprintf(str, "1300%02d.png", i);
        CCLOG("%s",str);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
    
    // 帧动画命名
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Explosion");
    
}

void Effect::killSprite(CCNode *pSender)
{
    if(pSender)
    pSender->removeFromParentAndCleanup(true);
}

