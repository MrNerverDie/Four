//
//  Chessboard.cpp
//  Four
//
//  Created by 王选易 on 14-4-20.
//
//

#include "Chessboard.h"
#include "Message.h"
#include "ChessboardChecker.h"

#include <algorithm>

bool Chessboard::init(){
    
    // 状态机实现
    Model::addTransition("start", BEGIN_MOVE_MSG, "moving")
        ->addTransition("moving", END_MOVE_MSG, "judge_eat")
        ->addTransition("judge_eat", NEXT_ROUND_MSG, "start")
        ->addTransition("judge_eat", BEGIN_EAT_MSG, "eating")
        ->addTransition("eating", END_EAT_MSG, "judge_win")
        ->addTransition("judge_win", NEXT_ROUND_MSG, "start")
        ->addTransition("judge_win", WIN_MSG, "win");
    
    PIECE _pieces[][WIDTH] = {
        { BLACK, BLACK, BLACK, BLACK },
        { ZERO, ZERO, ZERO, ZERO },
        { ZERO, ZERO, ZERO, ZERO },
        { WHITE, WHITE, WHITE, WHITE }
    };
   
    this->setPieces(_pieces);
    
    using namespace cocos2d;
    
    // Add Listeners
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Chessboard::onNextRound), NEXT_ROUND_MSG, nullptr);
    
    return true;
}

bool Chessboard::checkWin(const Move &move){
    return ::checkWin(pieces, move);
}

// 检查能否让某一方获胜,并且分发获胜事件
void Chessboard::alterWin(){
    this->onMessage(WIN_MSG);
}

bool Chessboard::checkEat(Move& move){
    return ::checkEat(pieces, move);
}

// 检测能否吃掉一个棋子
void Chessboard::alterEat(const Move& move){
    
    
    currentMove.eatenPoints = move.eatenPoints;
    std::vector<cocos2d::CCPoint>& eatenPoints = currentMove.eatenPoints;
    

    for (auto point : eatenPoints) {
        this->setPiece(point, ZERO);
    }
    
    
    this->onMessage(BEGIN_EAT_MSG);
    
}


bool Chessboard::checkMove(const Move &move){
    return ::checkMove(this->pieces, move);
}

// 检测这一步是否能走，并且修改当前Point的值
void Chessboard::alterMove(const Move& move){
    
    const cocos2d::CCPoint& src = currentMove.src = move.src;
    const cocos2d::CCPoint& dest = currentMove.dest =  move.dest;
    
    // 将currentPoint的值改为目标位置的值
    this->setPiece(src, ZERO);
    this->setPiece(dest, currentMove.currentRound);
    
    this->onMessage(BEGIN_MOVE_MSG);
}

void Chessboard::setPiece(const cocos2d::CCPoint& p, PIECE type){
    pieces[p.y][p.x] = type;
}

PIECE Chessboard::getPiece(const cocos2d::CCPoint& p){
    return pieces[p.y][p.x];
}

void Chessboard::setPieces(PIECE _pieces[][WIDTH]){
    pieces.clear();
    for (int i = 0; i < HEIGHT; ++i) {
        pieces.push_back(vector<PIECE>(_pieces[i], _pieces[i] + WIDTH));
    }
    return ;
}

void Chessboard::onNextRound(){
    moves.push(Move(currentMove));
    currentMove.currentRound = oppositePiece(currentMove.currentRound);
    currentMove.src = ccp(-1, -1);
    currentMove.dest = currentMove.dest;
    currentMove.eatenPoints.clear();
}



