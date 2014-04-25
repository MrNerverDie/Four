//
//  Chessboard.h
//  Four
//
//  Created by 王选易 on 14-4-20.
//
//

#ifndef __Four__Chessboard__
#define __Four__Chessboard__

#include "Model.h"
#include "ChessboardProtocol.h"
#include "Message.h"

#include <vector>
#include <stack>
using std::vector;
using std::stack;

using cocos2d::CCArray;
using cocos2d::CCPoint;

typedef std::vector< std::vector<PIECE> > ChessboardData;

struct Move {
    PIECE currentRound;
    CCPoint src;
    CCPoint dest;
    std::vector<cocos2d::CCPoint> eatenPoints;
    Move(PIECE _p):currentRound(_p){}
    Move(const Move& _move):currentRound(_move.currentRound),src(_move.src),dest(_move.dest),eatenPoints(_move.eatenPoints){}
};

class Chessboard : public Model {
    CC_SYNTHESIZE_READONLY(Move, currentMove, CurrentMove);
    
private:
    // 棋盘代表了存储棋子类型的二维数组
    ChessboardData pieces;
    stack< Move > moves;
    
    void setPiece(const cocos2d::CCPoint& p, PIECE type);
    
public:
    explicit Chessboard():Model("start"),currentMove(BLACK){}
    
    bool init();
    
    CREATE_FUNC(Chessboard);
    
    // 检查能否让某一方获胜,并且分发获胜事件
    bool alterWin();
    
    // 检测能否吃掉一个棋子,并且将棋盘模型进行改变
    bool alterEat();
    
    // 检测这一步是否能走，并且将棋盘模型进行改变
    bool alterMove(const CCPoint& src, const CCPoint& dest);
    
    // for test, not recommend to use
    void setPieces(PIECE _pieces[][WIDTH]);
    
    PIECE getPiece(const cocos2d::CCPoint& p);
    
    void clearMove();
    
    // callback
    
    void onNextRound();
    
};

#endif /* defined(__Four__Chessboard__) */
