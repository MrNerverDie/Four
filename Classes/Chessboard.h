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

#include "cocos2d.h"
using cocos2d::CCArray;
using cocos2d::CCPoint;

class Chessboard : public Model {
    CC_SYNTHESIZE_PASS_BY_REF(Move, currentMove, CurrentMove);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(ChessboardData, pieces, Pieces)
    
private:
    // 棋盘代表了存储棋子类型的二维数组
    stack< Move > moves;
    
    void setPiece(const cocos2d::CCPoint& p, PIECE type);
    
public:
    explicit Chessboard():Model("start"),currentMove(BLACK, ccp(-1, -1), ccp(-1, -1)){}
    
    virtual ~Chessboard();
    bool init();
    
    CREATE_FUNC(Chessboard);
    
    // 检查能否让某一方获胜,并且分发获胜事件
    bool checkWin(const Move& move);
    void alterWin();
    void alterLose();
    
    // 检测能否吃掉一个棋子,并且将棋盘模型进行改变
    bool checkEat(Move& move);
    void alterEat(const Move& move);
    
    // 检测这一步是否能走，并且将棋盘模型进行改变
    bool checkMove(const Move& move);
    void alterMove(const Move& move);
    
    void alterNextRound();
    void alterRegret();
    void alterAIRegret();
    
    // for test, not recommend to use
    void setPieces(PIECE _pieces[][WIDTH]);
    void setPieces(const ChessboardData& data );
    PIECE getPiece(const cocos2d::CCPoint& p);
    
};

#endif /* defined(__Four__Chessboard__) */
