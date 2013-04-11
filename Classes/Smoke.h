#ifndef __Smoke_H__
#define __Smoke_H__
#include "cocos2d.h"
using namespace cocos2d;

class Smoke : public CCNode {
public:
    virtual bool init();
    static Smoke *create();
    virtual void update(float dt);
    ~Smoke();
    void removeSmoke(CCNode *);
private:
    CCArray *smokes;
};
#endif
