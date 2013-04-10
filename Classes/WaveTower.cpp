#include "WaveTower.h"
WaveTower *WaveTower::create() {
    WaveTower *pRet = new WaveTower();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool WaveTower::init() {
    waves = CCArray::create();
    waves->retain();
    state = 0;
    passTime = 0;
    
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    scheduleUpdate();
    return true;
}

void WaveTower::draw() {
    CC_NODE_DRAW_SETUP();
    ccDrawSolidRect(ccp(-10, -10), ccp(10, 10), ccc4f(0.8, 0.8, 0.8, 1));
    ccDrawColor4F(1.0, 0.2, 0.3, 1);
    
    float vx = cos(dir)*15;
    float vy = sin(dir)*15;
    CCPoint d = ccp(vx, vy);

    ccDrawLine(ccp(0, 0), d);
    
    ccDrawColor4F(0, 0, 0, 0);
}

void WaveTower::update(float dt) {
    passTime += dt;
    if(state == 0) {
        float v = rand()*1.0/RAND_MAX;
        dir = v*kmPI*2;
        state = 1;
        passTime = 0;
    } else if(state == 1) {
        if(passTime >= 1) {
            CCPoint p = getPosition();
            float vx = cos(dir)*15; //炮弹口位置
            float vy = sin(dir)*15; 
            CCPoint d = ccp(p.x+vx, p.y+vy);

            ccColor3B color = ccc3(162, 10, 0);
            //ccc4f(0.63, 0.04, 0.06, 1.0)
            tail = CCMotionStreak::create(1.0f, 8.0f, 32., color, "tail.png");
            getParent()->addChild(tail);

            w = ParticleWave::create();
            getParent()->addChild(w);
            w->setPosition(d);
            w->setScale(0.4);
            
            //设置定点的尾巴

            w->tail = tail;
            
            w->bombStart(d, dir, 1.0);
            state = 2;
            passTime = 0;
        }
        float deg = random()%10000/10000.180+720;
    } else if(state == 2){
        if(passTime >= 1.0) {
            CCPoint p = getPosition();
            float vx = cos(dir); //炮弹口位置
            float vy = sin(dir); 
            CCPoint d = ccp(p.x+vx*15, p.y+vy*15);
            
            CCPoint e = ccp(p.x+vx*150, p.y+vy*150);

    //CCRotateBy::create(1.0, deg), CCScaleTo::create(1.0, 0.8), 
            //float deg = random()%10000/10000.180+720;
            w->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(2.0, e), NULL), CCFadeOut::create(1.0), NULL));
            //tail->runAction(CCMoveTo::create(2.0, e));
            w->bombFly(d, e, 1.0);

            state = 3;
            passTime = 0;
        }


    } else if(state == 3) {
        if(passTime >= 2) {
            w->bombEnd();

            state = 4;
            passTime = 0;
        }
    } else if(state == 4) {
        if(passTime >= 1) {
            w->removeFromParent();
            tail->removeFromParent();
            state = 0;
            passTime = 0;
        }
    }
}

WaveTower::~WaveTower() {
    waves->release();
}
