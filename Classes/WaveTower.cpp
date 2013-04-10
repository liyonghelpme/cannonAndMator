#include "WaveTower.h"
WaveTower *WaveTower::create() {
    WaveTower *pRet = new WaveTower();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool WaveTower::init() {
    scheduleUpdate();
    return true;
}

void WaveTower::update(float dt) {
}

WaveTower::~WaveTower() {
}
