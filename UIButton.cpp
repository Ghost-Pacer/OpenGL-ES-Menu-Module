#include "UIButton.h"

UIButton::UIButton()
{
    m_activeBG = UIImage();
	m_inactiveBG = UIImage();
    m_text = NULL;
    m_x = 0;
    m_y = 0;
    m_width = 0;
    m_height = 0;
    m_insetX = 0;
    m_insetY = 0;
    m_print2D = NULL;
}

UIButton::UIButton(char* text, float x, float y, GLuint color)
{
	m_activeBG = UIImage(c_UIBDefaults.activeBG, x, y, c_UIBDefaults.width, c_UIBDefaults.height);
	m_inactiveBG = UIImage(c_UIBDefaults.inactiveBG, x, y, c_UIBDefaults.width, c_UIBDefaults.height);
	m_text = text;
	m_x = x;
	m_y = y;
	m_insetX = c_UIBDefaults.insetX;
	m_insetY = c_UIBDefaults.insetY;
	m_textScale = c_UIBDefaults.textScale;
	m_color = color;
	m_print2D = NULL;
}

UIButton::UIButton(char* activeBG, char* inactiveBG, char* text, float x, float y, float width, float height, float insetX, float insetY, float textScale, GLuint color)
{
    m_activeBG = UIImage(activeBG, x, y, width, height);
	m_inactiveBG = UIImage(inactiveBG, x, y, width, height);
    m_text = text;
    m_x = x;
    m_y = y;
    m_insetX = insetX;
    m_insetY = insetY;
    m_textScale = textScale;
    m_color = color;
    m_print2D = NULL;
}

void
UIButton::ToggleActive()
{
	m_active = !m_active;
}

bool
UIButton::LoadTextures(CPVRTString* const pErrorStr)
{
    return (m_activeBG.LoadTextures(pErrorStr) && m_inactiveBG.LoadTextures(pErrorStr));
}

void
UIButton::BuildVertices()
{
    m_activeBG.BuildVertices();
	m_inactiveBG.BuildVertices();
}

bool
UIButton::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
{
    GLint viewport[4];
    GLint vWidth;                           // Viewport width
    GLint vHeight;                          // Viewport height
	glGetIntegerv(GL_VIEWPORT, viewport);

	vWidth = viewport[2];
	vHeight = viewport[3];
	// fprintf(stderr, "Viewport dimensions: %d %d\n", vWidth, vHeight);

	if (m_active) {
		m_activeBG.Render(uiMVPMatrixLoc);
	} else {
		m_inactiveBG.Render(uiMVPMatrixLoc);
	}

    m_print2D = new Print2D(print3D, isRotated);

	float textWidth;
	float textHeight;

	print3D->MeasureText(&textWidth, &textHeight, m_textScale, m_text);

	// fprintf(stderr, "Text coordinates: %f %f\n", (100*(m_x - m_insetX)/vWidth)+50, (100*(m_y - m_insetY)/vHeight)+50);
    m_print2D -> renderText((100*(m_x - (textWidth+m_insetX)/2)/vWidth)+50, -(100*(m_y + (textHeight+m_insetY)/2)/vHeight)+50, m_textScale, m_color, m_text);
	
    // m_print2D -> renderText(0, 0, m_textScale, m_color, m_text);
    return true;
}

/*!****************************************************************************
 @Function		Render
 @Description	UITextBlock implements a different version of UIElement::Render
******************************************************************************/
bool
UIButton::Render(GLuint uiMVPMatrixLoc)
{
    return false;
}

bool
UIButton::Text()
{
    return true;
}