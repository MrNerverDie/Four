//
//  StartController.h
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#ifndef __Four__StartController__
#define __Four__StartController__

#include "BaseController.h"

#include "cocos2d.h"

using namespace cocos2d;

class StartController : public BaseController {
    
public:
    bool init();
    CREATE_FUNC(StartController);
    
    // 进行人人对战
    void onH2H(CCObject* o);
    // 进行人机对战
    void onH2C(CCObject* o);
    // 当固定时间进行人机对战时
    void onFixTime(CCObject* o);
    // 当固定步数进行人机对战时
    void onFixMove(CCObject* o);
};



#endif /* defined(__Four__StartController__) */
