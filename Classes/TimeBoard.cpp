//
//  TimeBoard.cpp
//  Four
//
//  Created by 王选易 on 14-5-10.
//
//

#include "TimeBoard.h"
#include "Message.h"

bool TimeBoard::init(){
    
    leftSeconds = 60;
    CCLabelTTF::initWithString("60", "Helvetica-Bold", 32.0f);
    this->setColor(ccBLACK);
    this->setPosition(ccp(320, 860));
    
    return true;
}

void TimeBoard::onEnter(){
    CCLabelTTF::onEnter();
    this->schedule(schedule_selector(TimeBoard::onTimeChanged), 1.0f);
}

void TimeBoard::onExit(){
    CCLabelTTF::onExit();
    this->unscheduleAllSelectors();
}

void TimeBoard::onTimeChanged(float dt){
    leftSeconds--;
    CCString* str = CCString::createWithFormat("%d", leftSeconds);
    this->setString(str->getCString());
    if (leftSeconds == 0) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(LOSE_MSG);
    }
}