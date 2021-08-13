#include "OGLES2Tools.h"
#include "UITextBlock.h"
#include "UIElement.h"

#ifndef _UIBASICHUD_H
#define _UIBASICHUD_H

const int c_numBHElements = 2;

struct UIBHLayoutSpec {
	UITextType updateKey;
	char* subtext;
	float x, y;
};

const UIBHLayoutSpec c_UIBHSpecs[] = {
	{ UIDistanceM, "mi", -115, 300 },
	{ UIAvatarDistance, "m", 115, 300 }
};

class UIBasicHUD: public UIElement
{
    protected:
        bool m_hidden;
        UIElement* m_elements[c_numBHElements];
    public:
        UIBasicHUD();
		virtual bool LoadTextures(CPVRTString* const pErrorStr);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		virtual void Delete();
};

#endif