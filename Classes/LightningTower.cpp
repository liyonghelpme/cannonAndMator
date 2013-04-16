#include "LightningTower.h"
LightningTower *LightningTower::create() {
    LightningTower *pRet = new LightningTower();
    pRet->init();
    pRet->autorelease();
    return pRet;
}
bool LightningTower::init() {
    lightning = NULL;
    scheduleUpdate();
    return true;
}

void LightningTower::update(float dt) {
    if(lightning == NULL) {
        //CCLog("make light");
        Lightning *l = Lightning::create(NULL, 100, 10.0, 10.0, 20.0);
        lightning = l;
        addChild(lightning);

        lightning->type = 1;
        lightning->needSub = true;
        lightning->subMax = 10;
        lightning->possible = 5;
        lightning->realEnd = ccp(600, 200);
        
        //CCLog("mid displace ment");
        lightning->midDisplacement(100, 200, 600, 200, 100.0);
        lightning->makeSubLightning();
        
        CCLog("delay");
        CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(LightningTower::removeTempNode));
        lightning->runAction(CCSequence::create(CCDelayTime::create(1.0), func, NULL));

    }
}
void LightningTower::removeTempNode() {
    CCLog("removeTempNode");
    lightning->removeFromParent();
    lightning = NULL;

}


LightningTower::~LightningTower() {
}
