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
#include "FixTimeAIGameScene.h"
#include "FixMoveAIGameScene.h"
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
    
    CCSprite* fixTime = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("help.png"));
    ImageButton* fixTimeButton = ImageButton::create(fixTime, this, menu_selector(StartController::onFixTime));
    fixTimeButton->setPosition(LogicToReal(ccp(1, 1)));
    
    CCSprite* fixMove = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("exit.png"));
    ImageButton* fixMoveButton = ImageButton::create(fixMove, this, menu_selector(StartController::onFixMove));
    fixMoveButton->setPosition(LogicToReal(ccp(2, 1)));
    
    CCMenu* menu = CCMenu::create(h2hButton, h2cButton, fixTimeButton, fixMoveButton, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    return true;
}

void transfer2NextScene(CCScene* scene){
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CLICK_MSG);
    CCTransitionSlideInR* slide = CCTransitionSlideInR::create(0.3, scene);
    CCDirector::sharedDirector()->replaceScene(slide);
}

void StartController::onH2H(CCObject* o){
    CCScene* gs = GameScene::create();
    transfer2NextScene(gs);
}

void StartController::onH2C(CCObject* o){
    CCScene* gs = AIGameScene::create();
    transfer2NextScene(gs);
}

void StartController::onFixTime(CCObject* o){
    CCScene* gs = FixTimeAIGameScene::create();
    transfer2NextScene(gs);
}

void StartController::onFixMove(CCObject* o){
    CCScene* gs = FixMoveAIGameScene::create();
    transfer2NextScene(gs);
}

