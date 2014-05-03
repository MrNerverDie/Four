//
//  MenuController.h
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#ifndef __Four__MenuController__
#define __Four__MenuController__

#include "cocos2d.h"

using namespace cocos2d;

class MenuController : public CCLayer{
    
public:
    bool init();
    CREATE_FUNC(MenuController);
    
    void onBack();
};


#endif /* defined(__Four__MenuController__) */

