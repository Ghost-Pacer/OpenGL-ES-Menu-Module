#include "UIWorkoutView.h"

UIWorkoutView::UIWorkoutView(UIWorkoutStage startingState)
{
    m_state = startingState;
    m_hidden = false;

    UIElement** warmupElements = new UIElement*[c_numWVLayoutSpecs];
    UIElement** workoutElements = new UIElement*[c_numWVLayoutSpecs];
    UIElement** cooldownElements = new UIElement*[c_numWVLayoutSpecs];

    for (int i = 0 ; i < c_numWVLayoutSpecs; i ++ ) {
        WVLayoutSpec spec = c_wvLayoutSpecs[i];
        switch(spec.type) {
            case wvBG:
                warmupElements[i] = new UIImage("progContainer.pvr", spec.x, spec.y, spec.width, spec.height);
                workoutElements[i] = warmupElements[i];
                cooldownElements[i] = warmupElements[i];
                break;
            case wvWarmupIconActive:
                warmupElements[i] = new UIImage("warmupActive.pvr", spec.x, spec.y, spec.width, spec.height);
                workoutElements[i] = NULL;
                cooldownElements[i] = NULL;
                break;
            case wvWarmupIconInactive:
                warmupElements[i] = NULL;
                workoutElements[i] = new UIImage("warmupInactive.pvr", spec.x, spec.y, spec.width, spec.height);
                cooldownElements[i] =  workoutElements[i];
                break;
            case wvWorkoutIconActive:
                workoutElements[i] = new UIImage("workoutActive.pvr", spec.x, spec.y, spec.width, spec.height);
                warmupElements[i] = NULL;
                cooldownElements[i] = NULL;
                break;
            case wvWorkoutIconInactive:
                workoutElements[i] = NULL;
                warmupElements[i] = new UIImage("workoutInactive.pvr", spec.x, spec.y, spec.width, spec.height);
                cooldownElements[i] =  warmupElements[i];
                break;
            case wvCooldownIconActive:
                cooldownElements[i] = new UIImage("coolDownAct.pvr", spec.x, spec.y, spec.width, spec.height);
                workoutElements[i] = NULL;
                warmupElements[i] = NULL;
                break;
            case wvCooldownIconInactive:
                cooldownElements[i] = NULL;
                workoutElements[i] = new UIImage("coolDownInact.pvr", spec.x, spec.y, spec.width, spec.height);
                warmupElements[i] =  workoutElements[i];
                break;
            case wvProgressBarGreen:
                warmupElements[i] = new UIProgressBar(PBType::PBG, spec.x, spec.y, 1.f);
                workoutElements[i] = NULL;
                cooldownElements[i] = NULL;
                break;
            case wvProgressBarRed:
                workoutElements[i] = new UIProgressBar(PBType::PBR, spec.x, spec.y, 1.f);
                warmupElements[i] = NULL;
                cooldownElements[i] = NULL;
                break;
            case wvProgressBarBlue:
                cooldownElements[i] = new UIProgressBar(PBType::PBB, spec.x, spec.y, 1.f);
                workoutElements[i] = NULL;
                warmupElements[i] = NULL;
                break;
            default:
                warmupElements[i] = NULL;
                cooldownElements [i] = NULL;
                warmupElements[i] = NULL;
                break;
        }
    }
    m_stateMap[UIWarmup] = warmupElements;
    m_stateMap[UIWorkout] = workoutElements;
    m_stateMap[UICooldown] = cooldownElements;
}

bool
UIWorkoutView::LoadTextures(CPVRTString* const pErrorString)
{
    for ( int i = UIWarmup; i <= UICooldown; i ++ ) {
        UIWorkoutStage iState = static_cast<UIWorkoutStage>(i);
        if (!m_stateMap.Exists(iState)) {
            continue;
        }
        UIElement** elementArray = m_stateMap[iState];
        if (elementArray == NULL) {
            continue;
        }
        for ( int i = 0; i < c_numWVLayoutSpecs; i ++ ) {
            if (elementArray[i] == NULL) {
                continue;
            }
            
            if (!elementArray[i]->LoadTextures(pErrorString)) {
                fprintf(stderr, "UIWorkoutView texture %d load failed\n", i);
                return false;
            } else {
                // fprintf(stderr, "UIWorkoutView texture loaded\n");
            }
        }
    }
    return true;
}

void
UIWorkoutView::BuildVertices()
{
    for ( int i = UIWarmup; i <= UICooldown; i ++ ) {
        UIWorkoutStage iState = static_cast<UIWorkoutStage>(i);
        if (!m_stateMap.Exists(iState)) {
            continue;
        }
        UIElement** elementArray = m_stateMap[iState];
        if (elementArray == NULL) {
            continue;
        }
        for ( int i = 0; i < c_numWVLayoutSpecs; i ++ ) {
            if (elementArray[i] == NULL) {
                continue;
            }
            elementArray[i]->BuildVertices();
        }
    }
}

bool
UIWorkoutView::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (!m_stateMap.Exists(m_state)) {
        return false;
    }
    UIElement** elementArray = m_stateMap[m_state];
    if (elementArray == NULL) {
        return true;
    }
    for ( int i = 0; i < c_numWVLayoutSpecs; i ++ ) {
        if (elementArray[i] == NULL) {
            continue;
        } else if (!elementArray[i]->Render(uiMVPMatrixLoc, printer)) {
            fprintf(stderr, "UIWorkoutView element %d render failed\n", i);
        }
    }
    return true;
}

void
UIWorkoutView::Update(UIMessage updateMessage)
{
	m_state = updateMessage.ReadWorkoutStage();

    UIElement** elementArray = m_stateMap[m_state];
	UIMessage delegateMessage;
	if (elementArray != NULL) {
		for (int i = 0 ; i < c_numWVLayoutSpecs; i ++) {
			if (elementArray[i] == NULL) {
				continue;
			}
            WVElement type = c_wvLayoutSpecs[i].type;
			if (type == wvProgressBarRed || type == wvProgressBarGreen 
                    || type == wvProgressBarBlue) {
                //fprintf(stderr, "Valid message received in UIWorkoutView\n");
				delegateMessage = updateMessage.Delegate(UIStageProgress);
				elementArray[i]->Update(delegateMessage);
			}
		}
	}
}

void
UIWorkoutView::Hide()
{
    m_hidden = true;
}

void
UIWorkoutView::Show()
{
    m_hidden = false;
}