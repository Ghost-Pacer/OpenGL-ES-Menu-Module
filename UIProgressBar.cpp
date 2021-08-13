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
 @Input			type				The type of the Bar (R/G/B)
 @Input			x				    The x Position of the Bar
 @Input			y				    The y position of the Bar
 @Input			initialCompletion	The initial progress of the bar
 @Description	Constructs a dynamicall colored progress bar based on the given 
                parameters and class constant values
******************************************************************************/
UIProgressBar::UIProgressBar(PBType type, float x, float y, float initialCompletion)
{
    switch(type) {
        case PBR:
            m_bg = UIImage(c_progBGRTex, x, y, c_defaultPBWidth, c_defaultPBHeight);
            m_progress = UIImage(c_progRTex, x, y, (c_defaultPBWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
            break;
        case PBG:
            m_bg = UIImage(c_progBGGTex, x, y, c_defaultPBWidth, c_defaultPBHeight);
            m_progress = UIImage(c_progGTex, x, y, (c_defaultPBWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
            break;
        case PBB:
            m_bg = UIImage(c_progBGBTex, x, y, c_defaultPBWidth, c_defaultPBHeight);
            m_progress = UIImage(c_progBTex, x, y, (c_defaultPBWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
            break;
        case BrightnessB:
            fprintf(stderr, "Initting blue progbar\n");
            m_bg = UIImage(c_brightBBGTex, x, y, c_defaultBrightWidth, c_defaultPBHeight);
            m_progress = UIImage(c_brightBTex, x, y, (c_defaultBrightWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
            break;
        case BrightnessR:
            m_bg = UIImage(c_brightRBGTex, x, y, c_defaultBrightWidth, c_defaultPBHeight);
            m_progress = UIImage(c_brightRTex, x, y, (c_defaultBrightWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
            break;
        default:
            fprintf(stderr, "Initting default progbar\n");
            m_bg = UIImage(c_progBGRTex, x, y, c_defaultPBWidth, c_defaultPBHeight);
            m_progress = UIImage(c_progRTex, x, y, (c_defaultPBWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
            break;
    }
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
 @Input			initialCompletion	The initial progress of the bar
 @Description	Constructs a progress bar based on  class default values
******************************************************************************/
UIProgressBar::UIProgressBar(float x, float y, float initialCompletion)
{
    m_bg = UIImage(c_progBGRTex, x, y, c_defaultPBWidth, c_defaultPBHeight);
    m_progress = UIImage(c_progRTex, x, y, (c_defaultPBWidth-c_defaultPBInsetX), (c_defaultPBHeight-c_defaultPBInsetY));
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
    m_bg = UIImage(c_progBGRTex, x, y, width, height);
    m_progress = UIImage(c_progRTex, x, y, (width-insetX), (height-insetY));
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

/*!****************************************************************************
 @Function		Render
 @Input			uiMVPMatrixLoc		Address of the shader's MVP matrix
 @Input			printer				UIPrinter object used to display text
 @Description	Renders the object using gl
******************************************************************************/
bool
UIProgressBar::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
    m_bg.Render(uiMVPMatrixLoc, printer);
    m_progress.Render(uiMVPMatrixLoc, printer);

	return true;
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

/*!****************************************************************************
 @Function		Update
 @Input			updateMessage		UIMessage object containing frame info
 @Description	Updates the object based on information passed using UIMessage
******************************************************************************/
void
UIProgressBar::Update(UIMessage updateMessage)
{
	float messageContents = updateMessage.Read(UIStageProgress);
	// fprintf(stderr, "Message received to UIProgressBar, contents: %f\n", messageContents);
	if (messageContents >= 0 && messageContents <= 1) {
		SetCompletion(messageContents);
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
/*!****************************************************************************
 @Function		Delete
 @Description	Frees any memory allocated within the object
******************************************************************************/

void
UIProgressBar::Delete()
{
	return;
}