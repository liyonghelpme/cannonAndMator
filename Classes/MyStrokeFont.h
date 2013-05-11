#ifndef MYSTROKEFONT_H__
#define MYSTROKEFONT_H__
#include "cocos2d.h"
using namespace cocos2d;

extern int kTagStroke;
class MyStrokeFont : public CCLabelTTF {
public:
    int strokeSize;
    ccColor3B strokeColor;
    CCRenderTexture *shadow;

    static CCRenderTexture *createStroke(CCLabelTTF *, float size, ccColor3B cor);
    CREATE_FUNC(MyStrokeFont);
    bool init();
    virtual void setString(const char *string);
    void setShadow();

};
#endif
