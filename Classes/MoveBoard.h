//
//  MoveBoard.h
//  Four
//
//  Created by 王选易 on 14-5-10.
//
//

#ifndef __Four__MoveBoard__
#define __Four__MoveBoard__

#include "cocos2d.h"

using namespace cocos2d;

class MoveBoard : public CCLabelTTF {
private:
    int leftMoves;
    
public:
    bool init();
    CREATE_FUNC(MoveBoard);
    
    void onEnter();
    void onExit();
    
    void onNextRound(CCObject* o);
};

#endif /* defined(__Four__MoveBoard__) */
