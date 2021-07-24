#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "UIProgressBar.h"
#include "UITextBlock.h"

#ifndef _UIINFOVIEW_
#define _UIINFOVIEW_

enum IVState { main, info, pause, end };

enum IVElement { leftTV, rightTV, progBar, warmup, workout, cooldown, progBG };

struct IVLayoutSpec {
	IVElement type;
	float x, y, width, height;
};

const int c_ivNumElementPositions = 7;

const IVLayoutSpec c_IVLayoutSpecs[] = {
	{ leftTV, -115, 300, 220, 70 },
	{ rightTV, 115, 300, 220, 70 },
	{ progBG, 0, 235, 450, 30 },
	{ progBar, 40, 235, 350, 18 },
	{ warmup, -200, 235, 12, 16 },
	{ workout, -176, 235, 12, 16 },
	{ cooldown, -152, 235, 12, 16 }
};

const GLuint c_IVDefaultTextColor = 0xFF0000FF;

class UIInfoView : public UIElement
{
	protected:
		IVState m_state;
		CPVRTMap<IVState, UIElement**> m_stateMap;
		bool hidden;
	public:
		UIInfoView();
		UIInfoView(IVState startingState);
		virtual bool LoadTextures(CPVRTString* const pErrorString);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc);
		virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
		virtual bool Text();
		virtual void UpdateFrame(CPVRTMap<char*, void*> valueMap);
		virtual void Hide();
		virtual void Show();
		void SetState(IVState state);
		IVState GetState();
};

#endif