#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UITextBlock.h"

#ifndef _UISUMMARYVIEW_H
#define _UISUMMARYVIEW_H

enum SUMElement { completeIcon, distance, energy, pace, calories };

struct SUMLayoutSpec {
	SUMElement type;
	float x, y, width, height;
};

const int c_numSUMElements = 5;

const SUMLayoutSpec c_SUMLayouSpecs[] = {
	{ completeIcon, 0, 0, 80, 80 },
	{ distance, -115, -130, 220, 70 },
	{ energy, 115, -130, 220, 70 },
	{ pace, -115, -225, 220, 70 },
	{ calories, 115, -225, 220, 70 }
};

class UISummaryView
{
	protected:
		UIElement** m_elements;
		bool m_hidden;
	public:
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
};

#endif