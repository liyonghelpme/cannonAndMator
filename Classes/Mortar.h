#ifndef __MORTAR_H__
#define __MORTAR_H__
#include "cocos2d.h"
#include "Shell.h"
using namespace cocos2d;

class Mortar : public CCNode {
public:
    static Mortar *create();
    void init();
    virtual void update(float dt);
    virtual void draw();
private:
    float passTime;
    float dir;
    int state;
    Shell *shell;
};
#endif
