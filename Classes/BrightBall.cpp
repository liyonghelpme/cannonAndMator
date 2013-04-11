#include "BrightBall.h"
BrightBall *BrightBall::create() {
    BrightBall *pRet = new BrightBall();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool BrightBall::init() {
    state = 0;
    passTime = 0;
    balls = CCArray::create();
    balls->retain();

    scheduleUpdate();
    return true;
}

void BrightBall::update(float dt) {
    passTime += dt;
    if(balls->count() < 10 && passTime >= 1.0) {
        int leftNum = 10-balls->count();
        for(int i = 0; i < leftNum; i++) {
            CCSprite *sp = CCSprite::create("ball2.png");
            addChild(sp);
            balls->addObject(sp);
            ccBlendFunc f = {GL_ONE, GL_ONE};
            sp->setBlendFunc(f);
            sp->setColor(ccc3(255, 255, 255));
            float rx = random()%10000/10000.*10-5;
            float ry = random()%10000/10000.*20;
            sp->setPosition(ccp(rx, ry));

            float rmx = random()%10000/10000.*2;
            if(rx < 0)
                rmx = -rmx;
            float rmy = random()%10000/10000.*2+20;

            sp->runAction(CCSequence::create(CCSpawn::create(CCFadeOut::create(0.8), CCScaleTo::create(1.0, 1.0), CCMoveBy::create(1.0, ccp(rmx, rmy)), NULL), CCCallFunc::create(this, callfunc_selector(BrightBall::removeBall)), NULL));
        }
        passTime = 0;
    } 
}
void BrightBall::removeBall(CCNode *ps) {
    CCNode *p = (CCNode*)balls->objectAtIndex(0);
    p->removeFromParent();
    balls->removeObjectAtIndex(0);
}

BrightBall::~BrightBall() {
    balls->release();
}
