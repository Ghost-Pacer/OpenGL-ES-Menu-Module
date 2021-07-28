#include "UITopView.h"

UITopView::UITopView()
{
	m_state = UIMain;
	m_hidden = true;
}

UITopView::UITopView(UIState startingState, UIWorkoutStage startingWorkoutMode)
{
	m_state = startingState;
	m_startingWorkoutMode = startingWorkoutMode;
	m_hidden = false;

	// Add UIElements
	UIElement** mainElements = new UIElement*[c_tvNumElementPositions];
	UIElement** infoElements = new UIElement*[c_tvNumElementPositions];
	UIElement** pauseElements = new UIElement*[c_tvNumElementPositions];

	for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
		switch(c_TVLayoutSpecs[i].type) {
			case TVLeftTB:
				mainElements[i] = new UITextBlock("0", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVDefaultTextColor);
				infoElements[i] = new UITextBlock("0", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVDefaultTextColor);
				pauseElements[i] = NULL;
				break;
			case TVRightTB:
				mainElements[i] = new UITextBlock("0", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVDefaultTextColor);
				infoElements[i] = new UITextBlock("0", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVDefaultTextColor);
				pauseElements[i] = NULL;
				break;
			case TVWorkoutView:
				mainElements[i] = new UIWorkoutView(m_startingWorkoutMode);
				infoElements[i] = mainElements[i];
				pauseElements[i] = mainElements[i];
				break;
			/*
			case progBG:
				mainElements[i] = new UIImage("progContainer.pvr", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVLayoutSpecs[i].width, c_TVLayoutSpecs[i].height);
				infoElements[i] = mainElements[i], pauseElements[i] = mainElements[i];
				break;
			case warmup:
				mainElements[i] = new UIImage("warmupActive.pvr", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVLayoutSpecs[i].width, c_TVLayoutSpecs[i].height);
				infoElements[i] = mainElements[i], pauseElements[i] = mainElements[i];
				break;
			case workout:
				mainElements[i] = new UIImage("workoutActive.pvr", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVLayoutSpecs[i].width, c_TVLayoutSpecs[i].height);
				infoElements[i] = mainElements[i], pauseElements[i] = mainElements[i];
				break;
			case cooldown:
				mainElements[i] = new UIImage("coolDownAct.pvr", c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, c_TVLayoutSpecs[i].width, c_TVLayoutSpecs[i].height);
				infoElements[i] = mainElements[i], pauseElements[i] = mainElements[i];
				break;
			case progBar:
				mainElements[i] = new UIProgressBar(c_TVLayoutSpecs[i].x, c_TVLayoutSpecs[i].y, 1);
				infoElements[i] = mainElements[i], pauseElements[i] = mainElements[i];
				break;
			*/
			default:
				mainElements[i] = NULL, infoElements[i] = NULL, pauseElements[i] = NULL;
				break;
		}
	}

	m_stateMap[UIMain] = mainElements;
	m_stateMap[UIInfo] = infoElements;
	m_stateMap[UIPause] = pauseElements;
	m_stateMap[UISummary] = NULL;

	// fprintf(stderr, "Map size: %d\n", m_stateMap.GetSize());
	// for (int i = main; i != end; i ++) {
	// 	fprintf(stderr, "State: %d\n", i);
	// 	TVState iState = static_cast<TVState>(i);
	// 	UIElement** elementArray = m_stateMap[iState];
	// 	fprintf(stderr, "Array pointer %p: \n", elementArray);
	// 	fprintf(stderr, "Size: %d\n", sizeof(elementArray));
	// 	if (elementArray == NULL) {
	// 		continue;
	// 	}
	// 	for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
	// 		fprintf(stderr, "Element array index %d\n", i);
	// 		if (elementArray[i] != NULL) {
	// 			fprintf(stderr, "Non-null element %p\n", elementArray[i]);
	// 			fprintf(stderr, "Textual element? %d\n", elementArray[i]->Text());
	// 			// if (!elementArray[i]->LoadTextures(pErrorString)) {
	// 			// 	fprintf(stderr, "Texture failed to load\n");
	// 			// }
	// 		}
	// 	}
	// }
}

