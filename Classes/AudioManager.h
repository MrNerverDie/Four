//
//  AudioManager.h
//  Four
//
//  Created by 王选易 on 14-5-6.
//
//

#ifndef __Four__AudioManager__
#define __Four__AudioManager__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using cocos2d::CCObject;
using cocos2d::CCNotificationCenter;
using CocosDenshion::SimpleAudioEngine;
using cocos2d::CCString;
using cocos2d::CCDictionary;
using cocos2d::CCFileUtils;

class AudioManager : public CCObject {
private:
    CCDictionary* msg2audio;
    
public:
    virtual ~AudioManager();
    bool init();
    CREATE_FUNC(AudioManager);
    
    void play(CCString* str);
    void pause();
    void resume();
    
};

#endif /* defined(__Four__AudioManager__) */
