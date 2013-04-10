#ifndef __ParticleWave_H__
#define __ParticleWave_H__
#include "cocos2d.h"
using namespace cocos2d;


class ParticleWave : public CCSprite {
public:
    virtual bool init();
    static ParticleWave *create();
    virtual void update(float dt);
    ~ParticleWave();
private:
    CCArray *shadow;
    float passTime;
};
#endif
