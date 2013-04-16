#ifndef __LightningTower_H__
#define __LightningTower_H__
#include "cocos2d.h"
#include "Lightning.h"
using namespace cocos2d;

class LightningTower : public CCNode {
public:
    virtual bool init();
    static LightningTower *create();
    virtual void update(float dt);
    ~LightningTower();
private:
    Lightning *lightning;
    void removeTempNode();
};
#endif
