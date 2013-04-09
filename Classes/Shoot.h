#ifndef __Shoot_H__
#define __Shoot_H__
#include "cocos2d.h"
#include "Bullet.h"
using namespace cocos2d;

class Shoot : public CCNode {
public:
    virtual bool init();
    static Shoot *create();
    virtual void update(float dt);

private:
    CCSprite *ani;
    float passTime;
    int curFrame;
    Bullet *bullet;
};
#endif
