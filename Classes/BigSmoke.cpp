#include "BigSmoke.h"
BigSmoke *BigSmoke::create() {
    BigSmoke *pRet = new BigSmoke();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool BigSmoke::init() {
    state = 0;
    passTime = 0;
    
    smokes = CCArray::create();
    smokes->retain();


    scheduleUpdate();
    return true;
}

void BigSmoke::update(float dt) {
    if(smokes->count() < 20) {
        CCSprite *sp = CCSprite::create("smoke.png");
        addChild(sp);
        smokes->addObject(sp);
        ccBlendFunc f = {GL_ONE, GL_ONE};
        sp->setBlendFunc(f);
        sp->setColor(ccc3(10, 10, 10));
        float rx = random()%10000/10000.*80-40;
        float ry = random()%10000/10000.*50;
        sp->setPosition(ccp(rx, ry));

        float rmx = random()%10000/10000.*40;
        if(rx < 0)
            rmx = -rmx;
        float rmy = random()%10000/10000.*80+20;

        sp->runAction(CCSequence::create(CCSpawn::create(CCFadeOut::create(1.0), CCScaleTo::create(1.0, 2), CCMoveBy::create(1.0, ccp(rmx, rmy)), NULL), CCCallFunc::create(this, callfunc_selector(BigSmoke::removeSmoke)), NULL));
    } 
}

BigSmoke::~BigSmoke() {
    smokes->release();
}

void BigSmoke::removeSmoke(CCNode *ps) {
    CCNode *p = (CCNode*)smokes->objectAtIndex(0);
    p->removeFromParent();
    smokes->removeObjectAtIndex(0);
}
