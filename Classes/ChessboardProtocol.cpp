//
//  ChessboardProtocol.cpp
//  Four
//
//  Created by 王选易 on 14-4-26.
//
//

#include "ChessboardProtocol.h"


CCPoint LogicToReal(const cocos2d::CCPoint& p){
    return ccp(X_OFFSET + p.x * PIECE_WIDTH, Y_OFFSET + p.y * PIECE_HEIGHT);
}

CCPoint RealToLogic(const cocos2d::CCPoint& p){
    return ccp(round((p.x - X_OFFSET) / PIECE_WIDTH ), round((p.y - Y_OFFSET) / PIECE_HEIGHT));
}

void Move::operator=(const Move &_move){
    this->currentRound = _move.currentRound;
    this->src = _move.src;
    this->dest = _move.dest;
    this->eatenPoints = _move.eatenPoints;
}