//
//  LogoView.cpp
//  Four
//
//  Created by 王选易 on 14-5-3.
//
//

#include "LogoView.h"
#include "Message.h"

LogoView::~LogoView(){
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

bool LogoView::init(){
    CCSprite::init();
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LogoView::onNextRound), NEXT_ROUND_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(LogoView::onNextRound), REGRET_MSG, nullptr);
    
    return true;
}

LogoView* LogoView::create(const Move *_currentMove, cocos2d::CCSpriteFrame *frame, PIECE _presentRound){
    LogoView* view = LogoView::create();
    view->setDisplayFrame(frame);
    view->setCurrentMove(_currentMove);
    view->setPresentRound(_presentRound);
    return view;
}

void LogoView::onEnter(){
    CCSprite::onEnter();
    this->setPosition(ccp(832, 960));
    if (this->presentRound == this->currentMove->currentRound ){
        this->onNextRound(nullptr);
    }
}

void LogoView::onNextRound(CCObject* o){
    if (this->presentRound == this->currentMove->currentRound ) {
        this->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.0f, ccp(320, 960))));
    }else{
        this->runAction(CCSequence::createWithTwoActions(CCMoveTo::create(0.4f, ccp(-192, 960)), CCPlace::create(ccp(832, 960)) ) );
    }
}