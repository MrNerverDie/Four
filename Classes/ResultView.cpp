//
//  ResultView.cpp
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#include "ResultView.h"
#include "Message.h"

ResultView::~ResultView(){
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool ResultView::init(){
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ResultView::onWin), WIN_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ResultView::onLose), LOSE_MSG, nullptr);
    
    CCLabelTTF::initWithString("", "Helvetica-Bold", 96.0f);
    this->setColor(ccBLACK);
    this->setPosition(ccp(320, 1200));
    
    return true;
}

void ResultView::onWin(CCObject* o){
    this->setString("WIN");
    this->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5f, ccp(320, 960))));
}

void ResultView::onLose(CCObject* o){
    this->setString("LOSE");
    this->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5f, ccp(320, 960))));
}