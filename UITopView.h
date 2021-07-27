#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "UIProgressBar.h"
#include "UITextBlock.h"
#include "UIWorkoutView.h"

#ifndef _UITOPVIEW_
#define _UITOPVIEW_

enum TVElement { TVLeftTB, TVRightTB, TVWorkoutView /*, progBar, warmup, workout, cooldown, progBG */};

struct TVLayoutSpec {
	TVElement type;
	float x, y, width, height;
};

const int c_tvNumElementPositions = 3;

const TVLayoutSpec c_TVLayoutSpecs[] = {
	{ TVLeftTB, -115, 300, 220, 70 },
	{ TVRightTB, 115, 300, 220, 70 },
	{ TVWorkoutView, 0, 235, 450, 30 }
};

const GLuint c_TVDefaultTextColor = 0xFF0000FF;

class UITopView : public UIElement
{
	protected:
		UIState m_state;
		UIWorkoutMode m_startingWorkoutMode;
		CPVRTMap<UIState, UIElement**> m_stateMap;
		bool hidden;
	public:
		UITopView();
		UITopView(UIState startingState, UIWorkoutMode startingWorkoutState);
		virtual bool LoadTextures(CPVRTString* const pErrorString);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc);
		virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
		virtual bool Text();
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		void SetState(UIState state);
		UIState GetState();
};

#endif