#include "Gunner.h"
Gunner *Gunner::create() {
    Gunner *pRet = new Gunner();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool Gunner::init() {
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    passTime = 0;
    dir = 0;

    gun = Gun::create();
    addChild(gun);
    float vx = cos(dir)*15; //炮弹口位置
    float vy = sin(dir)*15; 
    CCPoint d = ccp(vx, vy);
    gun->setPosition(d);
    gun->setAnchorPoint(ccp(0, 0.5));

    scheduleUpdate();

    return true;
}
//旋转炮口 也旋转 火焰 方向
void Gunner::update(float dt) {
    passTime += dt;
    if(passTime >= 1.0) {
        float v = rand()*1.0/RAND_MAX;
        dir = v*kmPI*2;

        float vx = cos(dir)*15; //炮弹口位置
        float vy = sin(dir)*15; 
        CCPoint d = ccp(vx, vy);
        gun->setPosition(d);

        gun->setRotation(-dir*180/kmPI);

        passTime = 0;
    }

}
void Gunner::draw() {
    CC_NODE_DRAW_SETUP();
    ccDrawSolidRect(ccp(-10, -10), ccp(10, 10), ccc4f(0.8, 0.8, 0.8, 1));
    ccDrawColor4F(1.0, 0.2, 0.3, 1);
    
    float vx = cos(dir)*15;
    float vy = sin(dir)*15;
    CCPoint d = ccp(vx, vy);

    ccDrawLine(ccp(0, 0), d);
    
    ccDrawColor4F(0, 0, 0, 0);
}
