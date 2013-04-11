#ifndef __BrightBall_H__
#define __BrightBall_H__
#include "cocos2d.h"
using namespace cocos2d;

class BrightBall : public CCNode {
public:
    virtual bool init();
    static BrightBall *create();
    virtual void update(float dt);
    ~BrightBall();
private:
    CCArray *balls;
    void removeBall(CCNode *);
    int state;
    float passTime;
};
#endif
