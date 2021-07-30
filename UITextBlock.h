#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "Print2D.h"

#ifndef _UITEXTBLOCK_H
#define _UITEXTBLOCK_H

struct TextblockData {
	char* bg;
	float width, height, insetX, insetY, textScale;
};

const TextblockData c_UITBDefaults = {
	"basicBox.pvr", 221, 70, 0, -5, 0.36
};

class UITextBlock : public UIElement
{
    protected:
        UITextType m_updateKey;
        UIImage m_bg;
        Print2D* m_print2D;
        char* m_text;
        //UIFont m_fontMain;
        char* m_textSecondary;
        //UIFont m_fontSecondary;
        GLuint m_color;
        float m_x, m_y, m_width, m_height, m_insetX, m_insetY, m_textScale;
		bool m_hidden;
    public:
        UITextBlock();
		UITextBlock(char* text, float x, float y, GLuint color, UITextType m_updateKey);
		// UITextBlock(char* text, char* textSecondary, UIFont fontMain, UIFont fontSec,
        //      float x, float y, GLuint color, UITextType m_updateKey);
        UITextBlock(char* bg, char* text, float x, float y, float width, float height, 
                float insetX, float insetY, float textScale, GLuint color , UITextType m_updateKey);
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc);
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
        virtual bool Text();
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
};

#endif _UITEXTBLOCK_H