//
//  Chessboard.cpp
//  Four
//
//  Created by 王选易 on 14-4-20.
//
//

#include "Chessboard.h"
#include "Message.h"

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
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(Chessboard::onNextRound), NEXT_ROUND_MSG, NULL);
    
    return true;
}

// 检查能否让某一方获胜,并且分发获胜事件
bool Chessboard::alterWin(){
    PIECE enemyRound = (currentMove.currentRound == BLACK ? WHITE : BLACK);
    int cnt = 0;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (pieces[i][j] == enemyRound)
                cnt++;
        }
    }
    if (cnt < 2)
        return true;
    return false;
}

bool inbound(const CCPoint& p, int width, int height){
    return p.x >= 0 && p.y >= 0 && p.x < width && p.y < height;
}

bool inbound(const CCPoint& p){
    return inbound(p, WIDTH, HEIGHT);
}

PIECE oppositePiece(PIECE p){
    return (p == BLACK ? WHITE : BLACK);
}

// 检测能否吃掉一个棋子
bool Chessboard::alterEat(){
    
    cocos2d::CCPoint currentPoint = currentMove.dest;
    PIECE currentRound = currentMove.currentRound;
    std::vector<cocos2d::CCPoint>& eatenPoints = currentMove.eatenPoints;
    
    cocos2d::CCPoint directions[4] = {ccp(1, 0), ccp(-1, 0), ccp(0, 1), ccp(0, -1)};
    for(auto direction : directions){
        CCPoint first = currentPoint + direction;
        if (inbound(first) && this->getPiece(first) == currentRound){
            CCPoint second = currentPoint + direction * 2;
            if (inbound(second)){
                CCPoint third = currentPoint + direction * 3;
                if (inbound(third)) {
                    if (this->getPiece(second) == oppositePiece(currentRound) && this->getPiece(third) == ZERO){
                        eatenPoints.push_back(second);
                    }
                }else{
                    third = currentPoint - direction;
                    if ((this->getPiece(second) == oppositePiece(currentRound) && this->getPiece(third) == ZERO) ||
                        (this->getPiece(third) == oppositePiece(currentRound) && this->getPiece(second) == ZERO) ){
                        eatenPoints.push_back(second);
                    }
                }
            }else{
                second = currentPoint - direction;
                CCPoint third = currentPoint - direction * 2;
                if (this->getPiece(second) == oppositePiece(currentRound) && this->getPiece(third) == ZERO){
                    eatenPoints.push_back(second);
                }
            }
        }
    }
    
    CCLOG("size : %zu", eatenPoints.size());
    for (auto point : eatenPoints) {
        this->setPiece(point, ZERO);
    }
    
    if (eatenPoints.size() == 0)
        return false;
    return true;
}

// 检测这一步是否能走，并且修改当前Point的值
bool Chessboard::alterMove(const CCPoint& src, const CCPoint& dest){
    if ( this->getPiece(src) == currentMove.currentRound && this->getPiece(dest) == ZERO)
        return false;
    // 将currentPoint的值改为目标位置的值
    this->setPiece(src, ZERO);
    this->setPiece(dest, currentMove.currentRound);
    // 修改当前Move
    currentMove.src = src;
    currentMove.dest = dest;
    return true;
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

void Chessboard::clearMove(){
    currentMove.currentRound = oppositePiece(currentMove.currentRound);
    currentMove.src = ccp(-1, -1);
    currentMove.dest = currentMove.dest;
    currentMove.eatenPoints.clear();
}

void Chessboard::onNextRound(){
    moves.push(Move(currentMove));
    this->clearMove();
}



