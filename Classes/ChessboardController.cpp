//
//  ChessboardController.cpp
//  Four
//
//  Created by 王选易 on 14-4-24.
//
//

#include "ChessboardController.h"
#include "PieceView.h"
#include "LogoView.h"
#include "Chessboard.h"
#include "RotFlowerParticle.h"
#include "ChessboardProtocol.h"
#include "Tag.h"

ChessboardController::~ChessboardController(){
    CC_SAFE_RELEASE(chessboard);
}

bool ChessboardController::init(){
    using namespace cocos2d;
    
    if (! BaseController::init()) {
        return false;
    }
    
    // 初始化Model
    this->chessboard = Chessboard::create();
    this->chessboard->retain();
    
//    PIECE _pieces[4][4] = {
//        {ZERO, WHITE, ZERO, BLACK},
//        {ZERO, ZERO, WHITE, BLACK},
//        {ZERO, ZERO, ZERO, ZERO},
//        {ZERO, ZERO, ZERO, ZERO}
//    };
    
//    chessboard->setPieces(_pieces);
    
    //初始化View
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    
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
    
    CCSprite* black_logo = LogoView::create(&(this->chessboard->getCurrentMove()), cache->spriteFrameByName("black_logo.png"), BLACK);
    black_logo->setTag(ROUND_BLACK);
    CCSprite* white_logo = LogoView::create(&(this->chessboard->getCurrentMove()), cache->spriteFrameByName("white_logo.png"), WHITE);
    white_logo->setTag(ROUND_WHITE);
    this->addChild(black_logo);
    this->addChild(white_logo);
    
    // test font
//    CCLabelTTF* label = CCLabelTTF::create("Haha", "Helvetica-Bold", 32.0f);
//    label->setPosition(ccp(100, 100));
//    label->setColor(ccBLACK);
//    this->addChild(label);
    
    // touch

    return true;
}


void ChessboardController::onEnter()
{
    using cocos2d::CCDirector;
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChessboardController::tryEat), END_MOVE_MSG, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChessboardController::tryWin), END_EAT_MSG, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(ChessboardController::tryRegret), CLICK_REGRET_MSG, nullptr);
    
//    this->setTouchEnabled(true);
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCLayer::onEnter();
}

void ChessboardController::onExit()
{
    using cocos2d::CCDirector;
    
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
    
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

void ChessboardController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    logPoint(pTouch->getStartLocation());
    tryMove(RealToLogic(pTouch->getStartLocation()), RealToLogic(pTouch->getLocation()));
}

void ChessboardController::tryMove(const CCPoint& src, const CCPoint& dest){
    if (dest.equals(src))
        return;
    CCPoint newDest = (dest - src) / (dest - src).getLength() + src;
    Move move(chessboard->getCurrentMove().currentRound,src, newDest);
    if(chessboard->checkMessage(BEGIN_MOVE_MSG) && chessboard->checkMove(move)){
        chessboard->alterMove(move);
    }
    
}

void ChessboardController::tryEat(CCObject* o){
    
    Move move(chessboard->getCurrentMove());
    if(chessboard->checkMessage(BEGIN_EAT_MSG)){
        if (chessboard->checkEat(move)){
            chessboard->alterEat(move);
        }else{
            chessboard->alterNextRound();
        }
    }
}

void ChessboardController::tryWin(CCObject* o){
    if (chessboard->checkMessage(WIN_MSG)) {
        if (chessboard->checkWin(chessboard->getCurrentMove())){
            chessboard->alterWin();
            this->addChild(RotFlowerParticle::create());
        }else{
            chessboard->alterNextRound();
        }
    }
}

void ChessboardController::tryRegret(cocos2d::CCObject *o){
    if (chessboard->checkMessage(REGRET_MSG)){
        chessboard->alterRegret();
        
        CCString* frame_name = ( chessboard->getCurrentMove().currentRound == WHITE ) ? CCString::create("black.png") : CCString::create("white.png");
        
        for (CCPoint p : chessboard->getCurrentMove().eatenPoints) {
            CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
            CCSprite* piece = PieceView::create(&(this->chessboard->getCurrentMove()), this->chessboard, cache->spriteFrameByName(frame_name->getCString()), p);
            this->addChild(piece);
        }
    }
}
