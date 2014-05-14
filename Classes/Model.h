//
//  Model.h
//  Four
//
//  Created by 王选易 on 14-4-21.
//
//

#ifndef __Four__Model__
#define __Four__Model__

#include <map>
#include <string>

using std::map;
using std::string;

#include "cocos2d.h"

using cocos2d::CCAction;
using cocos2d::CCNode;
using cocos2d::CCObject;
using cocos2d::CCString;

class Model : public CCObject {
    
private:
    map<string, map<string, string> > transitions;
    string currentState;
    bool async;
    
public:
    explicit Model(const string& _initial):currentState(_initial), async(false){}
    
    explicit Model(const string& _initial ,const map<string, map<string, string> >& _transitions):
        currentState(_initial),transitions(_transitions), async(false){}
    
    virtual ~Model(){}
    
    // 添加一条状态转换，from-起始状态，msg-接收的消息，to-终结状态，在msg发生时会发生状态转换
    Model* addTransition(const string& from, const string& msg, const string& to);
    
    // 检查当前状态机能否发生msg对应的状态转换
    bool checkMessage(const string& msg);
    
    // 触发msg对应的状态转换
    void onMessage(const string& msg);
    void onMessage(const string& msg, CCObject* o);
    
    // 等待某个CCAction结束后发送一条消息。
    void waitAction(cocos2d::CCNode* node, cocos2d::CCFiniteTimeAction* action, const string& msg);
    
    // 得到当前状态名称
    const char* getState();
    
    // callback
    void onAsyncMessage(CCNode* node , CCString* msg);
};

#endif /* defined(__Four__Model__) */
