#include "Tin.h"
Tin *Tin::create() {
    Tin *p = new Tin();
    p->init();
    p->autorelease();
    return p;
}
bool Tin::init() {
    lifeTime = 1+random()%10000/10000.*0.5;
    passTime = 0;

    float sca = random()%10000/10000.*0.5+0.5;
    setScale(sca*.5);

    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("guantou_normal.plist");
    cache->addSpriteFramesWithFile("guantou_tilt.plist");

    initWithSpriteFrameName("guantou_normal1.png");
    
    int ani = random()%2;
    
    CCArray *aniFrames = CCArray::create();
    char str[100];
    for(int i = 1; i < 10; i++) {
        if(ani == 0)
            sprintf(str, "guantou_normal%d.png", i);
        else
            sprintf(str, "guantou_tilt%d.png", i);
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
        aniFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(aniFrames, 0.1f);


    runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    runAction(CCSequence::create(CCDelayTime::create(0.5), CCFadeOut::create(lifeTime), NULL));

    scheduleUpdate();

    return true;
}
void Tin::update(float dt) {
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
