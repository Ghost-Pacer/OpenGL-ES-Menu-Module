/******************************************************************************

 @File          UIBasicHUD.cpp

 @Title         UIBasicHUD

 @Author        Siddharth Hathi

 @Description   Implements the UIBasicHUD object class defined in UIBasicHUD.h

******************************************************************************/

#include "UIBasicHUD.h"

/*!****************************************************************************
 @Function		Constructor
 @Description	Initializes the UIBH elements
******************************************************************************/
UIBasicHUD::UIBasicHUD()
{
    m_hidden = false;
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        UITextBlock* element = new UITextBlock("0", c_UIBHSpecs[i].subtext, UIFBold, UIFBold, 
            c_UIBHSpecs[i].x, c_UIBHSpecs[i].y, 0xFFFF0000, c_UIBHSpecs[i].updateKey);
        m_elements[i] = element;
    }
}

/*!****************************************************************************
 @Function		LoadTextures
 @Output		pErrorStr		Pointer to the string returned on error
 @Description	Loads the object's textures into graphics memory
******************************************************************************/
bool
UIBasicHUD::LoadTextures(CPVRTString* const pErrorStr)
{
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL && !m_elements[i]->LoadTextures(pErrorStr)) {
            return false;
        }
    }
    return true;
}

/*!****************************************************************************
 @Function		BuildVertices
 @Description	Builds the object's vertex buffers
******************************************************************************/
void
UIBasicHUD::BuildVertices()
{
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL) {
            m_elements[i]->BuildVertices();
        }
    }
}

/*!****************************************************************************
 @Function		Render
 @Input			uiMVPMatrixLoc		Address of the shader's MVP matrix
 @Input			printer				UIPrinter object used to display text
 @Description	Renders the object using gl
******************************************************************************/
bool
UIBasicHUD::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
    if (m_hidden) {
        return true;
    }
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL) {
            m_elements[i]->Render(uiMVPMatrixLoc, printer);
        }
    }
    return true;
}

/*!****************************************************************************
 @Function		Update
 @Input			updateMessage		UIMessage object containing frame info
 @Description	Updates the object based on information passed using UIMessage
******************************************************************************/
void
UIBasicHUD::Update(UIMessage updateMessage)
{
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL) {
            m_elements[i]->Update(updateMessage);
        }
    }
}

/*!****************************************************************************
 @Function		Hide
 @Description	Makes object hidden
******************************************************************************/
void
UIBasicHUD::Hide()
{
    m_hidden = true;
}

/*!****************************************************************************
 @Function		Show
 @Description	Makes object visibile
******************************************************************************/
void
UIBasicHUD::Show()
{
    m_hidden = false;
}

/*!****************************************************************************
 @Function		Delete
 @Description	Frees memory allocated by the object
******************************************************************************/
void
UIBasicHUD::Delete()
{
    if (m_elements == NULL) {
        return;
    }
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL) {
            m_elements[i]->Delete();
            delete m_elements[i];
            m_elements[i] = NULL;
        }
    }
}