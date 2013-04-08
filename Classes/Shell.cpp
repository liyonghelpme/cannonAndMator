#include "Shell.h"
#include "stdlib.h"
#include "math.h"
Shell *Shell::create() {
    Shell *pRet = new Shell();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void Shell::init() {
    array = CCArray::create();
    array->retain();
    lightnings = CCArray::create();
    lightnings->retain();
    trails = CCArray::create();
    trails->retain();

    passTime = 0;
    lightTime = -0.5;

    radius = 32;
    picWidth = 64;

    /*
    circle = CCSprite::create("range_circle.png");
    addChild(circle);
    strike = CCMotionStreak::create(1.0f, 16.0f, 16., ccc3(235, 3, 247), "range_circle.png");
    addChild(strike);

    CCMoveBy *mb = CCMoveBy::create(1, ccp(200, 200));
    circle->runAction(CCRepeatForever::create(CCSequence::create(mb, mb->reverse(), NULL)));
    */

    scheduleUpdate();
    
}
//随机生成几个光圈
void Shell::update(float dt) {
    passTime += dt;
    if(passTime >= 0.3) {
        float rx = random()%10000/10000.;
        float ry = random()%10000/10000.;
        float rt = random()%10000/10000.;

        ccBlendFunc blend = {GL_ONE, GL_ONE};
        CCSprite *sp = CCSprite::create("shell.png");
        sp->setBlendFunc(blend);
        sp->setColor(ccc3(235, 3, 247));
        sp->setScale(0);
        sp->setPosition(ccp(rx*5, ry*5));
        sp->setRotation(rt*360);
        addChild(sp);
        sp->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.5, 1), CCFadeIn::create(0.5), NULL), CCDelayTime::create(0.3), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(Shell::removeCircle)), NULL));
        passTime -= 0.3;
        array->addObject(sp);
    }

    lightTime += dt;
    if(lightTime >= 0.2 && lightnings->count() <= 3) {
        int leftNum = 6 - lightnings->count();
        float difDeg = M_PI*2/leftNum;

        float deg = random()%10000/10000.;
        deg = deg*M_PI*2;

        for(int i = 0; i < leftNum; i++) {
            float rl = random()%10000/10000.*radius/2+radius/2;

            float dx = cos(deg+difDeg*i)*rl;
            float dy = sin(deg+difDeg*i)*rl;

            Lightning *light = Lightning::create(NULL, 20, 10, 40, 10);
            light->midDisplacement(0, 0, dx, dy, 20);
            addChild(light, -1);
             
            lightnings->addObject(light);
            light->runAction(CCSequence::create(CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(Shell::removeLight)) , NULL));
        }

        lightTime -= 0.2;
    }

    
}

void CCNode::setPosition(const CCPoint& newPosition)
{
    m_obPosition = newPosition;
    m_bTransformDirty = m_bInverseDirty = true;
}

void Shell::removeCircle(CCNode *pSender) {
    CCSprite *sp = (CCSprite*)array->objectAtIndex(0);
    sp->removeFromParent();
    array->removeObjectAtIndex(0);
}
void Shell::removeLight(CCNode *pSender) {
    CCNode *light = (CCNode*)lightnings->objectAtIndex(0);
    light->removeFromParent();
    lightnings->removeObjectAtIndex(0);
}

Shell::~Shell() {
    array->release();
    lightnings->release();
    trails->release();
}
