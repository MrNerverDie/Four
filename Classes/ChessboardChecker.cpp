//
//  ChessboardChecker.cpp
//  Four
//
//  Created by 王选易 on 14-4-26.
//
//

#include "ChessboardChecker.h"

#include <vector>
using std::vector;

bool inbound(const CCPoint& p, int width, int height){
    return p.x >= 0 && p.y >= 0 && p.x < width && p.y < height;
}

bool inbound(const CCPoint& p){
    return inbound(p, WIDTH, HEIGHT);
}

PIECE oppositePiece(PIECE p){
    return (p == BLACK ? WHITE : BLACK);
}

PIECE getPiece(const ChessboardData& pieces, const cocos2d::CCPoint& p){
    return pieces[p.y][p.x];
}

bool checkWin( const ChessboardData& pieces, const Move& move ){
    PIECE enemyRound = oppositePiece(move.currentRound);
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

bool checkMove( const ChessboardData& pieces, const Move& move ){
    CCLOG("%d", getPiece(pieces, move.dest));
    CCLOG("%d", getPiece(pieces, move.src));
    CCLOG("%d", move.currentRound);
//    PIECE p2 = getPiece(pieces, move.src);
//    PIECE p1 = getPiece(pieces, move.dest);
    if ( getPiece(pieces, move.src) == move.currentRound && getPiece(pieces, move.dest) == ZERO)
        return true;
    return false;
}

bool checkEat( const ChessboardData& pieces, Move& move ){
    cocos2d::CCPoint currentPoint = move.dest;
    PIECE currentRound = move.currentRound;
    std::vector<cocos2d::CCPoint>& eatenPoints = move.eatenPoints;
    
    cocos2d::CCPoint directions[4] = {ccp(1, 0), ccp(-1, 0), ccp(0, 1), ccp(0, -1)};
    for(auto direction : directions){
        CCPoint first = currentPoint + direction;
        if (inbound(first) && getPiece(pieces, first) == currentRound){
            CCPoint second = currentPoint + direction * 2;
            if (inbound(second)){
                CCPoint third = currentPoint + direction * 3;
                if (inbound(third)) {
                    if (getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO){
                        eatenPoints.push_back(second);
                    }
                }else{
                    third = currentPoint - direction;
                    if ((getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO) ||
                        (getPiece(pieces, third) == oppositePiece(currentRound) && getPiece(pieces, second) == ZERO) ){
                        eatenPoints.push_back(second);
                    }
                }
            }else{
                second = currentPoint - direction;
                CCPoint third = currentPoint - direction * 2;
                if (getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO){
                    eatenPoints.push_back(second);
                }
            }
        }
    }
        CCLOG("size : %lu", eatenPoints.size());
    
    if (eatenPoints.size() == 0)
        return false;
    return true;
}
