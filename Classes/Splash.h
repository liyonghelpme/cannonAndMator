#ifndef __SPLASH_H__
#define __SPLASH_H__
#include "cocos2d.h"
#include "stdlib.h"
#include "kazmath/utility.h"
#include "kazmath/vec3.h"
#include "kazmath/vec2.h"

//水泡是重力作用下的运动
//控制水泡的运动时间
//增加水泡的初始速度 较快发射

//blend 方式可以把水泡融合在一起 但是没有明显的水泡外在结构
using namespace cocos2d;
class MyParticle : public CCSprite {
public:
    static MyParticle *create();
    virtual bool init();
    
    virtual void update(float dt);
    kmVec2 velocity;
    float lifeTime;

    float passTime;

};


class Splash : public CCNode {
public:
    static Splash *create();
    void init();

    virtual void update(float dt);

    float passTime;
    bool go;
};



#endif
