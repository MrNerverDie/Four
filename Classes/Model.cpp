//
//  Model.cpp
//  Four
//
//  Created by 王选易 on 14-4-21.
//
//

#include "Model.h"

#include <algorithm>

Model* Model::addTransition(const string& from, const string& event, const string& to){
    map<string, string>& form_transitions = transitions[from];
    form_transitions[event] = to;
    return this;
}

void Model::onAsyncMessage(CCNode* node, CCString* msg){
    async = false;
    this->onMessage(msg->getCString());
    msg->release();
}

bool Model::checkMessage(const string &msg){
    return transitions[currentState].find(msg) != transitions[currentState].end();
}

void Model::onMessage(const string& msg){
    CCLOG("%s", msg.c_str());
    if (!async) {
        this->currentState = this->transitions[this->currentState][msg];
        CCLOG("transfer to State : %s", this->currentState.c_str());
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(msg.c_str());
    }
}

void Model::onMessage(const string &msg, CCObject* o){
    CCLOG("%s", msg.c_str());
    if (!async) {
        this->currentState = this->transitions[this->currentState][msg];
        CCLOG("transfer to State : %s", this->currentState.c_str());
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(msg.c_str(), o);
    }
}

void Model::waitAction(cocos2d::CCNode* node, cocos2d::CCFiniteTimeAction* action, const string& msg){
    using namespace cocos2d;
    async = true;
    CCString* cc_msg = CCString::create(msg);
    cc_msg->retain();
    CCFiniteTimeAction* action2 = CCCallFuncND::create(this, callfuncND_selector(Model::onAsyncMessage), (void *) cc_msg);
    CCSequence* sequence = CCSequence::createWithTwoActions(action, action2);
    node->runAction(sequence);
}

const char* Model::getState(){
    return this->currentState.c_str();
}
