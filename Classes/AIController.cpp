//
//  AIController.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIController.h"
#include "ChessboardChecker.h"
#include <cstdlib>
#include <ctime>

typedef std::vector<Solution> SolutionList;

bool AIController::init(){
    return true;
}

void AIController::getNextMove(const ChessboardData &pieces, Move &nextMove){
//   nextMove.src = ccp(0, 3);
//  nextMove.dest = ccp(0, 2);

	SolutionList solutionList;
	createSolutions(pieces, nextMove, solutionList);
	for (auto itr = solutionList.begin(); itr != solutionList.end(); ++itr)
		reduceBeKilledScore(*itr);

	int largest = solutionList[0].score;
//	Solution *resultSolution;
	Move resultMove = solutionList[0].move;
	for (auto s : solutionList){
		std::srand(std::time(0));
		if (s.score > largest) {
			largest = s.score;
//			resultSolution = &s;
			resultMove = s.move;
		}
		else if (s.score == largest && std::rand() > (RAND_MAX / 2)) {
			resultMove = s.move;
		}
	}
	nextMove = resultMove;
	solutionList.clear();
}

//生成解决方案呢
void AIController::createSolutions(const ChessboardData& pieces, Move& nextMove, SolutionList& solutionList) {
	PIECE p;

	for (int i = 0; i < WIDTH; i++) {	// 获取所有棋子
		for (int j = 0; j < HEIGHT; j++) {
			p = getPiece(pieces, ccp(i, j));
			if (p == nextMove.currentRound) {	// 所属同一阵营
				CCPoint pointDevision[] = { ccp(0, 1), ccp(0, -1), ccp(-1, 0), ccp(1, 0) };

				for (auto devision : pointDevision) {
					// 往四个方向
					Move move = Move(nextMove.currentRound, ccp(i, j), ccp(i, j) + devision);
					if (checkMove(pieces, move)) {
					CCLOG("from %d %d to %f %f", i, j, devision.x, devision.y);
						Solution solution = Solution();
						solution.move = move;
						createChessboardMoveOver(pieces, move, solution.pieces);
						solution.score = getTotalScore(solution.pieces, move);
						solutionList.push_back(solution);
					}
				}
			}
		}
	}
}

//生成一个解决方案
//Solution* AIController::createSolution(const ChessboardData& pieces, Move* move) {
//	Solution* solution = new Solution();
//	solution->move = move;
//	solution->score = getTotalScore(pieces, *move);
//}

// 创建走完后的棋盘
void AIController::createChessboardMoveOver(const ChessboardData& pieces1, Move& nextMove, ChessboardData& pieces2) {
	for (auto a : pieces1)
		pieces2.push_back(a);
	pieces2[nextMove.src.y][nextMove.src.x] = ZERO;
	pieces2[nextMove.dest.y][nextMove.dest.x] = nextMove.currentRound;
}

// 杀人评分
int AIController::getKillScore(const ChessboardData& pieces, Move& nextMove) {
//	Move move(nextMove);

//	bool canEat = checkEat(pieces, move);

	if (!checkEat(pieces, nextMove))
		return 0;

//	return (nextMove.eatenPoints.size() - nextMove.eatenPoints.size()) * 3;
	return nextMove.eatenPoints.size() * 3;
}
// 走位评分
int AIController::getGoalScore(const ChessboardData& pieces, Move& nextMove) {
	// 往中间走加1分
	return ((nextMove.src.x < 1 || nextMove.src.x > 2) && (nextMove.dest.x >= 1 && nextMove.dest.x <= 2) ? 1 : 0)
		+ ((nextMove.src.y < 1 || nextMove.src.y > 2) && (nextMove.dest.y >= 1 && nextMove.dest.y <= 2) ? 1 : 0);
}

// 总评分
int AIController::getTotalScore(const ChessboardData& pieces, Move& nextMove) {
	return getKillScore(pieces, nextMove) + getGoalScore(pieces, nextMove);
}

// 被杀扣分
void AIController::reduceBeKilledScore(Solution& solution) {
	Move move2 = solution.move;
	move2.currentRound = oppositePiece(solution.move.currentRound);

	SolutionList solutionList2;
	createSolutions(solution.pieces, move2, solutionList2);

	int largestPoint = 0;
	for (auto obj : solutionList2)
		largestPoint = obj.score > largestPoint ? obj.score : largestPoint;

	solution.score -= largestPoint;

//	int killCount = 0;
//	for (auto obj : solutionList2) 
//		killCount = (obj.move.eatenPoints.size() > killCount) ? obj.move.eatenPoints.size() : killCount;
	
//	solution.score -= killCount * 2;
}