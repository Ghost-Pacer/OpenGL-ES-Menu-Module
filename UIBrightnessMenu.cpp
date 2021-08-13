#include "UIBrightnessMenu.h"

UIBrightnessMenu::UIBrightnessMenu()
{
	m_hidden = true;
	m_brightSelected = false;
	m_selected = new UICompositeView("brightnessBG.pvr", 0, 50, 300, 300);
	m_deselected = new UICompositeView("brightnessBG.pvr", 0, 50, 300, 300);
	m_selected->AddImage("brightImgB.pvr", 0, 25, 150, 150);
	m_deselected->AddImage("brightImgR.pvr", 0, 25, 150, 150);
	UIProgressBar* progBlue = new UIProgressBar(PBType::BrightnessB, 0, -40, 0.75);
	m_selected->AddElement(progBlue);
	UIProgressBar* progRed = new UIProgressBar(PBType::BrightnessR, 0, -40, 0.75);
	m_deselected->AddElement(progRed);
}

bool
UIBrightnessMenu::LoadTextures(CPVRTString* const pErrorStr)
{
	if (m_selected != NULL && m_deselected != NULL) {
		m_selected->LoadTextures(pErrorStr);
		m_deselected->LoadTextures(pErrorStr);
		return true;
	} else {
		return false;
	}
}

void
UIBrightnessMenu::BuildVertices()
{
	if (m_selected != NULL && m_deselected != NULL) {
		m_selected->BuildVertices();
		m_deselected->BuildVertices();
	}
}

bool
UIBrightnessMenu::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		//fprintf(stderr, "UIBM hidden\n");
		return true;
	}
	if (m_selected != NULL && m_deselected != NULL) {
		//fprintf(stderr, "UIBM rendering\n");
		if (m_brightSelected) {
			if (!m_flash) {
				m_selected->Render(uiMVPMatrixLoc, printer);
			}
		} else {
			if (!m_flash) {
				m_deselected->Render(uiMVPMatrixLoc, printer);
			}
		}
	} else {
		fprintf(stderr, "UIBM NULL element\n");
	}
	GLuint color;
	if (!m_brightSelected) {
		color = 0xFFFF0000;
	} else {
		color = 0xFF0000FF;
	}
	printer->Print(0, -200, 0.325, color, UIFBold, "Back");
	return true;
}

void
UIBrightnessMenu::Update(UIMessage updateMessage)
{
	if (m_selected == NULL || m_deselected == NULL) {
		return;
	}

	if (updateMessage.ReadState() == UIMenuBrightness) {
		//fprintf(stderr, "UIBM message received\n");
		m_hidden = false;
		m_flash = updateMessage.Read(UIFlash);
		m_brightSelected = updateMessage.Read(UIBrightnessSelected);
		m_selected->Update(updateMessage);
		m_deselected->Update(updateMessage);
	} else {
		m_hidden = true;
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
	if (m_deselected != NULL) {
		m_deselected->Delete();
		delete m_deselected;
		m_deselected = NULL;
	}
	if (m_selected != NULL) {
		m_selected->Delete();
		delete m_selected;
		m_selected = NULL;
	}
	return;
}