#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIMessage.h"
#include "UIImage.h"
#include "UIProgressBar.h"

#ifndef _UIWORKOUTVIEW_H
#define _UIWORKOUTVIEW_H

enum WVElement { wvBG, wvWarmupIconActive, wvWarmupIconInactive, 
                    wvWorkoutIconActive, wvWorkoutIconInactive,
                    wvCooldownIconActive, wvCooldownIconInactive,
                    wvProgressBarRed, wvProgressBarGreen, wvProgressBarBlue };

struct WVLayoutSpec {
    WVElement type;
    float x, y, width, height;
};

const int c_numWVLayoutSpecs = 10;

const WVLayoutSpec c_wvLayoutSpecs[] = {
    { wvBG, 0, 235, 450, 30 },
    { wvWarmupIconActive, -200, 235, 12, 16 },
    { wvWarmupIconInactive, -200, 235, 12, 16 },
    { wvWorkoutIconActive, -176, 235, 12, 16 },
    { wvWorkoutIconInactive, -176, 235, 12, 16 },
    { wvCooldownIconActive, -152, 235, 12, 16 }, 
    { wvCooldownIconInactive, -152, 235, 12, 16 },
    { wvProgressBarRed, 40, 235, 450, 30 },
    { wvProgressBarGreen, 40, 235, 450, 30 },
    { wvProgressBarBlue, 40, 235, 450, 30 }
};

class UIWorkoutView : public UIElement
{
    protected:
        bool m_hidden;
        UIWorkoutStage m_state;
        CPVRTMap<UIWorkoutStage, UIElement**> m_stateMap;
    public:
        UIWorkoutView();
        UIWorkoutView(UIWorkoutStage startingState);
		virtual bool LoadTextures(CPVRTString* const pErrorString);
		virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		virtual void Delete();
};

#endif