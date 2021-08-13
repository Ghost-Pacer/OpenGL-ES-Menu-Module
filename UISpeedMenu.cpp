#include "UISpeedMenu.h"

UISpeedMenu::UISpeedMenu()
{
	m_hidden = false;
	m_flash = false;
	m_selected = false;
	m_currentSpeed = "0";
	UISMSpec imgSpec = c_UISMSpecs[Arrows];
	fprintf(stderr, "img tex: %s\n", imgSpec.imgTex);
	m_arrows = new UIImage(imgSpec.imgTex, imgSpec.x, imgSpec.y, imgSpec.width, imgSpec.height);
}

bool
UISpeedMenu::LoadTextures(CPVRTString* const pErrorStr)
{
	if (m_arrows != NULL) {
		return m_arrows->LoadTextures(pErrorStr);
	}
	return true;
}

void
UISpeedMenu::BuildVertices()
{
	if (m_arrows != NULL) {
		m_arrows->BuildVertices();
	}
}

bool
UISpeedMenu::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
	GLuint selectedColor = 0xFFFF0000;
	GLuint deselectedColor = 0xFF0000FF;
	if (m_arrows != NULL) {
		m_arrows->Render(uiMVPMatrixLoc, printer);
	}
	for ( int i = 0; i < c_numUISMElems; i ++ ) {
		UISMSpec spec = c_UISMSpecs[i];
		switch (spec.type) {
			case Title:
				printer->Print(spec.x, spec.y, spec.scale, deselectedColor, UIFBold, spec.text);
				break;
			case Value:
				if (!m_flash) {
					if (m_selected) {
						printer->Print(spec.x, spec.y, spec.scale, selectedColor, UIFBold, m_currentSpeed);
					} else {
						printer->Print(spec.x, spec.y, spec.scale, deselectedColor, UIFBold, m_currentSpeed);
					}
				}
				break;
			case Back:
				if (m_selected) {
					printer->Print(spec.x, spec.y, spec.scale, deselectedColor, UIFBold, spec.text);
				} else {
					printer->Print(spec.x, spec.y, spec.scale, selectedColor, UIFBold, spec.text);
				}
				break;
			default:
				break;
		}
	}
	return true;
}

void
UISpeedMenu::Update(UIMessage updateMessage)
{
	if (updateMessage.ReadState() != UIMenuSpeed) {
		m_hidden = true;
		return;
	}
	m_hidden = false;
	m_selected = updateMessage.Read(UISpeedSelected);
	m_flash = updateMessage.Read(UIFlash);
	if (updateMessage.Read(UISpeedMPM) != NULL) {
		char* prevSpeed = m_currentSpeed;
		m_currentSpeed = updateMessage.Read(UISpeedMPM);
		if (strcmp(prevSpeed, "0") != 0) {
			delete prevSpeed;
		}
	}
	return;
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
	if (m_arrows != NULL) {
		m_arrows->Delete();
		delete m_arrows;
		m_arrows = NULL;
	}
}