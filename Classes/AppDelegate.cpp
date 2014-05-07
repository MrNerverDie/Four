#include "AppDelegate.h"
#include "GameScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "AudioManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    audio = AudioManager::create();
    CC_SAFE_RETAIN(audio);
}

AppDelegate::~AppDelegate() 
{
    CC_SAFE_RELEASE(audio);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    
    pDirector->setOpenGLView(pEGLView);

    pEGLView->setDesignResolutionSize(640, 1136, kResolutionShowAll);

    
    // turn on display FPS
//    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = StartScene::create();
//    CCScene* pScene = HelloWorld::scene();

    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    audio->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    audio->resume();
}
