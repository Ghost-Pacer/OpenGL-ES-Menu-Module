#include "UIElement.h"
#include "UIMessage.h"
#include "UIImage.h"
#include "UIProgressBar.h"
#include "UICompositeView.h"

#ifndef _UISPEEDMENU_H
#define _UISPEEDMENU_H

class UISpeedMenu : public UIElement
{
	protected:
		bool m_hidden;
		UICompositeView* m_infoDisplay;
		UIProgressBar* m_speedBar;
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