#ifndef __SHELL_H__
#define __SHELL_H__
#include "cocos2d.h"
#include "Lightning.h"
using namespace cocos2d;
class Shell : public CCNode {
public:
    static Shell *create();
    void init();
    virtual void update(float dt);

    CCSprite *circle;
    CCMotionStreak *strike;

    CCArray *array;

    ~Shell();
    void removeCircle(CCNode*);
    void removeLight(CCNode*);

    CCArray *lightnings;
    CCArray *trails;// 世界坐标

    float radius;
    float picWidth;
    virtual void setPosition(const CCPoint &);

private:
    float passTime;
    float lightTime;
};
#endif
