#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "Print2D.h"

#ifndef _UIBUTTON_H
#define _UIBUTTON_H

struct ButtonData {
	char* activeBG;
	char* inactiveBG;
	float width, height, insetX, insetY, textScale;
};

const ButtonData c_UIBDefaults = {
	"buttonActive.pvr", "buttonInactive.pvr", 360, 40, 0, 0, 0.18 
};

class UIButton : public UIElement
{
	protected:
        UIImage m_activeBG;
		UIImage m_inactiveBG;
        Print2D* m_print2D;
        char* m_text;
        GLuint m_color;
		bool m_active;
        float m_x, m_y, m_width, m_height, m_insetX, m_insetY, m_textScale;
	public:
        UIButton();
		UIButton(char* text, float x, float y, GLuint color);
        UIButton(char* activeBG, char* inactiveBG, char* text, float x, float y, float width, float height, float insetX, float insetY, float textScale, GLuint color);
		void ToggleActive();
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc);
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Text();
		virtual void UpdateFrame(CPVRTMap<char*, void*> valueMap);
		virtual void Hide();
		virtual void Show();
};

#endif