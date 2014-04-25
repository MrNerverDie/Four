//
//  GameScene.cpp
//  Four
//
//  Created by 王选易 on 14-4-25.
//
//

#include "GameScene.h"
#include "ChessboardController.h"

bool GameScene::init(){
    CCScene::init();
    
    cocos2d::CCLayer* cc = ChessboardController::create();
    this->addChild(cc);
    
    return true;
}