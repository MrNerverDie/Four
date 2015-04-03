//
//  ChessboardChecker.h
//  Four
//
//  Created by 王选易 on 14-4-26.
//
//

#ifndef __Four__ChessboardChecker__
#define __Four__ChessboardChecker__

#include "ChessboardProtocol.h"

bool inbound(const CCPoint& p);

PIECE getPiece(const ChessboardData& pieces, const cocos2d::CCPoint& p);

PIECE oppositePiece(PIECE p);

bool checkMove( const ChessboardData& pieces, const Move& move );

bool checkEat( const ChessboardData& pieces, Move& move );

bool checkWin( const ChessboardData& pieces, const Move& move );

#endif /* defined(__Four__ChessboardChecker__) */
