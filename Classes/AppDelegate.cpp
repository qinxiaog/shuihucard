#include "AppDelegate.h"
#include "LoginScene.h"
#include "BattleScene.h"
#include "SceneGame.h"
#include "LoginScene.h"
USING_NS_CC;
//www.9miao.com
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    float x=screenSize.height/screenSize.width;
    CCSize designSize=CCSizeMake(640,640*x);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    bool bfirst=CCUserDefault::sharedUserDefault()->getBoolForKey("first",false);
    if(!bfirst)
    {
    CCUserDefault::sharedUserDefault()->setBoolForKey("first",true);
    CCUserDefault::sharedUserDefault()->flush();
    CCScene *pScene=LoginScene::scene();
    // run
    pDirector->runWithScene(pScene);
    }
    else
    {
        CCScene *pScene = new SceneGame(0);
        pDirector->runWithScene(pScene);
    }
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
