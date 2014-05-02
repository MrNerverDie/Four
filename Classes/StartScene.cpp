//
//  StartScene.cpp
//  Four
//
//  Created by 王选易 on 14-5-2.
//
//

#include "StartScene.h"
#include "StartController.h"

bool StartScene::init(){
    CCScene::init();
    
    StartController* sc = StartController::create();
    this->addChild(sc);
    
    return true;
}