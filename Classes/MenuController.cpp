//
//  MenuController.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "MenuController.h"
#include "ImageButton.h"
#include "StartScene.h"
#include "Message.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "C2DXShareSDK.h"

using namespace cn::sharesdk;

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, CCDictionary *shareInfo, CCDictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            CCLog("分享成功");
            break;
        case C2DXResponseStateFail:
            CCLog("分享失败");
            break;
        default:
            break;
    }
}

#endif

bool MenuController::init(){
    
    if (! CCLayer::init()) {
        return false;
    }
    
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("AllSprites.png");
    this->addChild(batch);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("AllSprites.plist");
    
    CCSprite* background = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("menubar.png"));
    background->setAnchorPoint(ccp(0, 0));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    CCSprite* back = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("back.png"));
    ImageButton* backButton = ImageButton::create(back, this, menu_selector(MenuController::onBack));
    backButton->setPosition(ccp(128, 48));
    
    CCSprite* regret = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("regret.png"));
    ImageButton* regretButton = ImageButton::create(regret, this, menu_selector(MenuController::onRegret));
    regretButton->setPosition(ccp(320, 48));
    
    CCSprite* plus = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("plus.png"));
    ImageButton* plusButton = ImageButton::create(plus, this, menu_selector(MenuController::onShare));
    plusButton->setPosition(ccp(512, 48));
    
    CCMenu* menu = CCMenu::create(backButton, regretButton, plusButton, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    return true;
}

void MenuController::onBack(CCObject* o){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
    StartScene* ss = StartScene::create();
    CCTransitionSlideInL* slide = CCTransitionSlideInL::create(0.3f, ss);
    CCDirector::sharedDirector()->replaceScene(slide);
}

void MenuController::onRegret(cocos2d::CCObject *o){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_REGRET_MSG);
}

void MenuController::onShare(cocos2d::CCObject *o){
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
       CCDictionary *content = CCDictionary::create();
    content -> setObject(CCString::create("这是一条测试内容"), "content");
    content -> setObject(CCString::create("http://img0.bdstatic.com/img/image/308342ac65c10385343da168d569113b07ecb8088ef.jpg"), "image");
    content -> setObject(CCString::create("测试标题"), "title");
    content -> setObject(CCString::create("测试描述"), "description");
    content -> setObject(CCString::create("http://sharesdk.cn"), "url");
    content -> setObject(CCString::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(CCString::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(CCString::create("ShareSDK"), "site");
    content -> setObject(CCString::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(CCString::create("extInfo"), "extInfo");
    
    C2DXShareSDK::showShareMenu(NULL, content, CCPointMake(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
#endif
}

