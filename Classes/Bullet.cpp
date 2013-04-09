#include "Bullet.h"
Bullet *Bullet::create() {
    Bullet *pRet = new Bullet();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool Bullet::init() {
    passTime = 0;
    bullets = CCArray::create();
    bullets->retain();
    scheduleUpdate();
    return true;
}

//向上攻击 子弹向两侧发射
//子弹飘出的 Bezier 曲线形式
void Bullet::update(float dt) {
    passTime += dt;
    if(bullets->count() < 10 && passTime >= 0.2) {
        CCSprite *s = CCSprite::create("cartridge.png");
        addChild(s);
        float sx = random()%10000/10000.*10;
        float sy = random()%10000/10000.*10;
        s->setPosition(ccp(sx, sy));

        ccBezierConfig conf;
        
        

        float rx = random()%10000/10000.*100+50;
        float ry = random()%10000/10000.*20+20;

        float x0 = rx/3.;
        conf.controlPoint_1 = ccp(x0, ry);

        ry = random()%10000/10000.*20+20;
        float x1 = rx/3.*2;
        conf.controlPoint_2 = ccp(x1, ry);

        ry = random()%10000/10000.*50;
        conf.endPosition = ccp(rx, ry);
        
        float sca = random()%10000/10000.*0.3+0.7;
        s->setScale(sca);

        float deg = random()%10000/10000.*200+200;
        s->runAction(CCSequence::create(CCSpawn::create(CCRotateBy::create(1, deg), CCBezierBy::create(0.5, conf), CCFadeOut::create(0.5),  NULL), CCCallFunc::create(this, callfunc_selector(Bullet::removeBullet)), NULL)); 

        bullets->addObject(s);

        passTime = 0;
    }

}
void Bullet::removeBullet(CCNode *p) {
    CCNode *b = (CCNode*)bullets->objectAtIndex(0);
    b->removeFromParent();
    bullets->removeObjectAtIndex(0);

}
Bullet::~Bullet() {
    bullets->release();
}
