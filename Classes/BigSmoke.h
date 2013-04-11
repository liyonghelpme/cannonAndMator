#ifndef __BigSmoke_H__
#define __BigSmoke_H__
#include "cocos2d.h"
using namespace cocos2d;

class BigSmoke : public CCNode {
public:
    virtual bool init();
    static BigSmoke *create();
    virtual void update(float dt);
    ~BigSmoke();

    void removeSmoke(CCNode *);
private:
    CCArray *smokes;
    int state;
    float passTime;
};
#endif
