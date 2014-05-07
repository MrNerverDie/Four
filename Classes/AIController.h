//
//  AIController.h
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#ifndef __Four__AIController__
#define __Four__AIController__

#include "ChessboardProtocol.h"
#include "cocos2d.h"

#include <vector>

struct Solution
{
public:
	Move move = Move(BLACK);
	int score;

	~Solution(){
		CCLOG("fdsadsaf %s", "haha");
//		delete move;
	}
};

typedef std::vector<Solution> SolutionList;
using cocos2d::CCObject;


class AIController : public CCObject {
    CC_SYNTHESIZE(PIECE, AIPiece, AIPiece);
    
public:
    bool init();
    CREATE_FUNC(AIController);
    
    void getNextMove(const ChessboardData& pieces, Move& nextMove);

private:

	//生成解决方案呢
	void createSolutions(const ChessboardData& pieces, Move& nextMove, SolutionList& solutionList);
	//生成一个解决方案
//	Solution* createSolution(const ChessboardData& pieces, Move* move);
	// 创建走完后的棋盘
	void createChessboardMoveOver(const ChessboardData& pieces1, Move& nextMove, ChessboardData& pieces2);

	// 杀人评分
	int getKillScore(const ChessboardData& pieces, Move& nextMove);
	// 走位评分
	int getGoalScore(const ChessboardData& pieces, Move& nextMove);
	// 总评分
	int getTotalScore(const ChessboardData& pieces, Move& nextMove);
};

#endif /* defined(__Four__AIController__) */
