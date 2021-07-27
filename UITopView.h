#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "UIProgressBar.h"
#include "UITextBlock.h"

#ifndef _UITOPVIEW_
#define _UITOPVIEW_

enum TVState { main, info, pause, summary };

enum TVElement { leftTB, rightTB, progBar, warmup, workout, cooldown, progBG };

struct TVLayoutSpec {
	TVElement type;
	float x, y, width, height;
};

const int c_tvNumElementPositions = 7;

const TVLayoutSpec c_TVLayoutSpecs[] = {
	{ leftTB, -115, 300, 220, 70 },
	{ rightTB, 115, 300, 220, 70 },
	{ progBG, 0, 235, 450, 30 },
	{ progBar, 40, 235, 350, 18 },
	{ warmup, -200, 235, 12, 16 },
	{ workout, -176, 235, 12, 16 },
	{ cooldown, -152, 235, 12, 16 }
};

const GLuint c_TVDefaultTextColor = 0xFF0000FF;

class UITopView : public UIElement
{
	protected:
		TVState m_state;
		CPVRTMap<TVState, UIElement**> m_stateMap;
		bool hidden;
	public:
		UITopView();
		UITopView(TVState startingState);
		virtual bool LoadTextures(CPVRTString* const pErrorString);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc);
		virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
		virtual bool Text();
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		void SetState(TVState state);
		TVState GetState();
};

#endif