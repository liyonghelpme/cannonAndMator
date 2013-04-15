#ifndef __Fog_H__
#define __Fog_H__
#include "cocos2d.h"
using namespace cocos2d;

class Fog : public CCNode {
public:
    virtual bool init();
    static Fog *create();
    virtual void update(float dt);
    ~Fog();

    void initFogPos();
    void initBigFog();
    void initMoveFog();
private:
    CCArray *fogs;
};
#endif
