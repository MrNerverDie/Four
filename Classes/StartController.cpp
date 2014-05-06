//
//  StartController.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "StartController.h"
#include "ImageButton.h"
#include "ChessboardProtocol.h"
#include "GameScene.h"
#include "AIGameScene.h"
#include "Message.h"

bool StartController::init(){
    if (! BaseController::init()) {
        return false;
    }
    
    
    // load res
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
    CCSprite* four_logo = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("four_logo.png"));
    four_logo->setPosition(ccp(320, 960));
    this->addChild(four_logo);

    CCSprite* h2h = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("h2h.png"));
    ImageButton* h2hButton = ImageButton::create(h2h, this, menu_selector(StartController::onH2H));
    h2hButton->setPosition(LogicToReal(ccp(1, 2)));
    
    CCSprite* h2c = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("h2c.png"));
    ImageButton* h2cButton = ImageButton::create(h2c, this, menu_selector(StartController::onH2C));
    h2cButton->setPosition(LogicToReal(ccp(2, 2)));
    
    CCSprite* help = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("help.png"));
    ImageButton* helpButton = ImageButton::create(help, this, menu_selector(StartController::onHelp));
    helpButton->setPosition(LogicToReal(ccp(1, 1)));
    
    CCSprite* exit = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("exit.png"));
    ImageButton* exitButton = ImageButton::create(exit, this, menu_selector(StartController::onEnd));
    exitButton->setPosition(LogicToReal(ccp(2, 1)));
    
    CCMenu* menu = CCMenu::create(h2hButton, h2cButton, helpButton, exitButton, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    return true;
}

void StartController::onH2H(CCObject* o){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
    CCScene* gs = GameScene::create();
    CCTransitionSlideInR* slide = CCTransitionSlideInR::create(0.3, gs);
    CCDirector::sharedDirector()->replaceScene(slide);
}

void StartController::onH2C(CCObject* o){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
    CCScene* gs = AIGameScene::create();
    CCTransitionSlideInR* slide = CCTransitionSlideInR::create(0.3, gs);
    CCDirector::sharedDirector()->replaceScene(slide);
}

void StartController::onHelp(CCObject* o){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
}

void StartController::onEnd(CCObject* o){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
    CCDirector::sharedDirector()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

