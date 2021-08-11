#include "UISpeedMenu.h"

UISpeedMenu::UISpeedMenu()
{
	m_hidden = true;
	m_infoDisplay = new UICompositeView(NULL, 0, -30, 0, 0);
	if (m_infoDisplay != NULL) {
		m_infoDisplay->AddText("Speed: ", 0xFF0000FF, -40, 0, 0.4, UIBrightness, UIFBold);
		m_infoDisplay->AddImage("arrows.pvr", 100, 0, 16, 16);
	}
	m_speedBar = new UIProgressBar(PBB, 0, -30, 1); 
}

bool
UISpeedMenu::LoadTextures(CPVRTString* const pErrorStr)
{
	if (m_infoDisplay != NULL && m_speedBar != NULL) {
		m_infoDisplay->LoadTextures(pErrorStr);
		m_speedBar->LoadTextures(pErrorStr);
		return true;
	} else {
		return false;
	}
}

void
UISpeedMenu::BuildVertices()
{
	if (m_infoDisplay != NULL && m_speedBar != NULL) {
		m_infoDisplay->BuildVertices();
		m_speedBar->BuildVertices();
	}
}

bool
UISpeedMenu::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
	if (m_infoDisplay != NULL && m_speedBar != NULL) {
		m_infoDisplay->Render(uiMVPMatrixLoc, printer);
		m_speedBar->Render(uiMVPMatrixLoc, printer);
	}
	return true;
}

void
UISpeedMenu::Update(UIMessage updateMessage)
{
	if (m_infoDisplay == NULL || m_speedBar == NULL) {
		return;
	}

	if (updateMessage.ReadState() == UIMenuSpeed) {
		m_hidden = false;
		m_infoDisplay->Update(updateMessage);
		m_speedBar->Update(updateMessage);
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
	if (m_speedBar != NULL) {
		m_speedBar->Delete();
		delete m_speedBar;
		m_speedBar = NULL;
	}
	return;
}