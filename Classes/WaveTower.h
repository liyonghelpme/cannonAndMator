#ifndef __WaveTower_H__
#define __WaveTower_H__
#include "cocos2d.h"
using namespace cocos2d;

class WaveTower : public CCNode {
public:
    virtual bool init();
    static WaveTower *create();
    virtual void update(float dt);
    ~WaveTower();
};
#endif
