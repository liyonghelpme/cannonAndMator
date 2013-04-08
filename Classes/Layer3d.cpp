#include "Layer3d.h"
Layer3d *Layer3d::create()
{
    Layer3d *pRet = new Layer3d();
    pRet->init();
    pRet->autorelease();
    return pRet;
}

void Layer3d::init()
{
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    mTexture = CCTextureCache::sharedTextureCache()->addImage("edge.png");
    glGenBuffers(2, &m_pBuffersVBO[0]);

    kmMat4 matrixP;
    kmMat4 matrixMV;
    kmMat4 matrixMVP;
    kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
    kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);
    kmQuaternion quat;
    kmMat4 move;
    kmMat4Translation(&move, 400, 100, 100);
    kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
    kmMat4Multiply(&matrixMVP, &matrixMVP, &move);
    GLuint matrixId = glGetUniformLocation(getShaderProgram()->getProgram(), kCCUniformMVPMatrix_s);
    printf("matrixId %d\n", matrixId);
    getShaderProgram()->setUniformLocationWithMatrix4fv(matrixId, matrixMVP.mat, 1);
}
void Layer3d::draw()
{
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CC_NODE_DRAW_SETUP();
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    ccGLBindTexture2D(mTexture->getName());
    
    ccVertex3F vertices[4];
    ccVertex2F uv[4];
    int index[] = {0, 1, 2, 0, 2, 3};
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, uv);


    
    float x = 0;
    float y = 0;
    float len = 100;
    
    vertices[0] = vertex3(x-len, y-len, len);
    vertices[1] = vertex3(x-len, y+len, len);
    vertices[2] = vertex3(x+len, y+len, len);
    vertices[3] = vertex3(x+len, y-len, len);

    uv[0] = vertex2(0, 1);
    uv[1] = vertex2(0, 0);
    uv[2] = vertex2(1, 0);
    uv[3] = vertex2(1, 1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, index);
}


