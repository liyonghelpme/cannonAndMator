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
    state = 0;

    detail = CCSprite::create("circleParticle.png");
    addChild(detail);

    detail->runAction(CCRepeatForever::create(CCRotateBy::create(0.5, 360)));

    //initWithFile("circleParticle.png");
    ccBlendFunc f = {GL_ONE, GL_ONE};
    //setBlendFunc(f);
    tail = NULL;



    shadow = CCArray::create();
    shadow->retain();
    //CCSize sz = getContentSize();
    //CCLog("init wave %f %f", sz.width, sz.height);
    for(int i = 0; i < 3; i++) {
        CCSprite *sp = CCSprite::create("circleParticle.png");
        addChild(sp, -1);
        sp->setBlendFunc(f);
        float dx = random()%10000/10000.*10-5;
        float dy = random()%10000/10000.*10-5;
        sp->setPosition(ccp(dx, dy));
        CCLog("set Position %f %f", sp->getPosition().x, sp->getPosition().y);
        shadow->addObject(sp);
        sp->runAction(CCRepeatForever::create(CCRotateBy::create(0.5, 360)));
    }

    sun = CCParticleSun::createWithTotalParticles(20);
    sun->setPositionType(kCCPositionTypeRelative);
    addChild(sun);
    //sun->setPosition(ccp(sz.width/2, sz.height/2));
    sun->setPosition(ccp(0, 0));
    CCTexture2D *pt = CCTextureCache::sharedTextureCache()->addImage("wavePoint.png");
    sun->setTexture(pt);
    sun->setStartSize(64);
    sun->setStartColor(ccc4f(0.63, 0.04, 0.06, 1.0));
    sun->setSpeed(30);

    scheduleUpdate();
    return true;
}
void ParticleWave::setPosition(const CCPoint &newPosition) {
    m_obPosition = newPosition;
    m_bTransformDirty = m_bInverseDirty = true;
    if(tail != NULL) {
        tail->setPosition(newPosition);
    }
}

void ParticleWave::update(float dt) {
    if(state == 0) {
    passTime += dt;
        //CCSize sz = getContentSize();
        for(unsigned int i = 0; i < shadow->count(); i++) {
            CCSprite *sp = (CCSprite*)shadow->objectAtIndex(i);
            float dx = random()%10000/10000.*20-10;
            float dy = random()%10000/10000.*20-10;
            sp->setPosition(ccp(dx, dy));
        }
    }
}


ParticleWave::~ParticleWave() {
    shadow->release();
}


void ParticleWave::bombEnd() {
    state = 1;
    sun->setSpeed(100);
    sun->setLife(0.1);
    detail->runAction(CCFadeOut::create(0.8));

    int leftNum = shadow->count();
    float difDeg = M_PI*2/leftNum;
    float deg = random()%10000/10000.;
    deg = deg*M_PI*2;
    for(unsigned int i = 0; i < shadow->count(); i++){

        float rx = random()%10000/10000.;
        float ry = random()%10000/10000.;
        float rt = random()%10000/10000.;

        float sca = random()%10000/10000.*0.3+0.7;

        float rl = (random()%10000/10000.*32+16)*5;

        float dx = cos(deg+difDeg*i)*rl;
        float dy = sin(deg+difDeg*i)*rl;

        CCSprite *sp = (CCSprite*)shadow->objectAtIndex(i);
        sp->setScale(sca);
        sp->setPosition(ccp(rx*5, ry*5));
        sp->setRotation(rt*360);

        sp->runAction(CCSequence::create(CCSpawn::create(CCMoveBy::create(1.0, ccp(dx, dy)), CCFadeOut::create(1.0), CCScaleTo::create(1.0, 0), NULL), NULL));
    }
}
