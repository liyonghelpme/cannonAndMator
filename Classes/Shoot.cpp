#include "Shoot.h"
Shoot *Shoot::create() {
    Shoot *pRet = new Shoot();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool Shoot::init() {
    ani = CCSprite::create("s0.png");
    addChild(ani);
    ani->setAnchorPoint(ccp(0.5, 0));
    passTime = 0;
    curFrame = 0;
    scheduleUpdate();
    return true;
}

void Shoot::update(float dt) {
    if(curFrame == 0) {
        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("s0.png");
        ani->setTexture(pTexture);
        float ry = random()%10000/10000.*0.5+0.5;
        ani->setScaleY(ry);
    } else if(curFrame == 1 || curFrame == 2) {
        ani->setVisible(false);
    } else if(curFrame == 3){
        ani->setVisible(true);

        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("s1.png");
        ani->setTexture(pTexture);

        float ry = random()%10000/10000.*0.5+0.5;
        ani->setScaleY(ry);
    } else {
        curFrame = 0;
    }
    curFrame++;
}
