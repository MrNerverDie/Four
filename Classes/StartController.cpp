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

bool StartController::init(){
    CCLayer::init();
    
    // load res
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("AllSprites.png");
    this->addChild(batch);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("AllSprites.plist");
    
    CCSprite* background = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("background.png"));
    background->setAnchorPoint(ccp(0, 0));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    CCSprite* h2h = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("black.png"));
    ImageButton* h2hButton = ImageButton::create(h2h, this, menu_selector(StartController::onH2H));
    h2hButton->setPosition(LogicToReal(ccp(1, 2)));
    
    CCSprite* h2c = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("white.png"));
    ImageButton* h2cButton = ImageButton::create(h2c, this, menu_selector(StartController::onH2C));
    h2cButton->setPosition(LogicToReal(ccp(2, 2)));
    
    CCMenu* menu = CCMenu::create(h2hButton, h2cButton, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    return true;
}

void StartController::onH2H(){
    GameScene* gs = GameScene::create();
    CCDirector::sharedDirector()->pushScene(gs);
}

void StartController::onH2C(){

}