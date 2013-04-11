#include "Smoke.h"
Smoke *Smoke::create() {
    Smoke *pRet = new Smoke();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool Smoke::init() {
    smokes = CCArray::create();
    smokes->retain();

    scheduleUpdate();
    return true;
}

void Smoke::update(float dt) {
    if(smokes->count() < 5) {
        CCSprite *sp = CCSprite::create("smoke.png");
        addChild(sp);
        smokes->addObject(sp);
        ccBlendFunc f = {GL_ONE, GL_ONE};
        sp->setBlendFunc(f);
        sp->setColor(ccc3(10, 10, 10));
        float rx = random()%10000/10000.*40-20;
        float ry = random()%10000/10000.*10-5;
        sp->setPosition(ccp(rx, ry));

        float rmx = random()%10000/10000.*20+5;
        if(rx < 0)
            rmx = -rmx;
        float rmy = random()%10000/10000.*40+20;

        sp->runAction(CCSequence::create(CCSpawn::create(CCFadeOut::create(1.0), CCScaleTo::create(1.0, 2), CCMoveBy::create(1.0, ccp(rmx, rmy)),  NULL),  CCCallFunc::create(this, callfunc_selector(Smoke::removeSmoke)), NULL));
    } 
}

void Smoke::removeSmoke(CCNode *ps) {
    CCNode *p = (CCNode*)smokes->objectAtIndex(0);
    p->removeFromParent();
    smokes->removeObjectAtIndex(0);
}
Smoke::~Smoke() {
    smokes->release();
}
