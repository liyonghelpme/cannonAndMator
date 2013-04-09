#ifndef __GUN_H__
#define __GUN_H__
#include "cocos2d.h"
using namespace cocos2d;

class Gun : public CCNode {
public:
    virtual bool init();
    static Gun *create();

    virtual void update(float dt);
    ~Gun();

    void removeLine(CCNode *);
private:
    CCArray *lines;
    float passTime;
};
#endif
