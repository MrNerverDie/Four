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
#include "Model.h"
#include "ChessboardProtocol.h"

using namespace cocos2d;

class PieceView : public CCSprite{
    CC_SYNTHESIZE(const Move*, currentMove, CurrentMove);
    CC_SYNTHESIZE(Model*, model, Model);
private:
    bool containsTouchLocation(CCTouch* touch);
    
public:
    PieceView(){}
    virtual ~PieceView();
    virtual bool init();
    CREATE_FUNC(PieceView);
    static PieceView* create(const Move* _currentMove, Model* _model, CCSpriteFrame* frame, const CCPoint& _logic_position);
    
    // listener
    void onBeginMove();
    void onBeginEat();
};

#endif /* defined(__Four__PieceView__) */
