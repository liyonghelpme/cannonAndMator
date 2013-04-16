#include "Lightning.h"
#include "stdlib.h"
#include "cmath"
#include "kazmath/utility.h"


Line *Line::create(const char *fileName, kmVec3 &a, kmVec3 &b, float thickness, float deg, ccColor3B c, kmVec3 &temp, Lightning *lightning)
{
    Line *line = new Line();
    line->initWithFile(fileName);
    line->setTextureRect(CCRectMake(63, 0, 1, 128));//宽第1的中间像素
    line->a = a;
    line->b = b;

    line->setAnchorPoint(ccp(0, 0.5));
    line->setScaleX(kmVec3Length(&temp)/1.0);
    line->setScaleY(thickness/128);
    line->setPosition(ccp(a.x, a.y));

    line->setRotation(deg);
    line->setColor(c);

    line->autorelease();
    return line;
}

//使用特定的Lightning 图片
//可以使用孩子节点的缓存 而不重新分配CCSprite

Lightning *Lightning::create(const char *fileName, unsigned int capacity, float detail, float thickness, float displace)//根据details 来设定sprite的容量
{
    Lightning *pRet = new Lightning();
    pRet->subMax = 0;
    pRet->needSub = false;
    pRet->type = 0;
    pRet->count = 0;
    pRet->initWithFile("edge.png", capacity);
    pRet->fileName = "edge.png";
    pRet->lines = CCArray::create();
    pRet->lines->retain();
    pRet->detail = detail;
    pRet->thickness = thickness;
    pRet->displace = displace;
    ccBlendFunc blendFunc = {GL_ONE, GL_ONE};
    pRet->setBlendFunc(blendFunc);
    pRet->alpha = 1.0f;
    pRet->fadeOutRate = 3.3f;
    pRet->color = ccc3(0.2*255, 0.2*255, 0.7*255);
    pRet->scheduleUpdate();
    pRet->subLightning = CCArray::create();
    pRet->subLightning->retain();
    pRet->possible = 10;
    pRet->subDifX = 50;
    pRet->subDifY = 50;
    pRet->points = CCArray::create();
    pRet->points->retain();
    pRet->realDis = 100;

    pRet->autorelease();
    return pRet;
}
void Lightning::update(float delta)
{
    if(type == 0) {
        alpha -= fadeOutRate*delta;
        CCArray *children = getChildren();
        CCObject *pObject;
        CCARRAY_FOREACH(children, pObject)
        {
            CCSprite *sp = (CCSprite *)pObject;
            ccColor3B c = {color.r*alpha, color.g*alpha, color.b*alpha};
            sp->setColor(c);
        }
    } else if(type == 1) {
        if(count < lines->count()) {
            CCNode *p;
            p = (CCNode*)lines->objectAtIndex(count);
            p->setVisible(true);

            p = (CCNode*)lines->objectAtIndex(count+1);
            p->setVisible(true);

            p = (CCNode*)lines->objectAtIndex(count+2);
            p->setVisible(true);

            count += 3;
        } else {
            type = 0; 
        }
    }
}
Lightning::~Lightning()
{
    lines->release();
    for(int i = 0; i < subLightning->count(); i++) {
        CCNode *p = (CCNode*)subLightning->objectAtIndex(i);
        p->removeFromParent();
    }
    subLightning->release();
    points->release();
}
void Lightning::testLine(float x1, float y1, float x2, float y2)
{
    /*
    kmVec3 a = {x1, y1};
    kmVec3 b = {x2, y2};

    //Line *line = Line::create(this->fileName.c_str(), a, b, thickness); 
    //addChild(line);


    CCSprite *s = CCSprite::create(fileName.c_str());
    s->setAnchorPoint(ccp(0.5, 0.5));
    s->ignoreAnchorPointForPosition(false);
    CCSize size = s->getContentSize();
    printf("%lf, %lf\n", size.width, size.height);
    //s->setPosition(ccp(32, 64));
    //s->setTextureRect(CCRectMake(63, 0, 1, 128));
    //s->setContentSize(CCSizeMake(1, 128));
    //s->setScaleX(20);
    //s->setScaleY(40/128.0);
    addChild(s);

    s = CCSprite::create(fileName.c_str());
    s->setAnchorPoint(ccp(0.5, 0.5));
    s->setPosition(ccp(b.x, b.y));
    //s->setTextureRect(CCRectMake(63, 0, 1, 128));
    //s->setContentSize(CCSizeMake(1, 128));
    s->setScaleX(20);
    //s->setScaleY(40/128.0);
    addChild(s);
    */
}
void Lightning::draw()
{
    if(alpha <= 0.0)
        return;

    if( m_pobTextureAtlas->getTotalQuads() == 0 )
    {
        return;
    }

    CC_NODE_DRAW_SETUP();

    arrayMakeObjectsPerformSelector(m_pChildren, updateTransform, CCSprite*);

    ccGLBlendFunc( m_blendFunc.src, m_blendFunc.dst );

    m_pobTextureAtlas->drawQuads();


}

