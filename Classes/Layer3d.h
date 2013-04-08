#ifndef __LAYER3D_H__
#define __LAYER3D_H__
#include "cocos2d.h"
using namespace cocos2d;
class Layer3d : public CCNode
{
public:
    virtual void draw();        
    static Layer3d *create(); 
    void init();
private:
    CCTexture2D *mTexture;
    GLuint m_pBuffersVBO[2];
};
#endif
