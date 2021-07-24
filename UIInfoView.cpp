#include "UIInfoView.h"

UIInfoView::UIInfoView()
{
	m_state = main;
	hidden = true;
}

UIInfoView::UIInfoView(IVState startingState)
{
	m_state = startingState;
	hidden = false;

	// Add UIElements
	UIElement* mainElements[c_ivNumElementPositions];
	UIElement* infoElements[c_ivNumElementPositions];
	UIElement* pauseElements[c_ivNumElementPositions];

	for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
		switch(c_IVLayoutSpecs[i].type) {
			case leftTV:
				mainElements[i] = new UITextBlock("0", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVDefaultTextColor);
				infoElements[i] = new UITextBlock("0", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVDefaultTextColor);
				pauseElements[i] = NULL;
			case rightTV:
				mainElements[i] = new UITextBlock("0", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVDefaultTextColor);
				infoElements[i] = new UITextBlock("0", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVDefaultTextColor);
				pauseElements[i] = NULL;
			case progBG:
				mainElements[i], infoElements[i], pauseElements[i] = new UIImage("progContainer.pvr", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVLayoutSpecs[i].width, c_IVLayoutSpecs[i].height);
			case warmup:
				mainElements[i], infoElements[i], pauseElements[i] = new UIImage("warmupActive.pvr", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVLayoutSpecs[i].width, c_IVLayoutSpecs[i].height);
			case workout:
				mainElements[i], infoElements[i], pauseElements[i] = new UIImage("workoutActive.pvr", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVLayoutSpecs[i].width, c_IVLayoutSpecs[i].height);
			case cooldown:
				mainElements[i], infoElements[i], pauseElements[i] = new UIImage("coolDownAct.pvr", c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, c_IVLayoutSpecs[i].width, c_IVLayoutSpecs[i].height);
			case progBar:
				mainElements[i], infoElements[i], pauseElements[i] = new UIProgressBar(c_IVLayoutSpecs[i].x, c_IVLayoutSpecs[i].y, 1);
		}
	}

	m_stateMap[main] = mainElements;
	m_stateMap[info] = infoElements;
	m_stateMap[pause] = pauseElements;
}

bool
UIInfoView::LoadTextures(CPVRTString* const pErrorString)
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] == NULL || elementArray[i]->LoadTextures(pErrorString)) {
				return false;
			}
		}
	}
}

void
UIInfoView::BuildVertices()
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->BuildVertices();
			}
		}
	}
}

bool
UIInfoView::Render(GLuint uiMVPMatrixLoc)
{
	return false;
}

bool
UIInfoView::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
{
	UIElement** elementArray = m_stateMap[m_state];

	if (elementArray != NULL) {
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				if (!elementArray[i]->Render(uiMVPMatrixLoc, print3D, isRotated)) {
					fprintf(stderr, "UIElement render failed\n");
				}
			}
		}
	}
}

bool
UIInfoView::Text()
{
	return true;
}

void
UIInfoView::UpdateFrame(CPVRTMap<char*, void*> valueMap)
{
	UIElement** elementArray = m_stateMap[m_state];

	if (elementArray != NULL) {
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->UpdateFrame(valueMap);
			}
		}
	}
}

void
UIInfoView::Hide()
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->Hide();
			}
		}
	}
}

void
UIInfoView::Show()
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->Show();
			}
		}
	}
}

void
UIInfoView::SetState(IVState state)
{
	this->m_state = state;
	for (int i = main; i != end; i ++) {
		IVState iState = static_cast<IVState>(i);
		UIElement** elementArray = m_stateMap[iState];
		for (int i = 0 ; i < c_ivNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				if (iState == m_state) {
					elementArray[i]->Show();
				} else {
					elementArray[i]->Hide();
				}
			}
		}
	}
}

IVState
UIInfoView::GetState()
{
	return m_state;
}