void Lightning::midDisplacement(float x1, float y1, float x2, float y2, float dis)
{
    if(dis < detail){
        kmVec3 a, b;
        kmVec3Fill(&a, x1, y1, 0);
        kmVec3Fill(&b, x2, y2, 0);
        
        kmVec3 temp;
        kmVec3Subtract(&temp, &b, &a);
        double deg = -atan2(temp.y, temp.x)*180/kmPI;
        ccColor3B c = {255*.2, 255*.2, 255*.7};


        Line *line = Line::create(this->fileName.c_str(), a, b, thickness, deg, c, temp, this);
        addChild(line);
        if(type == 1)
            line->setVisible(false);
        lines->addObject(line);

        CCSprite *s = CCSprite::create(fileName.c_str());
        s->setAnchorPoint(ccp(1.0, 0.5));
        s->setPosition(ccp(a.x, a.y));
        s->setRotation(deg);
        s->setScale(thickness/128);
        s->setColor(c);
        addChild(s);
        if(type == 1)
            s->setVisible(false);
        lines->addObject(s);

        s = CCSprite::create(fileName.c_str());
        s->setAnchorPoint(ccp(0, 0.5));
        s->setPosition(ccp(b.x, b.y));
        s->setRotation(deg);
        s->setFlipX(true);
        s->setScale(thickness/128);
        s->setColor(c);
        addChild(s);
        if(type == 1) 
            s->setVisible(false);
        lines->addObject(s);

        //what's possibility?
        PointObject *point = new PointObject();
        point->autorelease();
        point->x = x1;
        point->y = y1;
        points->addObject(point);



    }else {
        float midX = (x1+x2)/2;
        float midY = (y1+y2)/2;
        midX += (random()*1.0/RAND_MAX-0.5)*dis;
        midY += (random()*1.0/RAND_MAX-0.5)*dis;
        midDisplacement(x1, y1, midX, midY, dis/2);
        midDisplacement(midX, midY, x2, y2,  dis/2);

    }
}
void Lightning::makeSubLightning() {
    for(int i = 0; i < points->count(); i++) {
        if(needSub && subLightning->count() < subMax) {
            int rd = random()%possible;

            if(rd == 0) {
                PointObject *po = (PointObject*)points->objectAtIndex(i);
                float x1 = po->x;
                float y1 = po->y;
                CCLog("sub lightning");
                Lightning *sl = Lightning::create(NULL, 100, 10.0, 10.0, 20.0);
                getParent()->addChild(sl);
                sl->type = 1;
                float dx = random()%10000/10000.*subDifX;
                float dy = random()%10000/10000.*subDifY;
                sl->midDisplacement(x1, y1, realEnd.x+dx, realEnd.y+dy, realDis);

                subLightning->addObject(sl);
            }
        }
    }
}
