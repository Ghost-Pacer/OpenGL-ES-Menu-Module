#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "Print2D.h"

#ifndef _UITEXTBLOCK_H
#define _UITEXTBLOCK_H

class UITextBlock : public UIElement
{
    protected:
        UIImage m_bg;
        Print2D* m_print2D;
        char* m_text;
        GLuint m_color;
        float m_x, m_y, m_width, m_height, m_insetX, m_insetY, m_textScale;
    public:
        UITextBlock();
        UITextBlock(char* bg, char* text, float x, float y, float width, float height, float insetX, float insetY, float textScale, GLuint color);
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc);
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Text();
};

#endif _UITEXTBLOCK_H