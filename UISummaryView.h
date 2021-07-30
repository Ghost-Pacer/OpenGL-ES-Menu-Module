#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UITextBlock.h"

#ifndef _UISUMMARYVIEW_H
#define _UISUMMARYVIEW_H

enum SUMElement { SVCompleteIcon, SVDistance, SVEnergy, SVPace, SVCalories };

struct SUMLayoutSpec {
	SUMElement type;
	float x, y, width, height;
};

const int c_numSUMElements = 4;

const SUMLayoutSpec c_SUMLayouSpecs[] = {
	{ SVDistance, -115, -130, 220, 70 },
	{ SVEnergy, 115, -130, 220, 70 },
	{ SVPace, -115, -225, 220, 70 },
	{ SVCalories, 115, -225, 220, 70 }
};

class UISummaryView : public UIElement
{
	protected:
		UIElement** m_elements;
		bool m_hidden;
	public:
		UISummaryView();
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
};

#endif