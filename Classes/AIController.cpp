//
//  AIController.cpp
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#include "AIController.h"
#include "ChessboardChecker.h"

typedef std::vector<Solution> SolutionList;

bool AIController::init(){
    return true;
}

void AIController::getNextMove(const ChessboardData &pieces, Move &nextMove){
//   nextMove.src = ccp(0, 3);
//  nextMove.dest = ccp(0, 2);

	SolutionList solutionList;
	createSolutions(pieces, nextMove, solutionList);

	int index = 0, largest = 0;
//	Solution *resultSolution;
	Move resultMove = Move(nextMove.currentRound);
	for (auto s : solutionList){
		if (s.score > largest) {
			largest = s.score;
//			resultSolution = &s;
			resultMove = s.move;
		} 
	}
	nextMove = resultMove;
	solutionList.clear();
}

//生成解决方案呢
void AIController::createSolutions(const ChessboardData& pieces, Move& nextMove, SolutionList& solutionList) {
	PIECE p;
	float destX, destY;

	for (int i = 0; i < WIDTH; i++) {	// 获取所有棋子
		for (int j = 0; j < HEIGHT; j++) {
			p = getPiece(pieces, ccp(i, j));
			if (p == nextMove.currentRound) {	// 所属同一阵营
				//往上
				if (inbound(ccp(i, j + 1))) {
					Move move = Move(nextMove.currentRound, ccp(i, j), ccp(i, j + 1));
					if (checkMove(pieces, move)) {
						Solution solution = Solution();
						solution.move = move;
						ChessboardData pieces2;
						createChessboardMoveOver(pieces, move, pieces2);
						solution.score = getTotalScore(pieces2, move);
						solutionList.push_back(solution);
					}
				}

				//往下
				if (inbound(ccp(i, j - 1))) {
					Move move = Move(nextMove.currentRound, ccp(i, j), ccp(i, j - 1));
					if (checkMove(pieces, move)) {
						Solution solution;
						solution.move = move;
						ChessboardData pieces2;
						createChessboardMoveOver(pieces, move, pieces2);
						solution.score = getTotalScore(pieces2, move);
						solutionList.push_back(solution);
					}
				}
				//往左
				if (inbound(ccp(i - 1, j))) {
					Move move = Move(nextMove.currentRound, ccp(i, j), ccp(i - 1, j));
					if (checkMove(pieces, move)) {
						Solution solution;
						solution.move = move;
						ChessboardData pieces2;
						createChessboardMoveOver(pieces, move, pieces2);
						solution.score = getTotalScore(pieces2, move);
						solutionList.push_back(solution);
					}
				}
				//往右
				if (inbound(CCPoint(i + 1, j))) {
					Move move = Move(nextMove.currentRound, ccp(i, j), ccp(i + 1, j));
					if (checkMove(pieces, move)) {
						Solution solution;
						solution.move = move;
						ChessboardData pieces2;
						createChessboardMoveOver(pieces, move, pieces2);
						solution.score = getTotalScore(pieces2, move);
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