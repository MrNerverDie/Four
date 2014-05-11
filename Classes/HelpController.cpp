//
//  HelpController.cpp
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#include "HelpController.h"
#include "Tag.h"
#include "Chessboard.h"
#include "StartScene.h"
#include "PieceView.h"

HelpController::~HelpController(){
    CC_SAFE_RETAIN(intros);
}

bool HelpController::init(){
    BaseController::init();
    
    intros = CCArray::create();
    CC_SAFE_RETAIN(intros);

    
    intros->addObject(CCString::create(""));
    PIECE pieces1[HEIGHT][WIDTH] = {
        {ZERO, BLACK, ZERO, WHITE},
        {ZERO, ZERO, BLACK, ZERO},
        {ZERO, ZERO, ZERO, ZERO},
        {ZERO, ZERO, ZERO, ZERO}
    };
    ChessboardData data1;
    Pieces2Data(pieces1, data1);
    datas.push_back(data1);
    moves.push_back(Move(BLACK, ccp(2, 1), ccp(2, 0)));
    
    intros->addObject(CCString::create(""));
    PIECE pieces2[HEIGHT][WIDTH] = {
        {ZERO, BLACK, BLACK, ZERO},
        {ZERO, ZERO, ZERO, WHITE},
        {ZERO, ZERO, ZERO, ZERO},
        {ZERO, ZERO, ZERO, ZERO}
    };
    ChessboardData data2;
    Pieces2Data(pieces2, data2);
    datas.push_back(data2);
    moves.push_back(Move(WHITE, ccp(3, 1), ccp(3, 0)));
    
    this->chessboard = Chessboard::create();
    CC_SAFE_RETAIN(this->chessboard);
    chessboard->setPieces(datas[0]);
    ChessboardController::initPieceViews();
    
    progress = 0;
    
    return true;
}

void HelpController::onEnter(){
    ChessboardController::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, END_EAT_MSG);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HelpController::tryWin), END_EAT_MSG, nullptr);
}

void HelpController::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event){
    progress++;
    if (progress < (moves.size() * 2) ) {
        int index = progress / 2;
        if (progress % 2 != 0) {
            chessboard->setCurrentMove(moves[index]);
            tryMove(moves[index].src, moves[index].dest);
        }else{
            chessboard->setPieces(datas[index]);
            this->initPieceViews();
        }
    }else{
        StartScene* scene = StartScene::create();
        CCTransitionSlideInR* slide = CCTransitionSlideInR::create(0.3, scene);
        CCDirector::sharedDirector()->replaceScene(slide);
    }

}

void HelpController::tryWin(){
    if (chessboard->checkMessage(WIN_MSG)) {
        chessboard->alterNextRound();
    }
}