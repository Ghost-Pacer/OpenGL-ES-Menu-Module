#include "UIBasicHUD.h"

UIBasicHUD::UIBasicHUD()
{
    m_hidden = false;
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        UITextBlock* element = new UITextBlock("0", c_UIBHSpecs[i].subtext, UIFBold, UIFBold, 
            c_UIBHSpecs[i].x, c_UIBHSpecs[i].y, 0xFFFF0000, c_UIBHSpecs[i].updateKey);
        m_elements[i] = element;
    }
}

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

void
UIBasicHUD::BuildVertices()
{
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL) {
            m_elements[i]->BuildVertices();
        }
    }
}

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

void
UIBasicHUD::Update(UIMessage updateMessage)
{
    for ( int i = 0; i < c_numBHElements; i ++ ) {
        if (m_elements[i] != NULL) {
            m_elements[i]->Update(updateMessage);
        }
    }
}

void
UIBasicHUD::Hide()
{
    m_hidden = true;
}

void
UIBasicHUD::Show()
{
    m_hidden = false;
}

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