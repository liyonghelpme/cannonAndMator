#include "ParticleWave.h"
ParticleWave *ParticleWave::create() {
    CCLog("create ParticleWave");
    ParticleWave *pRet = new ParticleWave();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool ParticleWave::init() {
    passTime = 0;

    initWithFile("circleParticle.png");
    ccBlendFunc f = {GL_ONE, GL_ONE};
    //setBlendFunc(f);


    shadow = CCArray::create();
    shadow->retain();
    CCSize sz = getContentSize();
    CCLog("init wave %f %f", sz.width, sz.height);
    for(int i = 0; i < 3; i++) {
        CCSprite *sp = CCSprite::create("circleParticle.png");
        addChild(sp, -1);
        sp->setBlendFunc(f);
        float dx = random()%10000/10000.*10-5;
        float dy = random()%10000/10000.*10-5;
        sp->setPosition(ccp(sz.width/2+dx, sz.height/2+dy));
        CCLog("set Position %f %f", sp->getPosition().x, sp->getPosition().y);
        shadow->addObject(sp);
    }

    scheduleUpdate();
    return true;
}

void ParticleWave::update(float dt) {
    passTime += dt;
    if(passTime >= 0.05) {
        CCSize sz = getContentSize();
        for(unsigned int i = 0; i < shadow->count(); i++) {
            CCSprite *sp = (CCSprite*)shadow->objectAtIndex(i);
            float dx = random()%10000/10000.*5-2;
            float dy = random()%10000/10000.*5-2;
            sp->setPosition(ccp(sz.width/2+dx, sz.height/2+dy));
        }
        passTime -= 0.05;
    }
}


ParticleWave::~ParticleWave() {
    shadow->release();
}


