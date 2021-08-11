#include "UIBrightnessMenu.h"

UIBrightnessMenu::UIBrightnessMenu()
{
	m_hidden = true;
	m_infoDisplay = new UICompositeView(NULL, 0, -30, 0, 0);
	if (m_infoDisplay != NULL) {
		m_infoDisplay->AddText("Brightness: ", 0xFF0000FF, -40, 0, 0.5, UIBrightness, UIFBold);
		m_infoDisplay->AddImage("arrows.pvr", 100, 0, 16, 16);
	}
	m_brightnessBar = new UIProgressBar(PBB, 0, -30, 1); 
}

bool
UIBrightnessMenu::LoadTextures(CPVRTString* const pErrorStr)
{
	if (m_infoDisplay != NULL && m_brightnessBar != NULL) {
		m_infoDisplay->LoadTextures(pErrorStr);
		m_brightnessBar->LoadTextures(pErrorStr);
		return true;
	} else {
		return false;
	}
}

void
UIBrightnessMenu::BuildVertices()
{
	if (m_infoDisplay != NULL && m_brightnessBar != NULL) {
		m_infoDisplay->BuildVertices();
		m_brightnessBar->BuildVertices();
	}
}

bool
UIBrightnessMenu::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
	if (m_infoDisplay != NULL && m_brightnessBar != NULL) {
		m_infoDisplay->Render(uiMVPMatrixLoc, printer);
		m_brightnessBar->Render(uiMVPMatrixLoc, printer);
	}
	return true;
}

void
UIBrightnessMenu::Update(UIMessage updateMessage)
{
	if (m_infoDisplay == NULL || m_brightnessBar == NULL) {
		return;
	}

	if (updateMessage.ReadState() == UIMenuBrightness) {
		m_hidden = false;
		m_infoDisplay->Update(updateMessage);
		m_brightnessBar->Update(updateMessage);
	}
}

void
UIBrightnessMenu::Hide()
{
	m_hidden = true;
}

void
UIBrightnessMenu::Show()
{
	m_hidden = false;
}

void
UIBrightnessMenu::Delete()
{
	if (m_infoDisplay != NULL) {
		m_infoDisplay->Delete();
		delete m_infoDisplay;
		m_infoDisplay = NULL;
	}
	if (m_brightnessBar != NULL) {
		m_brightnessBar->Delete();
		delete m_brightnessBar;
		m_brightnessBar = NULL;
	}
	return;
}