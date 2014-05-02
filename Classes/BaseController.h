//
//  BaseController.h
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#ifndef __Four__BaseController__
#define __Four__BaseController__

#include "cocos2d.h"

using namespace cocos2d;

class BaseController : public CCLayer {
    
public:
    bool init();
    CREATE_FUNC(BaseController);
    
};

#endif /* defined(__Four__BaseController__) */
