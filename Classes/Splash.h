#ifndef __SPLASH_H__
#define __SPLASH_H__
#include "cocos2d.h"
#include "stdlib.h"
#include "kazmath/utility.h"
#include "kazmath/vec3.h"
#include "kazmath/vec2.h"

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
