//
//  ImageButton.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "ImageButton.h"

void ImageButton::onEnter(){
    CCMenuItemSprite::onEnter();
    this->setScale(0.05);
    CCActionInterval* s = CCScaleTo::create(0.3f, 1.0f);
    this->runAction(s);
}

void ImageButton::onExit(){
    CCMenuItemSprite::onExit();
    CCActionInterval* s = CCScaleTo::create(0.3f, 0.05f);
    this->runAction(s);
}

ImageButton* ImageButton::create(CCNode *sprite, cocos2d::CCObject *target, SEL_MenuHandler selector){
    ImageButton* pRet = new ImageButton();
    
    if (pRet && pRet->initWithNormalSprite(sprite, sprite, sprite, target, selector))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}