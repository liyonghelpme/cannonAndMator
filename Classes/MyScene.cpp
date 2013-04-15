#include "MyScene.h"
#include "AppMacros.h"
#include "Fog.h"
USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    CCDirector::sharedDirector()->setContentScaleFactor(1.0);
    //DesignResolution
    CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(960, 640, kResolutionExactFit);
    
    CCSprite *back = CCSprite::create("back.png");
    addChild(back);
    back->setAnchorPoint(ccp(0, 0));
    
    Fog *fog = Fog::create();
    addChild(fog);

    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
