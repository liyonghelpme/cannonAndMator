#include "Splash.h"

MyParticle *MyParticle::create() {
    MyParticle *p = new MyParticle();
    p->init();
    p->autorelease();
    return p;
}
//飞起的气泡主要是 初始速度 和 重力
//控制运动时间 和 运动位移
//调整速度 和 重力

//运动时间 2s 最高点 1s
//初始速度 200 加速度 200
//位移 = 200/2*t = 100

//水泡消失时间 1.5
bool MyParticle::init() {
    initWithFile("newDrop.png");
    kmVec2Fill(&velocity, 0, 0);
    lifeTime = 1+random()%10000/10000.*0.5;
    passTime = 0;

    //setBlendFunc(f);

    setColor(ccc3(50, 128, 255));
    float sca = random()%10000/10000.*0.5+0.5;
    setScale(sca*.5);
    runAction(CCFadeOut::create(lifeTime));

    ccBlendFunc f = {GL_ONE, GL_ONE};
    CCSprite *meta = CCSprite::create("newWater.png");
    addChild(meta);
    meta->setBlendFunc(f);
    meta->setColor(ccc3(50, 128, 255));
    CCSize sz = getContentSize();
    meta->setPosition(ccp(sz.width/2, sz.height/2));
    meta->setScale(3);

    scheduleUpdate();
    return true;
}

void MyParticle::update(float dt) {
    float gravity = -200;
    velocity.y += gravity*dt;
    CCPoint old = getPosition();
    old.x += velocity.x*dt;
    old.y += velocity.y*dt;
    setPosition(old);

    float deg = -180/M_PI*atan2(velocity.y, velocity.x);
    setRotation(deg);

    if(passTime >= lifeTime){
        removeFromParent();
    }

    passTime += dt;
}



Splash *Splash::create() {
    Splash *p = new Splash();
    p->init();
    p->autorelease();
    return p;
}

void Splash::init() {
    passTime = 0;
    scheduleUpdate();
    go = true;
}

void Splash::update(float dt) {
    passTime += dt;
    if(passTime >= 1.0) {
        for(int i = 0; i < 20; i++) {
            MyParticle *p = MyParticle::create();
            float rw = random()%10000/10000.*10;
            float rh = random()%10000/10000.*10;
            p->setPosition(ccp(100+rw, 150+rh));
            addChild(p);
            float rx = random()%10000/10000.*200-100;
            //float rx = 200;
            float ry = random()%10000/10000.*100+200;
            kmVec2Fill(&p->velocity, rx, ry);


        }
        go = false;
        passTime = 0;
    }
}
