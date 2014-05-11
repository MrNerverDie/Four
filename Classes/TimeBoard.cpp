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
    CCLabelTTF::initWithString("Time : 60", "Helvetica-Bold", 32.0f);
    this->setColor(ccBLACK);
    this->setPosition(ccp(320, 860));
    
    return true;
}

void TimeBoard::onEnter(){
    CCLabelTTF::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TimeBoard::onStop), WIN_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(TimeBoard::onStop), LOSE_MSG, nullptr);
    this->schedule(schedule_selector(TimeBoard::onTimeChanged), 1.0f);
}

void TimeBoard::onExit(){
    CCLabelTTF::onExit();
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    this->unscheduleAllSelectors();
}

void TimeBoard::onTimeChanged(float dt){
    leftSeconds--;
    CCString* str = CCString::createWithFormat("Time : %d", leftSeconds);
    this->setString(str->getCString());
    if (leftSeconds == 0) {
        CCNotificationCenter::sharedNotificationCenter()->postNotification(LOSE_MSG);
    }
}

void TimeBoard::onStop(){
    this->unscheduleAllSelectors();
}

