//
//  AIChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIChessboardController.h"
#include "AIController.h"
#include "Message.h"
#include "Chessboard.h"

AIChessboardController::~AIChessboardController(){
    CC_SAFE_RELEASE(actor);
}

bool AIChessboardController::init(){
    ChessboardController::init();
    
    actor = AIController::create();
    actor->retain();
    
    return true;
}

void AIChessboardController::onEnter(){
    ChessboardController::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(AIChessboardController::onNextRound), NEXT_ROUND_MSG, nullptr);
}

void AIChessboardController::onExit(){
    ChessboardController::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void AIChessboardController::onNextRound(CCObject* o){
    if (chessboard->getCurrentMove().currentRound == AI ) {
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
        Move move(AI);
        actor->getNextMove(chessboard->getPieces(), move);
        this->tryMove(move.src, move.dest);
    }else {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    }
}