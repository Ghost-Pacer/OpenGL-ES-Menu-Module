/******************************************************************************

 @File          UIProgressBar.cpp

 @Title         UIProgressBar

 @Author        Siddharth Hathi

 @Description   Creates the functionality of the PrgoressBar object class.

******************************************************************************/

#include "UIProgressBar.h"

/*!****************************************************************************
 @Function		Constructor
 @Description	Defines default values when a UIProgressBar is constructed without
				arguments
******************************************************************************/
UIProgressBar::UIProgressBar()
{
    m_bg = UIImage();
    m_progress = UIImage();
    m_completion = 0;
    m_width = 0;
    m_height = 0;
    m_insetX = 0; 
    m_insetY = 0;
    m_x = 0;
    m_y = 0;
}

/*!****************************************************************************
 @Function		Constructor
 @Input			x				    The x Position of the Bar
 @Input			y				    The y position of the Bar
 @Input			width			    The width of the image
 @Input			height			    The height of the image
 @Input			insetX			    The horizontal padding of the bar
 @Input			insetY			    The verical padding of the bar
 @Input			initialCompletion	The initial progress of the bar
 @Description	Constructs a progress bar based on the given parameters
******************************************************************************/
UIProgressBar::UIProgressBar(float x, float y, float initialCompletion)
{
    m_bg = UIImage(c_progBGTex, x, y, c_defaultPBWidth, c_defaultPBHeight);
    m_progress = UIImage(c_progTex, x, y, (c_defaultPBWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
    m_completion = initialCompletion;
    m_width = c_defaultPBWidth;
    m_height = c_defaultPBHeight;
    m_insetX = c_defaultPBInsetX; 
    m_insetY = c_defaultPBInsetY;
    m_x = x;
    m_y = y;
}

/*!****************************************************************************
 @Function		Constructor
 @Input			x				    The x Position of the Bar
 @Input			y				    The y position of the Bar
 @Input			width			    The width of the image
 @Input			height			    The height of the image
 @Input			insetX			    The horizontal padding of the bar
 @Input			insetY			    The verical padding of the bar
 @Input			initialCompletion	The initial progress of the bar
 @Description	Constructs a progress bar based on the given parameters
******************************************************************************/
UIProgressBar::UIProgressBar(float x, float y, float width, float height, float insetX, float insetY, float initialCompletion)
{
    m_bg = UIImage(c_progBGTex, x, y, width, height);
    m_progress = UIImage(c_progTex, x, y, (width-insetX), (height-insetY));
    m_completion = initialCompletion;
    m_width = width;
    m_height = height;
    m_insetX = insetX; 
    m_insetY = insetY;
    m_x = x;
    m_y = y;
}

/*!****************************************************************************
 @Function		LoadTextures
 @Output		pErrorStr	Error message on failure
 @Description	Loads the textures of the UIProgressBar's UIImages
******************************************************************************/
bool
UIProgressBar::LoadTextures(CPVRTString* const pErrorStr)
{
    if (!m_bg.LoadTextures(pErrorStr) || !m_progress.LoadTextures(pErrorStr)) {
        return false;
    }
    return true;
}

/*!****************************************************************************
 @Function		Build
 @Description	Creates and defines the vertices and vbos for the bar
******************************************************************************/
void
UIProgressBar::BuildVertices()
{
    m_bg.BuildVertices();
    m_progress.BuildVertices();
    m_progress.Scale(m_completion, 1, 1);
    m_progress.Move((m_width-m_insetX)*(m_completion-1)/2, 0);
}

/*!****************************************************************************
 @Function		Render
 @Input			uiMVPMatrixLoc	GLuint reference to the shader Matrix
 @Description	Sets up vertex arrays and draws the bar
******************************************************************************/
bool
UIProgressBar::Render(GLuint uiMVPMatrixLoc)
{

    m_bg.Render(uiMVPMatrixLoc);
    m_progress.Render(uiMVPMatrixLoc);

	return true;
}

bool
UIProgressBar::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
{
   return false;
}

/*!****************************************************************************
 @Function		SetCompletion
 @Input         newCompletion   The new completion value for the bar
 @Description	Sets the extent to which the progress bar is filled
******************************************************************************/
void
UIProgressBar::SetCompletion(float newCompletion)
{
    float xTranslation = (m_width-m_insetX)*(newCompletion-m_completion)/2;
    m_progress.Scale(newCompletion, 1, 1);
    m_progress.Move(xTranslation, 0);
    m_completion = newCompletion;
}

/*!****************************************************************************
 @Function		GetCompletion
 @Return        float   The progress bar's completion
 @Description	Returns the bar's completion
******************************************************************************/
float
UIProgressBar::GetCompletion()
{
    return m_completion;
}

void
UIProgressBar::UpdateFrame(CPVRTMap<char*, void*> valueMap)
{
	if (valueMap.Exists("PBCompletion")) {
		float newCompletion = *(float*)(valueMap["PBCompletion"]);
		SetCompletion(newCompletion);
	} else {
		fprintf(stderr, "Invalid call to UIProgressBar->UpdateFrame");
		return;
	}
}

/*!****************************************************************************
 @Function		Hide
 @Description	Hides the bar
******************************************************************************/
void
UIProgressBar::Hide()
{
    m_bg.Hide();
	m_progress.Hide();
}

/*!****************************************************************************
 @Function		Show
 @Description	Shows the bar
******************************************************************************/
void
UIProgressBar::Show()
{
    m_progress.Show();
	m_bg.Show();
}

bool
UIProgressBar::Text()
{
	return false;
}