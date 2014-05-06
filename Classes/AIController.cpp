//
//  AIController.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIController.h"

bool AIController::init(){
    return true;
}

void AIController::getNextMove(const ChessboardData &pieces, Move &nextMove){
    nextMove.src = ccp(0, 3);
    nextMove.dest = ccp(0, 2);
}