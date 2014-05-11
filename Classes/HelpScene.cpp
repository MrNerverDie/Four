//
//  HelpScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#include "HelpScene.h"
#include "HelpController.h"


bool HelpScene::init(){
    cocos2d::CCScene::create();
    
    CCLayer* layer = HelpController::create();
    this->addChild(layer);
    
    return true;
}