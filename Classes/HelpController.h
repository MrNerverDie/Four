//
//  HelpController.h
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#ifndef __Four__HelpController__
#define __Four__HelpController__

#include "ChessboardController.h"
#include "ChessboardProtocol.h"

#include "cocos2d.h"

#include <vector>

using namespace cocos2d;

class HelpController : public ChessboardController {
private:
    CCArray* intros;
    std::vector<ChessboardData> datas;
    std::vector<Move> moves;
    int progress;
    
public:
    ~HelpController();
    bool init();
    CREATE_FUNC(HelpController);
    
    void onEnter();
    
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void tryWin();
};

#endif /* defined(__Four__HelpController__) */
