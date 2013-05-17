#include "MyStrokeFont.h"
#include "math.h"
//https://gist.github.com/kohashi/3991482
int kTagStroke = 1000;

bool MyStrokeFont::init() {
    strokeSize = 2;
    strokeColor = ccc3(15, 15, 15);
    shadow = NULL;
    CCSprite::init();
    m_pFontName = new std::string("Helvetica");
    m_fFontSize = 12;
    return true;
}
//需要先绘制背影接着绘制字体本身
//要保证是中心位置移动
CCRenderTexture *MyStrokeFont::createStroke(CCLabelTTF *label, float size, ccColor3B cor) {
    CCTexture2D *texture = label->getTexture();
    CCLog("createStroke %x %f %x", label, size, texture);
    if(texture == NULL)
        return NULL;
    CCSize cs = texture->getContentSize();

    
    CCRenderTexture *rt = CCRenderTexture::create(texture->getContentSize().width+size*2, texture->getContentSize().height+size*2, kTexture2DPixelFormat_RGBA8888);
    CCPoint originalPos = label->getPosition();
    ccColor3B originalColor = label->getColor();
    float originalScaleX = label->getScaleX();
    float originalScaleY = label->getScaleY();
    bool originalVisibility = label->isVisible();
    ccBlendFunc originalBlend = label->getBlendFunc();

    label->setColor(cor);
    label->setScale(1);
    label->setVisible(true);
    //当前要放上去的阴影 使用阴影自身的alpha值来乘 SRC_ALPHA
    //已经放到纹理中的阴影 使用GL_ONE 保留阴影
    label->setBlendFunc((ccBlendFunc){GL_SRC_ALPHA, GL_ONE});


    CCPoint bottomLeft = ccp(
                            cs.width*label->getAnchorPoint().x+size, 
                                cs.height*label->getAnchorPoint().y+size);
    CCPoint positionOffset = ccp(label->getContentSize().width/2, label->getContentSize().height/2);
    rt->begin();
    for(int i = 0; i < 360; i += 10) {
        /*
        for(int j = 0; j < size; j++) {
            label->setPosition(ccp(
                            bottomLeft.x+sin(CC_DEGREES_TO_RADIANS(i))*j, 
                            bottomLeft.y+cos(CC_DEGREES_TO_RADIANS(i))*j));
            label->visit();
        }
        */

        label->setPosition(ccp(
                        bottomLeft.x+sin(CC_DEGREES_TO_RADIANS(i))*size, 
                        bottomLeft.y+cos(CC_DEGREES_TO_RADIANS(i))*size));
        label->visit();
    }
    rt->end();

    label->setPosition(originalPos);
    label->setColor(originalColor);
    label->setBlendFunc(originalBlend);
    label->setVisible(originalVisibility);
    
    label->setScaleX(originalScaleX);
    label->setScaleY(originalScaleY);

    rt->setPosition(positionOffset);
    return rt;
}

void MyStrokeFont::setString(const char *string) {
    CCLog("set String %s", string);
    CCLabelTTF::setString(string);
    setShadow();
}
void MyStrokeFont::setShadow() {
    if(shadow != NULL) {
        shadow->removeFromParent();
        shadow = NULL;
    }
    CCLog("setShadow");
    shadow = MyStrokeFont::createStroke(this, strokeSize, strokeColor);
    if(shadow != NULL)
        this->addChild(shadow, -1, kTagStroke);
}
