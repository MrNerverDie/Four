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

#include <algorithm>
#include <vector>

PieceView::~PieceView(){
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    CC_SAFE_DELETE(this->dropAction);
    CC_SAFE_RELEASE(this->model);
}

bool PieceView::init(){
    CCSprite::init();
    this->setAnchorPoint(ccp(0.5, 0.5));
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PieceView::onBeginMove), BEGIN_MOVE_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PieceView::onBeginEat), BEGIN_EAT_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PieceView::onRegret), REGRET_MSG, nullptr);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(PieceView::onAIRegret), AI_REGRET_MSG, nullptr);
    
    return true;
}

PieceView* PieceView::create(const Move* _currentMove, Model* _model, cocos2d::CCSpriteFrame *frame, const CCPoint& _logic_position){
    PieceView* view = PieceView::create();
    view->setCurrentMove(_currentMove);
    view->setModel(_model);
    _model->retain();
    view->setDisplayFrame(frame);
    CCPoint dest = LogicToReal(_logic_position);
    view->setPosition(ccp(dest.x, CCDirector::sharedDirector()->getVisibleSize().height));
    CCActionInterval* drop = CCMoveTo::create(0.6f, dest);

    drop->retain();
    view->setDropAction(drop);
    
    return view;
}

void PieceView::onEnter(){
    CCSprite::onEnter();
    CCActionInterval* bounce = CCEaseBounceOut::create(this->dropAction);
    this->runAction(bounce);
    CCNotificationCenter::sharedNotificationCenter()->postNotification(CREATE_MSG);
}

void PieceView::onExit(){
    CCSprite::onExit();
    this->runAction(dropAction->reverse());
}


void PieceView::onBeginMove(CCObject* o){
    if (!(currentMove->src).equals(RealToLogic(this->getPosition())))
        return;
    CCPoint dest = LogicToReal(currentMove->dest);
    model->waitAction(this, CCEaseExponentialOut::create(CCMoveTo::create(0.5f, dest)), END_MOVE_MSG);
}

void PieceView::onBeginEat(CCObject* o){
    const std::vector<CCPoint> eatenPoints = currentMove->eatenPoints;
    CCPoint logic_position = RealToLogic(this->getPosition());
    
    
    if (std::find_if(eatenPoints.begin(), eatenPoints.end(),
                     [logic_position](const CCPoint& p)->bool{return p.equals(logic_position) ;} ) == eatenPoints.end())
//    if (!eatenPoints[0].equals(logic_position))
        return;
    CCScaleTo* st = CCScaleTo::create(0.2f, 0.05);
    CCRemoveSelf* rs = CCRemoveSelf::create();
    model->waitAction(this, CCSequence::createWithTwoActions(st, rs), END_EAT_MSG);
}

void PieceView::onRegret(CCObject* o){
    if (!(currentMove->dest).equals(RealToLogic(this->getPosition())))
        return;
    CCPoint src = LogicToReal(currentMove->src);
    model->waitAction(this, CCEaseExponentialOut::create(CCMoveTo::create(0.6f, src)), END_MOVE_MSG);
}

void PieceView::onAIRegret(CCObject* o){
    if (!(currentMove->dest).equals(RealToLogic(this->getPosition())))
        return;
    CCPoint src = LogicToReal(currentMove->src);
    model->waitAction(this, CCEaseExponentialOut::create(CCMoveTo::create(0.65f, src)), AI_END_MOVE_MSG);
}



