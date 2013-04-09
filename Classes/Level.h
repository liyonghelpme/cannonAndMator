#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "cocos2d.h"
#include "Water.h"
#include "stdlib.h"

using namespace cocos2d;

class Level : public CCNode {
public:
    static Level *create();
    void init();
    ~Level(); 

    virtual void update(float dt);

private:
    CCArray *waterBlock;    
    float *leftDelta;
    float *rightDelta;
};
#endif
