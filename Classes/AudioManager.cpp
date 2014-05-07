//
//  AudioManager.cpp
//  Four
//
//  Created by 王选易 on 14-5-6.
//
//

#include "AudioManager.h"
#include "Message.h"

AudioManager::~AudioManager(){
    CC_SAFE_RELEASE(msg2audio);
}

bool AudioManager::init(){
    using namespace cocos2d;
    
    msg2audio = cocos2d::CCDictionary::create();
    CC_SAFE_RETAIN(msg2audio);
    CCFileUtils::sharedFileUtils()->addSearchPath("audio/");
    
    msg2audio->setObject(CCStringMake("move.WAV"), BEGIN_MOVE_MSG);
    msg2audio->setObject(CCStringMake("eat.WAV"), BEGIN_EAT_MSG);
    msg2audio->setObject(CCStringMake("next_round.WAV"), NEXT_ROUND_MSG);
    msg2audio->setObject(CCStringMake("click.WAV"), CLICK_MSG);
//    msg2audio->setObject(CCStringMake("create.WAV"), CREATE_MSG);
    
    CCDictElement* e = nullptr;
    CCDICT_FOREACH(msg2audio, e){
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(AudioManager::play), e->getStrKey(), e->getObject());
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(((CCString *)e->getObject())->getCString());
    }
    
    return true;
}

void AudioManager::play(cocos2d::CCString *str){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(str->getCString());
}

void AudioManager::pause(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

void AudioManager::resume(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}