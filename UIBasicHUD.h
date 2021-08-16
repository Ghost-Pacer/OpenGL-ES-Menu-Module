/******************************************************************************

 @File          UIBasicHUD.h

 @Title         UIBasicHUD Header

 @Author        Siddharth Hathi

 @Description   Header file for the UIBasicHUD object class. Defines UIBasicHUD

******************************************************************************/

#include "OGLES2Tools.h"
#include "UITextBlock.h"
#include "UIElement.h"

#ifndef _UIBASICHUD_H
#define _UIBASICHUD_H

// Number of elements in the hud
const int c_numBHElements = 2;

// Struct used to store the location and update keys for the two hud elements
struct UIBHLayoutSpec {
	UITextType updateKey;
	char* subtext;
	float x, y;
};

// The layout specifications of the 2 elements
const UIBHLayoutSpec c_UIBHSpecs[] = {
	{ UIDistanceM, "mi", -115, 300 },
	{ UIAvatarDistance, "m", 115, 300 }
};

class UIBasicHUD: public UIElement
{
    protected:
		// Instance variables

		// Is the HUD hidden?
        bool m_hidden;

		// The array of elements that make up the HUD
        UIElement* m_elements[c_numBHElements];
    public:
		// Publicly exported functions
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