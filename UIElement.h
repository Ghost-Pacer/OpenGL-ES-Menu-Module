#include "OGLES2Tools.h"
#include "UIMessage.h"

#ifndef _UIELEMENT_H
#define _UIELEMENT_H

#include "UIPrinter.h"

class UIElement
{
    public:
        virtual bool LoadTextures(CPVRTString* const pErrorStr) = 0;
        virtual void BuildVertices() = 0;
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated) = 0;
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer) = 0;
		virtual void Update(UIMessage updateMessage) = 0;
		virtual void Hide() = 0;
		virtual void Show() = 0;
};

#endif _UIELEMENT_H