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
    
    Model* addTransition(const string& from, const string& event, const string& to);
    
    bool checkMessage(const string& msg);
    
    void onMessage(const string& msg);
    
    void onAsyncMessage(const string& msg);
    
    void waitAction(cocos2d::CCNode* node, cocos2d::CCFiniteTimeAction* action, const string& msg);
    
    const char* getState();
};

#endif /* defined(__Four__Model__) */
