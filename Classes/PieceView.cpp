//
//  PieceView.cpp
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#include "PieceView.h"
#include "ChessboardProtocol.h"
#include "Chessboard.h"

cocos2d::CCPoint toRealLocation(const cocos2d::CCPoint& logic_location){
    return ccp(logic_location.x * PIECE_WIDTH + X_OFFSET, logic_location.y * PIECE_HEIGHT + Y_OFFSET);
}

bool PieceView::init(){
    CCSprite::init();
    this->setAnchorPoint(ccp(0.5, 0.5));
    return true;
}

PieceView* PieceView::create(const Move* _currentMove, cocos2d::CCSpriteFrame *frame, const CCPoint& logic_location){
    PieceView* view = PieceView::create();
    view->setCurrentMove(_currentMove);
    view->setDisplayFrame(frame);
    view->setPosition(toRealLocation(logic_location));
    return view;
}

