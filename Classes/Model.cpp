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

void Model::onAsyncMessage(const string& msg){
    async = false;
    this->onMessage(msg);
}

bool Model::checkMessage(const string &msg){
    return transitions[currentState].find(msg) != transitions[currentState].end();
}

void Model::onMessage(const string& msg){
    if (!async) {
        cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(msg.c_str());
        this->currentState = this->transitions[this->currentState][msg];
    }
}

void Model::waitAction(cocos2d::CCNode* node, cocos2d::CCFiniteTimeAction* action, const string& msg){
    using namespace cocos2d;
    async = true;
    CCFiniteTimeAction* action2 = CCCallFuncND::create(this, callfuncND_selector(Model::onAsyncMessage), (void *) &msg);
    CCSequence* sequence = CCSequence::createWithTwoActions(action, action2);
    node->runAction(sequence);
}

const char* Model::getState(){
    return this->currentState.c_str();
}
