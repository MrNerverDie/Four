//
//  ChessboardChecker.cpp
//  Four
//
//  Created by 王选易 on 14-4-26.
//
//

#include "ChessboardChecker.h"

#include <vector>
#include <cmath>

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
//add by yun 
bool canMove(const ChessboardData& pieces,const int i,const int j)
{
	return
	!((i==0||pieces[i-1][j]!=ZERO)&&
	(i==HEIGHT-1||pieces[i+1][j]!=ZERO)&&
	(j==0||pieces[i][j-1]!=ZERO)&&
	(j==WIDTH-1||pieces[i][j+1]!=ZERO));
}
bool checkNowhereMove(const ChessboardData& pieces, const Move& move )
{
	PIECE enemyRound = oppositePiece(move.currentRound);
	auto canNotMove=true;
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (pieces[i][j] == enemyRound)
			{
				if (canMove(pieces,i,j))
					{
						canNotMove=false;
						break;
				}
			}
		}
	}
	return canNotMove;
}
//end
bool checkWin( const ChessboardData& pieces, const Move& move ){
    PIECE enemyRound = oppositePiece(move.currentRound);
    int cnt = 0;
	//auto canNotMove=true;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (pieces[i][j] == enemyRound)
			{
                cnt++;
				//if (canMove(pieces,i,j))
				//	canNotMove=false;
			}
        }
    }
	//if (canNotMove)
		//return true;
    if (cnt < 2)
        return true;
    return false;
}

bool checkMove( const ChessboardData& pieces, const Move& move ){
  
    if ( inbound(move.src) && inbound(move.dest) && 
		getPiece(pieces, move.src) == move.currentRound && 
		getPiece(pieces, move.dest) == ZERO && 
		(move.dest.x - (floor)(move.dest.x)) == 0)
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
                    if ((getPiece(pieces, second) == oppositePiece(currentRound) && getPiece(pieces, third) == ZERO)){
                        eatenPoints.push_back(second);
                    }else if (getPiece(pieces, third) == oppositePiece(currentRound) && getPiece(pieces, second) == ZERO){
                        eatenPoints.push_back(third);
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
    logPoint(eatenPoints[0]);
    return true;
}
