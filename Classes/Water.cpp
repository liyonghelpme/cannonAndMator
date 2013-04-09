#include "Water.h"
Water *Water::create() {
    Water *pRet = new Water();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void Water::init() {
    kmVec2Fill(&velocity, 0, 0);
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    //scheduleUpdate();
    targetHeight = 150;
}
void Water::draw() {
    CC_NODE_DRAW_SETUP();
    ccDrawSolidRect(ccp(-10, -10), ccp(10, 10), ccc4f(0.8, 0.8, 0.8, 1));
    
    ccDrawColor4F(0, 0, 0, 0);
}
void Water::update(float dt) {

    float k = 2*M_PI;
    CCPoint old = getPosition();
    float x = old.y-targetHeight;
    float dampening = k/100.;
    float acc = -k*x-velocity.y*dampening;
    
    old.x += velocity.x*dt;
    old.y += velocity.y*dt;

    setPosition(old);

    velocity.y += acc*dt;

}

