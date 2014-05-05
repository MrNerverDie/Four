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
    void onH2H();
    // 进行人机对战
    void onH2C();
    // 当点击帮助时
    void onHelp();
    // 当点击退出时
    void onEnd();
};



#endif /* defined(__Four__StartController__) */
