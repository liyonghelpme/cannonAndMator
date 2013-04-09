#ifndef __TIN_H__
#define __TIN_H__
#include "cocos2d.h"
using namespace cocos2d;
class Tin : public CCSprite {
public:
    static Tin *create();
    virtual bool init();

    kmVec2 velocity;
    float lifeTime;
    float passTime;
    virtual void update(float dt);
};
#endif
