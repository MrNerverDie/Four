//
//  FixTimeAIChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-5-9.
//
//

#include "FixTimeAIChessboardController.h"
#include "TimeBoard.h"

bool FixTimeAIChessboardController::init(){
    AIChessboardController::init();
    
    CCLabelTTF* label = TimeBoard::create();
    this->addChild(label);
    
    modeLabel->setString("固定时间");
    
    return true;
}