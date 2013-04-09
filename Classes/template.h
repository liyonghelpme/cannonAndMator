#ifndef __[NAME]_H__
#define __[NAME]_H__
#include "cocos2d.h"
using namespace cocos2d;

class [NAME] : public CCNode {
public:
    virtual bool init();
    static [NAME] *create();
    virtual void update(float dt);
    ~[NAME]();
};
#endif
