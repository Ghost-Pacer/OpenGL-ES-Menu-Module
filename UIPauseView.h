#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "UIButton.h"

#ifndef _UIPAUSEVIEW_H
#define _UIPAUSEVIEW_H

enum PVElement { PVIcon, PVResumeButton, PVEndButton };

struct PVLayoutSpec {
	PVElement type;
	float x, y, width, height;
};

const int c_numPVElements = 3;

const PVLayoutSpec c_PVLayoutSpecs[] = {
	{ PVIcon, 0, 0, 85, 115 },
	{ PVResumeButton, 0, -190, 360, 40 },
	{ PVEndButton, 0, -255, 360, 40 }
};

class UIPauseView : public UIElement
{
	private:
		UIElement** m_elements;
		bool m_hidden;
		bool m_resume;
	public:
		UIPauseView();
		virtual bool LoadTextures(CPVRTString* const pErrorString);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		bool ResumeSelected();
};

#endif