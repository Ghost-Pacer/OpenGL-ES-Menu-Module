#include "UISummaryView.h"

UISummaryView::UISummaryView()
{
	m_elements = new UIElement*[c_numSUMElements];
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		SUMLayoutSpec spec = c_SUMLayouSpecs[i];
		switch(spec.type) {
			case SVDistance:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF, UIDistanceM);
				break;
			case SVEnergy:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF, UIEnergyKJ);
				break;
			case SVPace:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF, UISpeedMPM);
				break;
			case SVCalories:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF, UICalories);
				break;
			default:
				m_elements[i] = NULL;
				break;
		}
	}
}

bool
UISummaryView::LoadTextures(CPVRTString* const pErrorStr)
{
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		if (m_elements[i] == NULL) {
			continue;
		} else if (!m_elements[i]->LoadTextures(pErrorStr)) {
			fprintf(stderr, "UISummaryView element failed to load\n");
			return false;
		}
	}
	return true;
}

void
UISummaryView::BuildVertices()
{
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		if (m_elements[i] != NULL) {
			m_elements[i]->BuildVertices();
		}
	}
}

bool
UISummaryView::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
{
	if (m_hidden) {
		return true;
	}
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		if (m_elements[i] == NULL) {
			continue;
		} else if (!m_elements[i]->Render(uiMVPMatrixLoc, print3D, isRotated)) {
			fprintf(stderr, "UISummaryView element failed to render\n");
		}
	}
	return true;
}

void
UISummaryView::Update(UIMessage updateMessage)
{
	//UIMessage delegateMessage;
	m_hidden = !(updateMessage.ReadState() == UISummary);
	for (int i = 0 ; i < c_numSUMElements; i ++) {
		if (m_elements[i] == NULL) {
			continue;
		}
		m_elements[i]->Update(updateMessage);
	}
}

void
UISummaryView::Hide()
{
	m_hidden = true;
}

void
UISummaryView::Show()
{
	m_hidden = false;
}