#include "AppDelegate.h"
#include "HelpScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "AudioManager.h"

#include <string>

USING_NS_CC;
using namespace cn::sharesdk;

AppDelegate::AppDelegate() {
    audio = AudioManager::create();
    CC_SAFE_RETAIN(audio);
}

AppDelegate::~AppDelegate() 
{
    CC_SAFE_RELEASE(audio);
}

bool AppDelegate::applicationDidFinishLaunching() {

    C2DXShareSDK::open(CCString::create("api20"), false); 

    initPlatformConfig();

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

void AppDelegate::initPlatformConfig()
{
    //新浪微博
    CCDictionary *sinaConfigDict = CCDictionary::create();
    sinaConfigDict -> setObject(CCString::create("568898243"), "app_key");
    sinaConfigDict -> setObject(CCString::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
    
    //腾讯微博
    CCDictionary *tcConfigDict = CCDictionary::create();
    tcConfigDict -> setObject(CCString::create("801307650"), "app_key");
    tcConfigDict -> setObject(CCString::create("ae36f4ee3946e1cbb98d6965b0b2ff5c"), "app_secret");
    tcConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTencentWeibo, tcConfigDict);
    
    //短信
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSMS, NULL);
    
    //QQ空间
    CCDictionary *qzConfigDict = CCDictionary::create();
    qzConfigDict -> setObject(CCString::create("100371282"), "app_id");
    qzConfigDict -> setObject(CCString::create("aed9b0303e3ed1e27bae87c33761161d"), "app_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeQZone, qzConfigDict);
    
    //微信
    CCDictionary *wcConfigDict = CCDictionary::create();
    wcConfigDict -> setObject(CCString::create("wx4868b35061f87885"), "app_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiSession, wcConfigDict);
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiTimeline, wcConfigDict);
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiFav, wcConfigDict);
    
    //QQ
    CCDictionary *qqConfigDict = CCDictionary::create();
    qqConfigDict -> setObject(CCString::create("100371282"), "app_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeQQ, qqConfigDict);
    
    //Facebook
    CCDictionary *fbConfigDict = CCDictionary::create();
    fbConfigDict -> setObject(CCString::create("107704292745179"), "api_key");
    fbConfigDict -> setObject(CCString::create("38053202e1a5fe26c80c753071f0b573"), "app_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFacebook, fbConfigDict);
    
    //Twitter
    CCDictionary *twConfigDict = CCDictionary::create();
    twConfigDict -> setObject(CCString::create("mnTGqtXk0TYMXYTN7qUxg"), "consumer_key");
    twConfigDict -> setObject(CCString::create("ROkFqr8c3m1HXqS3rm3TJ0WkAJuwBOSaWhPbZ9Ojuc"), "consumer_secret");
    twConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTwitter, twConfigDict);
    
    //Google+
    CCDictionary *gpConfigDict = CCDictionary::create();
    gpConfigDict -> setObject(CCString::create("232554794995.apps.googleusercontent.com"), "client_id");
    gpConfigDict -> setObject(CCString::create("PEdFgtrMw97aCvf0joQj7EMk"), "client_secret");
    gpConfigDict -> setObject(CCString::create("http://localhost"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeGooglePlus, gpConfigDict);
    
    //人人网
    CCDictionary *rrConfigDict = CCDictionary::create();
    rrConfigDict -> setObject(CCString::create("226427"), "app_id");
    rrConfigDict -> setObject(CCString::create("fc5b8aed373c4c27a05b712acba0f8c3"), "app_key");
    rrConfigDict -> setObject(CCString::create("f29df781abdd4f49beca5a2194676ca4"), "secret_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeRenren, rrConfigDict);
    
    //开心网
    CCDictionary *kxConfigDict = CCDictionary::create();
    kxConfigDict -> setObject(CCString::create("358443394194887cee81ff5890870c7c"), "api_key");
    kxConfigDict -> setObject(CCString::create("da32179d859c016169f66d90b6db2a23"), "secret_key");
    kxConfigDict -> setObject(CCString::create("http://www.sharesdk.cn/"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeKaixin, kxConfigDict);
    
    //邮件
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeMail, NULL);
    
    //打印
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeAirPrint, NULL);
    
    //拷贝
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeCopy, NULL);
    
    //搜狐微博
    CCDictionary *shwbConfigDict = CCDictionary::create();
    shwbConfigDict -> setObject(CCString::create("SAfmTG1blxZY3HztESWx"), "consumer_key");
    shwbConfigDict -> setObject(CCString::create("yfTZf)!rVwh*3dqQuVJVsUL37!F)!yS9S!Orcsij"), "consumer_secret");
    shwbConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "callback_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSohuWeibo, shwbConfigDict);
    
    //网易微博
    CCDictionary *neConfigDict = CCDictionary::create();
    neConfigDict -> setObject(CCString::create("T5EI7BXe13vfyDuy"), "consumer_key");
    neConfigDict -> setObject(CCString::create("gZxwyNOvjFYpxwwlnuizHRRtBRZ2lV1j"), "consumer_secret");
    neConfigDict -> setObject(CCString::create("http://www.shareSDK.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatType163Weibo, neConfigDict);
    
    //豆瓣
    CCDictionary *dbConfigDict = CCDictionary::create();
    dbConfigDict -> setObject(CCString::create("02e2cbe5ca06de5908a863b15e149b0b"), "api_key");
    dbConfigDict -> setObject(CCString::create("9f1e7b4f71304f2f"), "secret");
    dbConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeDouBan, dbConfigDict);
    
    //印象笔记
    CCDictionary *enConfigDict = CCDictionary::create();
    enConfigDict -> setObject(CCString::create("sharesdk-7807"), "consumer_key");
    enConfigDict -> setObject(CCString::create("d05bf86993836004"), "consumer_secret");
    enConfigDict -> setObject(CCString::create("0"), "host_type");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeEvernote, enConfigDict);
    
    //LinkedIn
    CCDictionary *liConfigDict = CCDictionary::create();
    liConfigDict -> setObject(CCString::create("ejo5ibkye3vo"), "api_key");
    liConfigDict -> setObject(CCString::create("cC7B2jpxITqPLZ5M"), "secret_key");
    liConfigDict -> setObject(CCString::create("http://sharesdk.cn"), "redirect_url");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeLinkedIn, liConfigDict);
    
    //Pinterest
    CCDictionary *piConfigDict = CCDictionary::create();
    piConfigDict -> setObject(CCString::create("1432928"), "client_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypePinterest, piConfigDict);
    
    //Pocket
    CCDictionary *poConfigDict = CCDictionary::create();
    poConfigDict -> setObject(CCString::create("11496-de7c8c5eb25b2c9fcdc2b627"), "consumer_key");
    poConfigDict -> setObject(CCString::create("pocketapp1234"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypePocket, poConfigDict);
    
    //Instapaper
    CCDictionary *ipConfigDict = CCDictionary::create();
    ipConfigDict -> setObject(CCString::create("4rDJORmcOcSAZL1YpqGHRI605xUvrLbOhkJ07yO0wWrYrc61FA"), "consumer_key");
    ipConfigDict -> setObject(CCString::create("GNr1GespOQbrm8nvd7rlUsyRQsIo3boIbMguAl9gfpdL0aKZWe"), "consumer_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeInstapaper, ipConfigDict);
    
    //有道云笔记
    CCDictionary *ydConfigDict = CCDictionary::create();
    ydConfigDict -> setObject(CCString::create("dcde25dca105bcc36884ed4534dab940"), "consumer_key");
    ydConfigDict -> setObject(CCString::create("d98217b4020e7f1874263795f44838fe"), "consumer_secret");
    ydConfigDict -> setObject(CCString::create("http://www.sharesdk.cn/"), "oauth_callback");
    ydConfigDict -> setObject(CCString::create("1"), "host_type");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeYouDaoNote, ydConfigDict);
    
    //搜狐随身看
    CCDictionary *shkConfigDict = CCDictionary::create();
    shkConfigDict -> setObject(CCString::create("e16680a815134504b746c86e08a19db0"), "app_key");
    shkConfigDict -> setObject(CCString::create("b8eec53707c3976efc91614dd16ef81c"), "app_secret");
    shkConfigDict -> setObject(CCString::create("http://sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSohuKan, shkConfigDict);
    
    //Flickr
    CCDictionary *flickrConfigDict = CCDictionary::create();
    flickrConfigDict -> setObject(CCString::create("33d833ee6b6fca49943363282dd313dd"), "api_key");
    flickrConfigDict -> setObject(CCString::create("3a2c5b42a8fbb8bb"), "api_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFlickr, flickrConfigDict);
    
    //Tumblr
    CCDictionary *tumblrConfigDict = CCDictionary::create();
    tumblrConfigDict -> setObject(CCString::create("2QUXqO9fcgGdtGG1FcvML6ZunIQzAEL8xY6hIaxdJnDti2DYwM"), "consumer_key");
    tumblrConfigDict -> setObject(CCString::create("3Rt0sPFj7u2g39mEVB3IBpOzKnM3JnTtxX2bao2JKk4VV1gtNo"), "consumer_secret");
    tumblrConfigDict -> setObject(CCString::create("http://sharesdk.cn"), "callback_url");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTumblr, tumblrConfigDict);
    
    //Dropbox
    CCDictionary *dropboxConfigDict = CCDictionary::create();
    dropboxConfigDict -> setObject(CCString::create("7janx53ilz11gbs"), "app_key");
    dropboxConfigDict -> setObject(CCString::create("c1hpx5fz6tzkm32"), "app_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeDropbox, dropboxConfigDict);
    
    //Instagram
    CCDictionary *instagramConfigDict = CCDictionary::create();
    instagramConfigDict -> setObject(CCString::create("ff68e3216b4f4f989121aa1c2962d058"), "client_id");
    instagramConfigDict -> setObject(CCString::create("1b2e82f110264869b3505c3fe34e31a1"), "client_secret");
    instagramConfigDict -> setObject(CCString::create("http://sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeInstagram, instagramConfigDict);
    
    //VK
    CCDictionary *vkConfigDict = CCDictionary::create();
    vkConfigDict -> setObject(CCString::create("3921561"), "application_id");
    vkConfigDict -> setObject(CCString::create("6Qf883ukLDyz4OBepYF1"), "secret_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeVKontakte, vkConfigDict);
}
