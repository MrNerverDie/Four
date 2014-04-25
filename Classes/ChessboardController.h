//
//  ChessboardController.h
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#ifndef __Four__ChessboardController__
#define __Four__ChessboardController__

#include "ChessboardProtocol.h"

#include "cocos2d.h"

class Chessboard;

using cocos2d::CCLayer;

class ChessboardController : public CCLayer  {
private:
    Chessboard* chessboard;
    
public:
    virtual bool init();
    
    CREATE_FUNC(ChessboardController);
    
};

#endif /* defined(__Four__ChessboardController__) */
