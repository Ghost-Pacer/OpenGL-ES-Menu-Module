/******************************************************************************

 @File          UIProgressBar.h

 @Title         UIProgressBar Header File 

 @Author        Siddharth Hathi

 @Description   Header file for UIProgressBar.cpp

******************************************************************************/

#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"

#ifndef _UIPROGRESSBAR_H
#define _UIPROGRESSBAR_H

// Names of pvr textures for the bar and it's background
const char c_progBGRTex[] = "progBGR.pvr";
const char c_progRTex[] = "progR.pvr";
const char c_progBGBTex[] = "progBGB.pvr";
const char c_progBTex[] = "progB.pvr";
const char c_progBGGTex[] = "progBGG.pvr";
const char c_progGTex[] = "progG.pvr";

const float c_defaultPBWidth = 350;
const float c_defaultPBHeight = 18;
const float c_defaultPBInsetX = 12;
const float c_defaultPBInsetY = 12;

enum PBType { PBR, PBG, PBB };

/*!****************************************************************************
 Object Class. A UIProgressBar is a C++ class that displays a Progress Bar that can
 be dynamically animated. It contains functionality for loading, building, rendering 
 and modifying the Progress Bar. It's functionality is implemented in UIProgressBar.cpp
******************************************************************************/
class UIProgressBar : public UIElement
{
    protected:
        // instance variables
        UIImage m_bg;
        UIImage m_progress;
        float m_completion, m_width, m_height, m_insetX, m_insetY, m_x, m_y;
    public:
        // functions
        UIProgressBar();
        UIProgressBar(float x, float y, float initialCompletion);
        UIProgressBar(PBType type, float x, float y, float initialCompletion);
        UIProgressBar(float x, float y, float width, float height, float insetX, float insetY, float initialCompletion);
		virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
		virtual bool Render(GLuint uiMVPMatrixLoc);
		virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer) { return true; };
        void SetCompletion(float newCompletion);
        float GetCompletion();
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		bool Text();
};

#endif _UIPROGRESSBAR_H