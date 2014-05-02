//
//  ImageButton.h
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#ifndef __Four__ImageButton__
#define __Four__ImageButton__

#include "cocos2d.h"

using namespace cocos2d;

class ImageButton : public CCMenuItemSprite {
    
public:
    void onEnter();
    void onExit();
    
    static ImageButton* create(CCNode* sprite, CCObject* target, SEL_MenuHandler selector);
    
};

#endif /* defined(__Four__ImageButton__) */
