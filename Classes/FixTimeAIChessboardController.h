//
//  FixTimeAIChessboardController.h
//  Four
//
//  Created by 王选易 on 14-5-9.
//
//

#ifndef __Four__FixTimeAIChessboardController__
#define __Four__FixTimeAIChessboardController__

#include "AIChessboardController.h"

#include "cocos2d.h"

using namespace cocos2d;

class FixTimeAIChessboardController : public AIChessboardController {
    
public:
    bool init();
    CREATE_FUNC(FixTimeAIChessboardController);
};

#endif /* defined(__Four__FixTimeAIChessboardController__) */
