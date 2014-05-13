//
//  FixMoveAIChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-5-9.
//
//

#include "FixMoveAIChessboardController.h"
#include "MoveBoard.h"

bool FixMoveAIChessboardController::init(){
    AIChessboardController::init();
    
    CCLabelTTF* label = MoveBoard::create();
    this->addChild(label);
    
    modeLabel->setString("固定步数");
    
    return true;
}