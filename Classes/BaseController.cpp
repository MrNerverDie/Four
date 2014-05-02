//
//  BaseController.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "BaseController.h"

bool BaseController::init(){
    if (! CCLayer::init()) {
        return false;
    }
    
    // load res
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("AllSprites.png");
    this->addChild(batch);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("AllSprites.plist");
    
    // add background
    CCSprite* background = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("background.png"));
    background->setAnchorPoint(ccp(0, 0));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    return true;
}