bool
UITopView::LoadTextures(CPVRTString* const pErrorString)
{
	if (m_stateMap.GetSize() < 1) {
		return false;
	}
	fprintf(stderr, "Map size: %d\n", m_stateMap.GetSize());
	for (int i = UIMain; i != UISummary; i ++) {
		fprintf(stderr, "State: %d\n", i);
		UIState iState = static_cast<UIState>(i);
		UIElement** elementArray = m_stateMap[iState];
		fprintf(stderr, "Array pointer %p: \n", elementArray);
		fprintf(stderr, "Size: %d\n", sizeof(elementArray));
		if (elementArray == NULL) {
			continue;
		}
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
			fprintf(stderr, "Element array index %d\n", i);
			if (elementArray[i] != NULL) {
				fprintf(stderr, "Non-null element %p\n", elementArray[i]);
				//fprintf(stderr, "Textual element? %d\n", elementArray[i]->Text());
				if (!elementArray[i]->LoadTextures(pErrorString)) {
					fprintf(stderr, "Texture failed to load\n");
				}
			}
		}
	}
	return true;
}

void
UITopView::BuildVertices()
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		if (elementArray == NULL) {
			continue;
		}
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->BuildVertices();
			}
		}
	}
}

bool
UITopView::Render(GLuint uiMVPMatrixLoc)
{
	return false;
}

bool
UITopView::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
{
	if (m_hidden) {
		return true;
	}

	UIElement** elementArray = m_stateMap[m_state];

	if (elementArray != NULL) {
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				if (!elementArray[i]->Render(uiMVPMatrixLoc, print3D, isRotated)) {
					// fprintf(stderr, "UIElement %d  render failed\n", i);
				} else {
					// fprintf(stderr, "UIElement %d rendered\n", i);
				}
			}
		}
		return true;
	}
	return false;
}

bool
UITopView::Text()
{
	return true;
}

void
UITopView::Update(UIMessage updateMessage)
{
	if (updateMessage.ReadState() == UISummary) {
		m_hidden = true;
		return;
	}
	m_state = updateMessage.ReadState();
	UIElement** elementArray = m_stateMap[m_state];
	UIMessage delegateMessage;
	if (elementArray != NULL) {
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
			if (elementArray[i] == NULL) {
				continue;
			}
			if (c_TVLayoutSpecs[i].type == TVLeftTB && m_state == UIMain) {
				fprintf(stderr, "Message sent from UITopView\n");
				delegateMessage = updateMessage.Delegate(UIRank);
				elementArray[i]->Update(delegateMessage);
			} else if (c_TVLayoutSpecs[i].type == TVRightTB && m_state == UIMain) {
				fprintf(stderr, "Message sent from UITopView\n");
				delegateMessage = updateMessage.Delegate(UIEnergyKJ);
				elementArray[i]->Update(delegateMessage);
			} else if (c_TVLayoutSpecs[i].type == TVLeftTB && m_state == UIInfo) {
				fprintf(stderr, "Message sent from UITopView\n");
				delegateMessage = updateMessage.Delegate(UIDistanceM);
				elementArray[i]->Update(delegateMessage);
			} else if (c_TVLayoutSpecs[i].type == TVRightTB && m_state == UIInfo) {
				fprintf(stderr, "Message sent from UITopView\n");
				delegateMessage = updateMessage.Delegate(UISpeedMPM);
				elementArray[i]->Update(delegateMessage);
			} else if (c_TVLayoutSpecs[i].type == TVWorkoutView) {
				fprintf(stderr, "Message sent from UITopView\n");
				delegateMessage = updateMessage.Delegate(UIStageProgress);
				elementArray[i]->Update(delegateMessage);
			}
		}
	}
}

void
UITopView::Hide()
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->Hide();
			}
		}
	}
}

void
UITopView::Show()
{
	for (int i = 0; i < m_stateMap.GetSize(); i ++) {
		UIElement** elementArray = *m_stateMap.GetDataAtIndex(i);
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
			if (elementArray[i] != NULL) {
				elementArray[i]->Show();
			}
		}
	}
}

void
UITopView::SetState(UIState state)
{
	this->m_state = state;
	for (int i = UIMain; i != UISummary; i ++) {
		UIState iState = static_cast<UIState>(i);
		UIElement** elementArray = m_stateMap[iState];
		for (int i = 0 ; i < c_tvNumElementPositions; i ++) {
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

UIState
UITopView::GetState()
{
	return m_state;
}