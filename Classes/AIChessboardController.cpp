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
#include "PieceView.h"
#include "LogoView.h"
#include "Tag.h"
#include "ResultView.h"
#include "RotFlowerParticle.h"

AIChessboardController::~AIChessboardController(){
    CC_SAFE_RELEASE(actor);
}

bool AIChessboardController::init(){
    ChessboardController::init();
    
    actor = AIController::create();
    actor->retain();
    
    LogoView* black = dynamic_cast<LogoView*>(this->getChildByTag(ROUND_BLACK));
    LogoView* white = dynamic_cast<LogoView*>(this->getChildByTag(ROUND_WHITE));
    
    black->activateStop();
    white->activateStop();
    
    CCLabelTTF* label = ResultView::create();
    this->addChild(label);
    
    modeLabel->setString("人机对战");
    
    return true;
}

void AIChessboardController::onEnter(){
    ChessboardController::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(AIChessboardController::onNextRound), NEXT_ROUND_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, CLICK_REGRET_MSG);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(AIChessboardController::tryRegret), AI_END_MOVE_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(AIChessboardController::tryAIRegret), CLICK_REGRET_MSG, nullptr);
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

void AIChessboardController::tryAIRegret(cocos2d::CCObject *o){
    if (chessboard->checkMessage(REGRET_MSG)){
        chessboard->alterAIRegret();
        
        CCString* frame_name = ( chessboard->getCurrentMove().currentRound == WHITE ) ? CCString::create("black.png") : CCString::create("white.png");
        
        for (CCPoint p : chessboard->getCurrentMove().eatenPoints) {
            CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
            CCSprite* piece = PieceView::create(&(this->chessboard->getCurrentMove()), this->chessboard, cache->spriteFrameByName(frame_name->getCString()), p);
            this->addChild(piece);
        }
    }
}

void AIChessboardController::tryWin(cocos2d::CCObject* o){
    if (chessboard->checkMessage(WIN_MSG)) {
        if (chessboard->checkWin(chessboard->getCurrentMove()) &&  chessboard->getCurrentMove().currentRound == PLAYER){
            chessboard->alterWin();
            this->addChild(RotFlowerParticle::create());
        }else if (chessboard->checkWin(chessboard->getCurrentMove()) &&  chessboard->getCurrentMove().currentRound == AI) {
            chessboard->alterLose();
        }else{
            chessboard->alterNextRound();
        }
    }
}
