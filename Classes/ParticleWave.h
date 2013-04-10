#ifndef __ParticleWave_H__
#define __ParticleWave_H__
#include "cocos2d.h"
using namespace cocos2d;


class ParticleWave : public CCNode {
public:
    virtual bool init();
    static ParticleWave *create();
    virtual void update(float dt);
    ~ParticleWave();
    CCMotionStreak *tail;
    virtual void setPosition(const CCPoint &);
    void bombStart(CCPoint &, float dir, float time);
    void bombFly(CCPoint &, CCPoint &, float time);
    void bombEnd();
private:
    CCArray *shadow;
    float passTime;

    CCParticleSun *sun;
    CCSprite *detail;
    int state;

};
#endif
