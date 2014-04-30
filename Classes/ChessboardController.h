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

using cocos2d::CCTouch;
using cocos2d::CCEvent;

class Chessboard;

using cocos2d::CCLayer;

class ChessboardController : public CCLayer  {
private:
    Chessboard* chessboard;
    
public:
    virtual bool init();
    
    CREATE_FUNC(ChessboardController);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    // try方法, 向Model请求进行操作
    void tryMove(const CCPoint& src, const CCPoint& dest);
    void tryEat();
    void tryWin();
    
};



#endif /* defined(__Four__ChessboardController__) */
