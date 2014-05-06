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
    ImageButton* regretButton = ImageButton::create(regret, NULL, NULL);
    regretButton->setPosition(ccp(320, 48));
    
    CCSprite* plus = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("plus.png"));
    ImageButton* plusButton = ImageButton::create(plus, NULL, NULL);
    plusButton->setPosition(ccp(512, 48));
    
    CCMenu* menu = CCMenu::create(backButton, regretButton, plusButton, NULL);
    menu->setPosition(ccp(0, 0));
    this->addChild(menu);
    
    return true;
}

void MenuController::onBack(CCObject* o){
    StartScene* ss = StartScene::create();
    CCTransitionSlideInL* slide = CCTransitionSlideInL::create(0.3f, ss);
    CCDirector::sharedDirector()->replaceScene(slide);
}