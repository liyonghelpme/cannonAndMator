#include "FoodFactory.h"
FoodFactory *FoodFactory::create() {
    FoodFactory *p = new FoodFactory();
    p->init();
    p->autorelease();
    return p;
}
void FoodFactory::init() {
    scheduleUpdate();
    passTime = 0;
}
//增强Y 方向的 位置偏移 制造涌出来的效果
void FoodFactory::update(float dt) {
    passTime += dt;
    if(passTime >= 1.0) {
        for(int i = 0; i < 10; i++) {
            Tin *tin = Tin::create();
            addChild(tin);

            float rw = random()%10000/10000.*10;
            float rh = random()%10000/10000.*100;
            tin->setPosition(ccp(300+rw, 300+rh));
            
            float rx = random()%10000/10000.*200-100;
            float ry = random()%10000/10000.*100+200;
            kmVec2Fill(&tin->velocity, rx, ry);
        }
        passTime = 0;
    }
}
