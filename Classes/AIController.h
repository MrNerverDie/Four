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

using cocos2d::CCObject;

class AIController : public CCObject {
    CC_SYNTHESIZE(PIECE, AIPiece, AIPiece);
    
public:
    bool init();
    CREATE_FUNC(AIController);
    
    void getNextMove(const ChessboardData& pieces, Move& nextMove);
};

#endif /* defined(__Four__AIController__) */
