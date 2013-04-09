#ifndef __Bullet_H__
#define __Bullet_H__
#include "cocos2d.h"
using namespace cocos2d;

class Bullet : public CCNode {
public:
    virtual bool init();
    static Bullet *create();
    virtual void update(float dt);
    ~Bullet();
    void removeBullet(CCNode *);

private:
    float passTime;
    CCArray *bullets;

};
#endif
