/******************************************************************************

 @File          UIPauseView.h

 @Title         UIPauseView Header File 

 @Author        Siddharth Hathi

 @Description   Header file for the UIPauseView class.

******************************************************************************/

#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "UIButton.h"

#ifndef _UIPAUSEVIEW_H
#define _UIPAUSEVIEW_H

// Enum identifiers for fixed view elements
enum PVElement { PVIcon, PVResumeButton, PVEndButton };

// Data structure for element positioning and layout
struct PVLayoutSpec {
	PVElement type;
	float x, y, width, height;
};

// Global constant number of UIPauseView UIElements
const int c_numPVElements = 3;

// Global constant array of element layout specifications 
const PVLayoutSpec c_PVLayoutSpecs[] = {
	{ PVIcon, 0, 0, 85, 115 },
	{ PVResumeButton, 0, -190, 360, 40 },
	{ PVEndButton, 0, -255, 360, 40 }
};

/*!****************************************************************************
 @class UIElement
Object class. The UIPauseView is container UIElement used to house and display
all the UIElements visible when a peloton workout is paused.
******************************************************************************/
class UIPauseView : public UIElement
{
	protected:
		// Instance variables:
		
		// Child elements
		UIElement** m_elements;

		// Is the UIPV hidden?
		bool m_hidden;

		// Is the resume button selected?
		bool m_resume;
		
	public:
		// Exported functions
		UIPauseView();
		virtual bool LoadTextures(CPVRTString* const pErrorString);
		virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		bool ResumeSelected();
		void Delete();
};

#endif