#include "Mortar.h"
Mortar *Mortar::create() {
    Mortar *pRet = new Mortar();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void Mortar::init() {
    state = 0;
    passTime = 0;
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    scheduleUpdate();
}
//大炮3个状态
//聚集能量
//发射炮弹
//炮弹爆炸

//setRadius 可以设定发射炮弹的尺寸大小
void Mortar::update(float dt) {
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

            shell = Shell::create(1);
            getParent()->addChild(shell); 
            shell->setRadius(20);
            shell->setPosition(d);
            shell->bombStart(d, dir, 1.0);
            
            passTime = 0;
            state = 2;
        }
    } else if(state == 2) {
        if(passTime >= 1) {

            CCPoint p = getPosition();
            float vx = cos(dir); //炮弹口位置
            float vy = sin(dir); 
            CCPoint d = ccp(p.x+vx*15, p.y+vy*15);
            CCPoint e = ccp(p.x+vx*200, p.y+vy*200);
            shell->bombFly(d, e, 5.0);
            /*
            ccBezierConfig conf;

            conf.controlPoint_1 = ccp(100, 100);
            conf.controlPoint_2 = ccp(200, 100);
            conf.endPosition = ccp(300, 100);
            
            shell->runAction(CCBezierBy::create(1, conf)); 
            */
            
            state = 3;
            passTime = 0;
        }
    } else if(state == 3) {
        if(passTime >= 5.) {
            state = 4;
            passTime = 0;

            CCPoint p = getPosition();//攻击中点
            float vx = cos(dir); //炮弹口位置
            float vy = sin(dir); 
            CCPoint e = ccp(p.x+vx*200, p.y+vy*200);
            shell->bombEnd(e);
        }
    } else if(state == 4) {
        if(passTime >= 1.0) {
            shell->removeFromParent();
            state = 0;
            passTime = 0;
        }
    }
}

void Mortar::draw() {
    CC_NODE_DRAW_SETUP();
    ccDrawSolidRect(ccp(-10, -10), ccp(10, 10), ccc4f(0.8, 0.8, 0.8, 1));
    ccDrawColor4F(1.0, 0.2, 0.3, 1);
    
    float vx = cos(dir)*15;
    float vy = sin(dir)*15;
    CCPoint d = ccp(vx, vy);

    ccDrawLine(ccp(0, 0), d);
    
    ccDrawColor4F(0, 0, 0, 0);
}
