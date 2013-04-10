#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "Lightning.h"
#include "Bomb.h"
#include "Cannon.h"
#include "Background.h"
#include "Shell.h"
#include "Mortar.h"
#include "Water.h"
#include "Level.h"
#include "Splash.h"
#include "Tin.h"
#include "FoodFactory.h"
#include "Gun.h"
#include "Gunner.h"
#include "Shoot.h"
#include "Bullet.h"
#include "ParticleWave.h"
#include "WaveTower.h"

//#include "Range.h"

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

    setTouchEnabled(true);
    setTouchPriority(1);
    setTouchMode(kCCTouchesOneByOne);

    //resourceSize / designSize
    CCDirector::sharedDirector()->setContentScaleFactor(1.0);
    //DesignResolution
    CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(800, 480, kResolutionExactFit);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize winPixle = CCDirector::sharedDirector()->getWinSizeInPixels();

    float contentScalor = CCDirector::sharedDirector()->getContentScaleFactor();

    printf("%f, %f, %f, %f\n", visibleSize.width, visibleSize.height, origin.x, origin.y);
    printf("winSize %f, %f, %f, %f, %f, %f, %f\n", winSize.width, winSize.height, winPixle.width, winPixle.height, contentScalor, visibleSize.width, visibleSize.height);

    
    Lightning *lightning = Lightning::create(NULL, 100, 10.0, 10.0, 20.0);
    lightning->midDisplacement(0, 160, 480, 160, 100.0);
    //lightning->testLine(300 ,400, 50, 200);
    //lightning->testLine(50 ,200, 300, 400);
    this->addChild(lightning);
    //lightning->runAction(CCFadeOut::create(2));

    //Layer3d *layer3d = Layer3d::create();
    //this->addChild(layer3d);
    //Bomb *bomb = Bomb::create();
    //addChild(bomb);

    Background *bk = Background::create();
    addChild(bk);
    
    Cannon *cannon = Cannon::create();
    addChild(cannon);
    cannon->setPosition(ccp(400, 240));

    /*
    shell = Shell::create(10);
    addChild(shell);
    shell->setPosition(ccp(300, 200));
    */


    Mortar *mortar = Mortar::create();
    mortar->setPosition(ccp(300, 200));
    addChild(mortar);



    Level *level = Level::create();
    addChild(level);

    Splash *s = Splash::create();
    addChild(s);

    /*
    Tin *tin = Tin::create();
    addChild(tin);
    tin->setPosition(ccp(300, 300));
    */

    FoodFactory *food = FoodFactory::create();
    addChild(food);

    /*
    Gun *gun = Gun::create();
    addChild(gun);
    gun->setPosition(ccp(400, 200));
    */


    Gunner *gunner = Gunner::create();
    addChild(gunner);
    gunner->setPosition(ccp(500, 200));

    //机枪火光
    Shoot *shoot = Shoot::create();
    addChild(shoot);
    shoot->setPosition(ccp(600, 300));


    /*
    Bullet *b = Bullet::create();
    addChild(b);
    b->setPosition(ccp(550, 200));
    */

    ParticleWave *particle = ParticleWave::create();
    addChild(particle);
    particle->setPosition(ccp(350, 200));


    WaveTower *w = WaveTower::create();
    addChild(w);
    w->setPosition(ccp(650, 200));
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}

void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {   
    //shell->setPosition(pTouch->getLocation());
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
}
