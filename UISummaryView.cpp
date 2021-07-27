#include "UISummaryView.h"

UISummaryView::UISummaryView()
{
	m_elements = new UIElement*[c_numSUMElements];
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		SUMLayoutSpec spec = c_SUMLayouSpecs[i];
		switch(spec.type) {
			case distance:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF);
				break;
			case energy:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF);
				break;
			case pace:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF);
				break;
			case calories:
				m_elements[i] = new UITextBlock("0", spec.x, spec.y, 0xFF0000FF);
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
		if (m_elements[i] == NULL || !m_elements[i]->LoadTextures(pErrorStr)) {
			fprintf(stderr, "UISummaryView element failed to load\n");
			return false;
		}
	}
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
		if (m_elements[i] == NULL || m_elements[i]->Render(uiMVPMatrixLoc, print3D, isRotated)) {
			fprintf(stderr, "UISummaryView element failed to render\n");
		}
	}
}

void
UISummaryView::Update(UIMessage updateMessage)
{
	
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