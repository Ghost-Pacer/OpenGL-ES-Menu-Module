#include "UIElement.h"
#include "UIMessage.h"
#include "UIImage.h"
#include "UIProgressBar.h"
#include "UICompositeView.h"

#ifndef _UIBRIGHTNESSMENU_H
#define _UIBRIGHTNESSMENU_H

class UIBrightnessMenu : public UIElement
{
	protected:
		bool m_hidden;
		UICompositeView* m_infoDisplay;
		UIProgressBar* m_brightnessBar;
	public:
		UIBrightnessMenu();
		virtual bool LoadTextures(CPVRTString* const pErrorStr);
		virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		virtual void Delete();
};

#endif