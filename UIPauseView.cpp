#include "UIPauseView.h"

UIPauseView::UIPauseView()
{
	m_hidden = false;
	m_elements = new UIElement*[c_numPVElements];
	for ( int i = 0; i < c_numPVElements; i ++ ) {
		PVLayoutSpec layoutSpec = c_PVLayoutSpecs[i];
		switch(layoutSpec.type) {
			case PVIcon:
				m_elements[i] = new UIImage("pause.pvr", layoutSpec.x, layoutSpec.y, layoutSpec.width, layoutSpec.height);
				break;
			case PVResumeButton:
				m_elements[i] = new UIButton("Resume", layoutSpec.x, layoutSpec.y, 0xFF0000FF, 0xFF000000);
				break;
			case PVEndButton:
				m_elements[i] = new UIButton("End", layoutSpec.x, layoutSpec.y, 0xFF0000FF, 0xFF000000);
				break;
			default:
				m_elements[i] = NULL;
				break;
		}
	}
}

bool
UIPauseView::LoadTextures(CPVRTString* const pErrorString)
{
	for ( int i = 0 ; i < c_numPVElements; i ++ ) {
		if (m_elements == NULL || !m_elements[i]->LoadTextures(pErrorString)) {
			fprintf(stderr, "UIPauseView item texture failed to load\n");
			return false;
		}
	}
	return true;
}

void
UIPauseView::BuildVertices()
{
	for ( int i = 0 ; i < c_numPVElements; i ++ ) {
		if (m_elements[i] != NULL) {
			m_elements[i]->BuildVertices();
		}
	}
}

bool
UIPauseView::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
	for ( int i = 0 ; i < c_numPVElements; i ++ ) {
		if (m_elements == NULL || !m_elements[i]->Render(uiMVPMatrixLoc, printer)) {
			fprintf(stderr, "UIPauseView item render failed\n");
		}
	}
	return true;
}

void
UIPauseView::Update(UIMessage updateMessage)
{
	if (updateMessage.ReadState() != UIPause) {
		// fprintf(stderr, "State: UISummary\n");
		m_hidden = true;
		return;
	} else {
		m_hidden = false;
	}
	if (m_elements[PVResumeButton] != NULL && m_elements[PVEndButton] != NULL
		 && updateMessage.ReadAction() == UIToggleActiveButton) {
		//fprintf(stderr, "Message received from UILayer\n");
		m_resume = !m_resume;
		updateMessage.Write(UIButtonActive, m_resume);
		m_elements[PVResumeButton]->Update(updateMessage);
		updateMessage.Write(UIButtonActive, !m_resume);
		m_elements[PVEndButton]->Update(updateMessage);
	}
}

void
UIPauseView::Hide()
{
	m_hidden = true;
}

void
UIPauseView::Show()
{
	m_hidden = false;
}

bool
UIPauseView::ResumeSelected()
{
	return m_resume;
}

void
UIPauseView::Delete()
{
	for ( int i = 0 ; i < c_numPVElements; i ++ ) {
		if (m_elements == NULL && m_elements[i] != NULL) {
			delete m_elements[i];
			m_elements[i] = NULL;
		}
	}
}