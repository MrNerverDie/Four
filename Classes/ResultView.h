//
//  ResultView.h
//  Four
//
//  Created by 王选易 on 14-5-11.
//
//

#ifndef __Four__ResultView__
#define __Four__ResultView__

#include "cocos2d.h"

using namespace cocos2d;

class ResultView : public CCLabelTTF {
    
public:
    ~ResultView();
    bool init();
    CREATE_FUNC(ResultView);
    
    void onWin(CCObject* o);
    void onLose(CCObject* o);
};

#endif /* defined(__Four__ResultView__) */
