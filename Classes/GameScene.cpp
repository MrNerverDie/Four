//
//  GameScene.cpp
//  Four
//
//  Created by 王选易 on 14-4-25.
//
//

#include "GameScene.h"
#include "ChessboardController.h"
#include "MenuController.h"

bool GameScene::init(){
    CCScene::init();
    
    CCLayer* cc = ChessboardController::create();
    this->addChild(cc);
    CCLayer* mc = MenuController::create();
    this->addChild(mc);
    
    return true;
}