//
//  AIGameScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIGameScene.h"
#include "AIChessboardController.h"
#include "MenuController.h"

bool AIGameScene::init(){
    CCScene::init();
    
    CCLayer* cc = AIChessboardController::create();
    this->addChild(cc);
    CCLayer* mc = MenuController::create();
    this->addChild(mc);
    
    return true;
}