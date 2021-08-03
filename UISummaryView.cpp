#include "UISummaryView.h"

UISummaryView::UISummaryView()
{
	m_elements = new UIElement*[c_numSUMElements];
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		SUMLayoutSpec spec = c_SUMLayouSpecs[i];
		UICompositeView* completeIcon = new UICompositeView("textContainer.pvr", spec.x, spec.y, spec.width, spec.height);
		switch(spec.type) {
			case SVComplete:
				completeIcon->AddText("Workout Complete", 0xFF0000FF, 40, 0, 0.22, UINone, UIFBold);
				completeIcon->AddImage("checkmark.pvr", -120, 0, 40, 42);
				m_elements[i] = completeIcon;
				break;
			case SVDistance:
				m_elements[i] = new UITextBlock("0", "mi", UIFBold, UIFMedium, spec.x, spec.y, 0xFF0000FF, UIDistanceM);
				break;
			case SVEnergy:
				m_elements[i] = new UITextBlock("0", "kJ", UIFBold, UIFMedium, spec.x, spec.y, 0xFF0000FF, UIEnergyKJ);
				break;
			case SVPace:
				m_elements[i] = new UITextBlock("0", "/mi", UIFBold, UIFMedium, spec.x, spec.y, 0xFF0000FF, UISpeedMPM);
				break;
			case SVCalories:
				m_elements[i] = new UITextBlock("0", "cal", UIFBold, UIFMedium, spec.x, spec.y, 0xFF0000FF, UICalories);
				break;
			case SVBadges:
				m_elements[i] = new UIBadges(spec.x, spec.y);
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
	fprintf(stderr, "Loading summaryview elements\n");
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		fprintf(stderr, "Loading element #%d\n", i);
		if (m_elements[i] == NULL) {
			fprintf(stderr, "NULL element\n");
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
UISummaryView::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		if (m_elements[i] == NULL) {
			continue;
		} else if (!m_elements[i]->Render(uiMVPMatrixLoc, printer)) {
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
	if (m_hidden) {
		return;
	}
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

void
UISummaryView::Delete()
{
	for ( int i = 0; i < c_numSUMElements; i ++ ) {
		if (m_elements != NULL && m_elements[i] != NULL)
		m_elements[i]->Delete();
		delete m_elements[i];
		m_elements[i] = NULL;
	}
}