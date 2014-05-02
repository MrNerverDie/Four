//
//  ChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#include "ChessboardController.h"
#include "PieceView.h"
#include "Chessboard.h"

bool ChessboardController::init(){
    using namespace cocos2d;
    
    if (! CCLayer::init()) {
        return false;
    }
    
    // 初始化Model
    this->chessboard = Chessboard::create();
    this->chessboard->retain();
    
    //初始化View
    CCSpriteBatchNode* batch = CCSpriteBatchNode::create("AllSprites.png");
    this->addChild(batch);
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("AllSprites.plist");
    
    CCSprite* background = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("background.png"));
    background->setAnchorPoint(ccp(0, 0));
    background->setPosition(ccp(0, 0));
    this->addChild(background);
    
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            CCString* frame_name;
            if (chessboard->getPiece(ccp(j, i)) == BLACK )
                frame_name = new CCString("black.png");
            else if (chessboard->getPiece(ccp(j, i)) == WHITE)
                frame_name = new CCString("white.png");
            else
                continue;
            CCSprite* black = PieceView::create(&(this->chessboard->getCurrentMove()), this->chessboard, cache->spriteFrameByName(frame_name->getCString()), ccp(j, i));
            this->addChild(black);
        }
    }
    
//    // touch
    this->setTouchEnabled(true);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChessboardController::tryEat), END_MOVE_MSG, nullptr);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChessboardController::tryWin), END_EAT_MSG, nullptr);

    return true;
}


void ChessboardController::onEnter()
{
    using cocos2d::CCDirector;
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
}

void ChessboardController::onExit()
{
    using cocos2d::CCDirector;
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool ChessboardController::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    return true;
}

void ChessboardController::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    //    CCTouchDelegate
}

void logPoint(const cocos2d::CCPoint& p){
    CCLOG("x:%f y:%f", p.x, p.y);
}

void ChessboardController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    tryMove(RealToLogic(pTouch->getStartLocation()), RealToLogic(pTouch->getLocation()));
}

void ChessboardController::tryMove(const CCPoint& src, const CCPoint& dest){
    CCPoint newDest = (dest - src) / (dest - src).getLength();
    Move move(chessboard->getCurrentMove().currentRound,src, newDest);
    if(chessboard->checkMessage(BEGIN_MOVE_MSG) && chessboard->checkMove(move)){
        chessboard->alterMove(move);
    }
}

void ChessboardController::tryEat(){
    Move move(chessboard->getCurrentMove());
    if(chessboard->checkMessage(BEGIN_EAT_MSG)){
        if (chessboard->checkEat(move)){
            chessboard->alterEat(move);
        }else{
            chessboard->onMessage(NEXT_ROUND_MSG);
        }
    }
}

void ChessboardController::tryWin(){
    if (chessboard->checkMessage(WIN_MSG)) {
        if (chessboard->checkWin(chessboard->getCurrentMove())){
            chessboard->alterWin();
        }else{
            chessboard->onMessage(NEXT_ROUND_MSG);
        }
    }
}
