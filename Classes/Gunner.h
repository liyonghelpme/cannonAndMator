#ifndef __GUNNER_H__
#define __GUNNER_H__
#include "cocos2d.h"
#include "Gun.h"
using namespace cocos2d;


class Gunner : public CCNode {
public:
    virtual bool init();
    static Gunner *create();
    virtual void draw();
    virtual void update(float dt);

    float passTime;
    float dir;
private:
    Gun *gun;
};
#endif
