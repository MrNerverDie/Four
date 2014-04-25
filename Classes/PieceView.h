//
//  PieceView.h
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#ifndef __Four__PieceView__
#define __Four__PieceView__

#include "cocos2d.h"

using cocos2d::CCSprite;
using cocos2d::CCSpriteFrame;
using cocos2d::CCPoint;

class Chessboard;

class PieceView : public CCSprite {
    CC_SYNTHESIZE(Chessboard*, chessboard, Chessboard);
    
public:
    virtual bool init();
    CREATE_FUNC(PieceView);
    static PieceView* create(Chessboard* chessboard, CCSpriteFrame* frame, const CCPoint& logic_location);
};

#endif /* defined(__Four__PieceView__) */
