//
//  ChessboardProtocol.h
//  Four
//
//  Created by 王选易 on 14-4-20.
//
//

#ifndef Four_ChessboardProtocol_h
#define Four_ChessboardProtocol_h

#include "cocos2d.h"
using cocos2d::CCPoint;

typedef enum {
    ZERO,
    BLACK,
    WHITE,
} PIECE;

const int WIDTH = 4;
const int HEIGHT = 4;
const int PIECE_NUM = 4;

const int PIECE_WIDTH = 128;
const int PIECE_HEIGHT = 128;

const int X_OFFSET = 128;
const int Y_OFFSET = 288;

struct Move {
    PIECE currentRound;
    CCPoint src;
    CCPoint dest;
    std::vector<cocos2d::CCPoint> eatenPoints;
    Move(PIECE _p):currentRound(_p){}
    Move(PIECE _p,const cocos2d::CCPoint& _src, const cocos2d::CCPoint& _dest):currentRound(_p),src(_src),dest(_dest){}
    Move(const cocos2d::CCPoint& _src, const cocos2d::CCPoint& _dest):src(_src),dest(_dest){}
    Move(const Move& _move):currentRound(_move.currentRound),src(_move.src),dest(_move.dest),eatenPoints(_move.eatenPoints){}
};

typedef std::vector< std::vector<PIECE> > ChessboardData;

CCPoint LogicToReal(const cocos2d::CCPoint& p);

CCPoint RealToLogic(const cocos2d::CCPoint& p);


#endif
