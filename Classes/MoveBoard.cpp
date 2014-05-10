//
//  MoveBoard.cpp
//  Four
//
//  Created by 王选易 on 14-5-10.
//
//

#include "MoveBoard.h"
#include "Message.h"
#include "Chessboard.h"

bool MoveBoard::init(){
    
    leftMoves = 30;
    CCLabelTTF::initWithString("Move : 30", "Helvetica-Bold", 32.0f);
    this->setColor(ccBLACK);
    this->setPosition(ccp(320, 860));
    
    return true;
}

void MoveBoard::onEnter(){
    CCLabelTTF::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MoveBoard::onNextRound), NEXT_ROUND_MSG, NULL);
}

void MoveBoard::onExit(){
    CCLabelTTF::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void MoveBoard::onNextRound(cocos2d::CCObject *o){
    Chessboard* chessboard = dynamic_cast<Chessboard*>(o);
    if (chessboard->getCurrentMove().currentRound == BLACK){
        leftMoves--;
        CCString* str = CCString::createWithFormat("Move : %d", leftMoves);
        this->setString(str->getCString());
        if (leftMoves == 0) {
            CCNotificationCenter::sharedNotificationCenter()->postNotification(LOSE_MSG);
        }
    }
}


