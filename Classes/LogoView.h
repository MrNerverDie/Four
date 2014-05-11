//
//  LogoView.h
//  Four
//
//  Created by 王选易 on 14-5-3.
//
//

#ifndef __Four__LogoView__
#define __Four__LogoView__

#include "ChessboardProtocol.h"

#include "cocos2d.h"

using namespace cocos2d;

class LogoView : public CCSprite {
    CC_SYNTHESIZE(const Move*, currentMove, CurrentMove);
    CC_SYNTHESIZE(PIECE, presentRound, PresentRound);
    
public:
    bool init();
    CREATE_FUNC(LogoView);
    static LogoView* create(const Move* _currentMove, CCSpriteFrame* frame, PIECE _presentRound);
    virtual ~LogoView();
    
    void onEnter();
    
    // listener
    void onNextRound(CCObject* o);

    // 在有AI的情况下LogoView需要对胜利或者失败的场景做出反应
    void activateStop();
    void onStop();
};

#endif /* defined(__Four__LogoView__) */
