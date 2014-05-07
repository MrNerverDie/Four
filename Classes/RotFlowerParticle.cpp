//
//  RotFlowerParticle.cpp
//  Four
//
//  Created by 王选易 on 14-5-7.
//
//

#include "RotFlowerParticle.h"

bool RotFlowerParticle::init(){
    
    CCParticleSnow::init();
    
    this->setTexture(CCTextureCache::sharedTextureCache()->addImage("star.png"));
    this->setEmissionRate(this->getTotalParticles() / this->getLife());
    this->setPosition(ccp(320, 1100));
    this->setLife(3);
    this->setLifeVar(1);
    this->setGravity(CCPointZero);
    this->setSpeed(130);
    this->setSpeedVar(30);
    
    // color of particles
    ccColor4F startColor = {0.5f, 0.5f, 0.5f, 1.0f};
    this->setStartColor(startColor);
    
    ccColor4F startColorVar = {0.5f, 0.5f, 0.5f, 1.0f};
    this->setStartColorVar(startColorVar);
    
    ccColor4F endColor = {0.1f, 0.1f, 0.1f, 0.2f};
    this->setEndColor(endColor);
    
    ccColor4F endColorVar = {0.1f, 0.1f, 0.1f, 0.2f};
    this->setEndColorVar(endColorVar);
    
    this->setScale(2.0);
    
    return true;
}