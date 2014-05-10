//
//  FixMoveAIChessboardController.h
//  Four
//
//  Created by 王选易 on 14-5-9.
//
//

#ifndef __Four__FixMoveAIChessboardController__
#define __Four__FixMoveAIChessboardController__

#include "AIChessboardController.h"

#include "cocos2d.h"

using namespace std;

class FixMoveAIChessboardController : public AIChessboardController {
    
public:
    bool init();
    CREATE_FUNC(FixMoveAIChessboardController);
};

#endif /* defined(__Four__FixMoveAIChessboardController__) */
