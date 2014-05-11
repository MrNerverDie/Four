//
//  AIChessboardController.h
//  Four
//
//  Created by 王选易 on 14-5-5.
//
//

#ifndef __Four__AIChessboardController__
#define __Four__AIChessboardController__

#include "ChessboardController.h"
#include "ChessboardProtocol.h"

#include "cocos2d.h"

using cocos2d::CCNotificationCenter;

class AIController;

class AIChessboardController : public ChessboardController{
    PIECE PLAYER;
    PIECE AI;
    
    AIController* actor;
public:
    bool init();
    AIChessboardController():PLAYER(BLACK), AI(WHITE){}
    virtual ~AIChessboardController();
    
    CREATE_FUNC(AIChessboardController);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onNextRound(CCObject* o);
    virtual void tryAIRegret(CCObject* o);
    virtual void tryWin(CCObject* o);
};

#endif /* defined(__Four__AIChessboardController__) */
