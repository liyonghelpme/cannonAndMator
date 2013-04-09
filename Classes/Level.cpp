#include "Level.h"

Level *Level::create() {
    Level *pRet = new Level();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
void Level::init() {
    scheduleUpdate();
    leftDelta = new float[8];
    rightDelta = new float[8];

    waterBlock = CCArray::create();
    waterBlock->retain();

    for(int i = 0; i < 8; i++) {
        Water *w = Water::create();
        w->setPosition(ccp(100+i*50, 150));
        addChild(w);
        waterBlock->addObject(w);
    }

    Water *w = (Water *)waterBlock->objectAtIndex(0);
    //w->setPosition(ccp(100, 100));
    w->velocity = {0, 100*M_PI};

}

Level::~Level() {
    waterBlock->release();
    delete [] leftDelta;
    delete [] rightDelta;
}

void Level::update(float dt) {
    float Spread = 0.1;
    for(unsigned int i = 0; i < waterBlock->count(); i++) {
        Water *w = (Water *)waterBlock->objectAtIndex(i);
        w->update(dt);
    }
    //iteration speed and position
    for(int j = 0; j < 3; j++) {
        //adjust velocity
        for(unsigned int i = 0; i < waterBlock->count(); i++) {
            Water *w = (Water*)waterBlock->objectAtIndex(i);
            if(i > 0) {
                Water *lw = (Water *)waterBlock->objectAtIndex(i-1);
                leftDelta[i] = Spread*dt*(w->getPosition().y-lw->getPosition().y);
                lw->velocity.y += leftDelta[i];
            }
            if(i < waterBlock->count()-1) {
                Water *rw = (Water*)waterBlock->objectAtIndex(i+1);
                rightDelta[i] = Spread*dt*(w->getPosition().y-rw->getPosition().y);
                rw->velocity.y += rightDelta[i];
            }
        }
        
        //adjust Height
        for(unsigned int i = 0; i < waterBlock->count(); i++) {
            if(i > 0)  {
                Water *lw = (Water*)waterBlock->objectAtIndex(i-1);
                CCPoint old = lw->getPosition();
                old.y += leftDelta[i];
                lw->setPosition(old);
            }
            if(i < waterBlock->count()-1) {
                Water *rw = (Water*)waterBlock->objectAtIndex(i+1);
                CCPoint old = rw->getPosition();
                old.y += rightDelta[i];
                rw->setPosition(old);
            }
        }
    }
}

