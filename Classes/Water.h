#ifndef __WATER_H__
#define __WATER_H__
#include "cocos2d.h"
#include "kazmath/utility.h"
#include "kazmath/vec3.h"
#include "kazmath/vec2.h"

using namespace cocos2d;
class Water : public CCNode {
public:
    static Water *create();
    void init();
    kmVec2 velocity;
    float targetHeight;
    
    virtual void draw();
    virtual void update(float dt);
};
#endif
