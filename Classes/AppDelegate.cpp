#include "AppDelegate.h"
#include "HelpScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "AudioManager.h"

#include <string>

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "C2DXShareSDK.h"

using namespace cn::sharesdk;

#endif

AppDelegate::AppDelegate() {
    audio = AudioManager::create();
    CC_SAFE_RETAIN(audio);
}

AppDelegate::~AppDelegate() 
{
    CC_SAFE_RELEASE(audio);
}

bool AppDelegate::applicationDidFinishLaunching() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    C2DXShareSDK::open(CCString::create("api20"), false); 
#endif

    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    
    pDirector->setOpenGLView(pEGLView);

    pEGLView->setDesignResolutionSize(640, 1136, kResolutionShowAll);

    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    CCDictionary* config = CCDictionary::create();
    
    CCScene* pScene = nullptr;
    
    std::string config_path = CCFileUtils::sharedFileUtils()->getWritablePath() + "Config.plist";
    
    bool firstTime = !CCFileUtils::sharedFileUtils()->isFileExist(config_path);
    
    if (firstTime) {
        pScene = HelpScene::create();
        config->setObject(CCString::create("0"), "FirstTime");
        CCAssert(config->writeToFile(config_path.c_str()), "not passes");
    }else{
        pScene = StartScene::create();
    }
    
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