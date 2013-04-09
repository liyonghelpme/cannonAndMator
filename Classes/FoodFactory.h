#ifndef __FOOD_FACTORY_H__
#define __FOOD_FACTORY_H__
#include "cocos2d.h"
#include "Tin.h"
//食品工厂 模仿 水滴爆炸效果
//update 方法

//随机生成若干个 不同位置的 罐头
//播放罐头动画 罐头受重力影响 
using namespace cocos2d;
class FoodFactory : public CCNode {
public: 
    static FoodFactory *create();
    void init();
    
    virtual void update(float dt);
    float passTime;
};
#endif
