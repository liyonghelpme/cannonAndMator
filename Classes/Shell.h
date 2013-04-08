#ifndef __SHELL_H__
#define __SHELL_H__
#include "cocos2d.h"
#include "Lightning.h"
using namespace cocos2d;
class Shell : public CCNode {
public:
    static Shell *create(float );
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
    virtual const CCPoint& getPosition();

    void setRealPosition(const CCPoint& newPosition);

    float lifeTime;
    void setRadius(float r);

    CCParticleSystemQuad *bombStart(CCPoint&, float dir, float time);
    void bombFly(CCPoint& start, CCPoint& end, float time);
    void bombEnd(CCPoint& end);

private:
    float passTime;
    float lightTime;
    float countLife;

    CCNode *ball;
    float scaleForBall;

    ccColor3B bombColor;
    int state;
};
#endif
