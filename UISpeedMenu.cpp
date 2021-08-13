#include "UISpeedMenu.h"

UISpeedMenu::UISpeedMenu()
{
	m_hidden = true;
	m_infoDisplay = new UICompositeView(NULL, 0, -30, 0, 0);
	if (m_infoDisplay != NULL) {
		m_infoDisplay->AddText("Speed:", 0xFF0000FF, 0, 100, 0.325, UINone, UIFBold);
		m_infoDisplay->AddImage("arrows.pvr", 120, 0, 40, 40);
		m_infoDisplay->AddText("00:00", 0xFF0000FF, -40, 0, 0.75, UIBrightness, UIFBold);
		m_infoDisplay->AddText("Back", 0xFFFF0000, 0, -200, 0.325, UIBrightness, UIFBold);
	}
}

bool
UISpeedMenu::LoadTextures(CPVRTString* const pErrorStr)
{
	if (m_infoDisplay != NULL) {
		m_infoDisplay->LoadTextures(pErrorStr);
		return true;
	} else {
		return false;
	}
}

void
UISpeedMenu::BuildVertices()
{
	if (m_infoDisplay != NULL) {
		m_infoDisplay->BuildVertices();
	}
}

bool
UISpeedMenu::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
	if (m_infoDisplay != NULL) {
		m_infoDisplay->Render(uiMVPMatrixLoc, printer);
	}
	return true;
}

void
UISpeedMenu::Update(UIMessage updateMessage)
{
	if (m_infoDisplay == NULL) {
		return;
	}

	if (updateMessage.ReadState() == UIMenuSpeed) {
		m_hidden = false;
		m_infoDisplay->Update(updateMessage);
	}
}

void
UISpeedMenu::Hide()
{
	m_hidden = true;
}

void
UISpeedMenu::Show()
{
	m_hidden = false;
}

void
UISpeedMenu::Delete()
{
	if (m_infoDisplay != NULL) {
		m_infoDisplay->Delete();
		delete m_infoDisplay;
		m_infoDisplay = NULL;
	}
	return;
}