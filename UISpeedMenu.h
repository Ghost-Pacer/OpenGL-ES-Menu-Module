#include "UIElement.h"
#include "UIMessage.h"
#include "UIImage.h"
#include "UIProgressBar.h"
#include "UICompositeView.h"

#ifndef _UISPEEDMENU_H
#define _UISPEEDMENU_H

enum UISMType {
	Title,
	Arrows,
	Value,
	Back
};

struct UISMSpec {
	char* text;
	char* imgTex;
	float x, y, scale, width, height;
	UISMType type;
};

const UISMSpec c_UISMSpecs[] = {
	{ "Speed", NULL, 0, 120, 0.325, 0, 0, Title },
	{ NULL, "updown.pvr", 120, 20, 0, 30, 40, Arrows },
	{ "00:00", NULL, -40, 20, 0.75, 0, 0, Value },
	{ "Back", NULL, 0, -200, 0.325, 0, 0, Back }
};

const int c_numUISMElems = 4;

class UISpeedMenu : public UIElement
{
	protected:
		bool m_selected;
		bool m_flash;
		bool m_hidden;
		char* m_currentSpeed;
		UIImage* m_arrows;
	public:
		UISpeedMenu();
		virtual bool LoadTextures(CPVRTString* const pErrorStr);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		virtual void Delete();
};

#endif