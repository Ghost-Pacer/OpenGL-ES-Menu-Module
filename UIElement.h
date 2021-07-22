#include "OGLES2Tools.h"

#ifndef _UIELEMENT_H
#define _UIELEMENT_H

class UIElement
{
    public:
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc);
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Text();
};

#endif _UIELEMENT_H