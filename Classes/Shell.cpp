#include "Shell.h"
#include "stdlib.h"
#include "math.h"
Shell *Shell::create(float l) {
    Shell *pRet = new Shell();
    pRet->init();
    pRet->lifeTime = l;
    pRet->countLife = 0;

    pRet->autorelease();
    return pRet;
}
void Shell::init() {
    state = 0;
    bombColor = ccc3(235, 3, 247);

    ball = CCNode::create();
    addChild(ball);

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
    scaleForBall = 1.0;


    strike = CCMotionStreak::create(1.0f, 64.0f, 64., bombColor, "circle2.png");
    strike->retain();

    scheduleUpdate();
    
}
//随机生成几个光圈
void Shell::update(float dt) {
    countLife += dt;
    if(state == 0)
    {
        passTime += dt;
        if(passTime >= 0.2 && array->count() < 10) {
            float rx = random()%10000/10000.;
            float ry = random()%10000/10000.;
            float rt = random()%10000/10000.;

            float sca = random()%10000/10000.*0.3+0.7;

            ccBlendFunc blend = {GL_ONE, GL_ONE};
            CCSprite *sp = CCSprite::create("shell.png");
            sp->setBlendFunc(blend);
            sp->setColor(bombColor);
            sp->setScale(0);
            sp->setPosition(ccp(rx*5, ry*5));
            sp->setRotation(rt*360);
            ball->addChild(sp);
            sp->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.5, sca*scaleForBall), CCFadeIn::create(0.5), NULL), CCDelayTime::create(0.3), CCFadeOut::create(0.5), CCCallFunc::create(this, callfunc_selector(Shell::removeCircle)), NULL));
            passTime -= 0.2;
            array->addObject(sp);
        }

        lightTime += dt;
        if(lightTime >= 0.2 && lightnings->count() <= 3) {
            int leftNum = 6 - lightnings->count();
            float difDeg = M_PI*2/leftNum;

            float deg = random()%10000/10000.;
            deg = deg*M_PI*2;

            for(int i = 0; i < leftNum; i++) {
                float rl = (random()%10000/10000.*radius/2+radius/2)*0.8;

                float dx = cos(deg+difDeg*i)*rl;
                float dy = sin(deg+difDeg*i)*rl;

                Lightning *light = Lightning::create(NULL, 20, 10, 40, 10);
                light->midDisplacement(0, 0, dx, dy, 20);
                ball->addChild(light, -1);
                 
                lightnings->addObject(light);
                light->runAction(CCSequence::create(CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(Shell::removeLight)) , NULL));
            }

            lightTime -= 0.2;
        }
    } else {
        //passTime += dt;

    }
}
void Shell::setRadius(float f) {
    radius = f;
    scaleForBall = radius*2/picWidth; 
}
void Shell::setRealPosition(const CCPoint& newPosition) {
    m_obPosition = newPosition;
    m_bTransformDirty = m_bInverseDirty = true;
}

//移动实际的球体 以及motionStreak 因为motion需要世界坐标来做
void Shell::setPosition(const CCPoint& newPosition)
{
    //m_obPosition = newPosition;
    //m_bTransformDirty = m_bInverseDirty = true;
    ball->setPosition(newPosition);
    strike->setPosition(newPosition);
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
    strike->release();
}
const CCPoint &Shell::getPosition() {
    return ball->getPosition();
}

CCParticleSystemQuad *Shell::bombStart(CCPoint &pos, float dir, float time){
    printf("bombStart\n");
    CCParticleSystemQuad *p = CCParticleSystemQuad::createWithTotalParticles(40);

    p->setEmissionRate(40/0.3);
    p->setDuration(time);

    p->setEmitterMode(kCCParticleModeRadius);
    p->setLife(0.3f);//越小运动越快
    p->setLifeVar(0.1);
    p->setStartSize(20);//根据具体图片
    p->setStartSizeVar(0);
    p->setEndSize(0);
    p->setEndSizeVar(0);

    p->setAngle(dir*180/kmPI+180); //根据炮口位置设定
    p->setAngleVar(100);//调整吸收空间能量的幅度

    p->setStartRadius(20);//根据炮的相对大小调整吸引范围的大小
    p->setStartRadiusVar(5);//根据炮的大小调整 幅度
    p->setEndRadius(3);
    p->setEndRadiusVar(2);
    p->setRotatePerSecond(0);//每秒旋转角度
    
    p->setPosition(pos); //炮口的位置
    //p->setSourcePosition(pos);

    ccColor4F c4 = ccc4FFromccc3B(bombColor);

    p->setStartColor(c4);
    p->setStartColorVar(ccc4f(0, 0, 0, 0.0));

    p->setEndColor(c4);
    p->setEndColorVar(ccc4f(0.1, 0.1, 0.1, 0.0));

    p->setBlendAdditive(true);
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("circle2.png");
    p->setTexture(pTexture);

    this->addChild(p);
    return p;
}
void Shell::bombFly(CCPoint &start, CCPoint &end, float flyTime) {
    ball->runAction(CCMoveTo::create(flyTime, end));
}
void Shell::bombEnd(CCPoint &end) {
    state = 1;
    passTime = 0;

    int leftNum = random()%3+8;
    float difDeg = M_PI*2/leftNum;

    float deg = random()%10000/10000.;
    deg = deg*M_PI*2;

    for(int i = 0; i < leftNum; i++) {
        float rx = random()%10000/10000.;
        float ry = random()%10000/10000.;
        float rt = random()%10000/10000.;

        float sca = random()%10000/10000.*0.3+0.7;

        float rl = (random()%10000/10000.*radius/2+radius/2)*5;

        float dx = cos(deg+difDeg*i)*rl;
        float dy = sin(deg+difDeg*i)*rl;

        ccBlendFunc blend = {GL_ONE, GL_ONE};
        CCSprite *sp = CCSprite::create("shell.png");
        sp->setBlendFunc(blend);
        sp->setColor(bombColor);
        sp->setScale(sca*scaleForBall);
        sp->setPosition(ccp(rx*5, ry*5));
        sp->setRotation(rt*360);
        ball->addChild(sp);


        sp->runAction(CCSequence::create(CCSpawn::create(CCMoveBy::create(1.0, ccp(dx, dy)), CCFadeOut::create(1.0), CCScaleTo::create(1.0, 0), NULL), NULL));
        array->addObject(sp);
    }


    for(int i = 0; i < leftNum; i++) {
        float rl = (random()%10000/10000.*radius/2+radius/2);

        float dx = cos(deg+difDeg*i)*rl*4;
        float dy = sin(deg+difDeg*i)*rl*4;

        float mx = cos(deg+difDeg*i)*rl*5;
        float my = sin(deg+difDeg*i)*rl*5;

        Lightning *light = Lightning::create(NULL, 20, 10, 40, 10);
        light->midDisplacement(0, 0, dx, dy, 20);
        ball->addChild(light, -1);
         
        lightnings->addObject(light);
        light->runAction(CCSequence::create(CCMoveBy::create(1.0, ccp(mx, my)) , NULL));
    }

}
