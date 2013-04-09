#include "[NAME].h"
[NAME] *[NAME]::create() {
    [NAME] *pRet = new [NAME]();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool [NAME]::init() {
    scheduleUpdate();
    return true;
}

void [NAME]::update(float dt) {
}

[NAME]::~[NAME]() {
}
