#include "UITextBlock.h"

UITextBlock::UITextBlock()
{
    m_bg = UIImage();
    m_text = NULL;
    m_x = 0;
    m_y = 0;
    m_width = 0;
    m_height = 0;
    m_insetX = 0;
    m_insetY = 0;
    m_print2D = NULL;
}

UITextBlock::UITextBlock(char* bg, char* text, float x, float y, float width, float height, float insetX, float insetY, float textScale, GLuint color)
{
    m_bg = UIImage(bg, x, y, width, height);
    m_text = text;
    m_x = x;
    m_y = y;
    m_insetX = insetX;
    m_insetY = insetY;
    m_textScale = textScale;
    m_color = color;
    m_print2D = NULL;
}

bool
UITextBlock::LoadTextures(CPVRTString* const pErrorStr)
{
    return m_bg.LoadTextures(pErrorStr);
}

void
UITextBlock::BuildVertices()
{
    m_bg.BuildVertices();
}

bool
UITextBlock::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
{
    GLint viewport[4];
    GLint vWidth;                           // Viewport width
    GLint vHeight;                          // Viewport height
	glGetIntegerv(GL_VIEWPORT, viewport);

	vWidth = viewport[2];
	vHeight = viewport[3];
	// fprintf(stderr, "Viewport dimensions: %d %d\n", vWidth, vHeight);

    m_bg.Render(uiMVPMatrixLoc);

    m_print2D = new Print2D(print3D, isRotated);

	// fprintf(stderr, "Text coordinates: %f %f\n", (100*(m_x - m_insetX)/vWidth)+50, (100*(m_y - m_insetY)/vHeight)+50);
    m_print2D -> renderText((100*(m_x - m_insetX)/vWidth)+50, (100*(m_y - m_insetY)/vHeight)+50, m_textScale, m_color, m_text);
	
    // m_print2D -> renderText(0, 0, m_textScale, m_color, m_text);
    return true;
}

/*!****************************************************************************
 @Function		Render
 @Description	UITextBlock implements a different version of UIElement::Render
******************************************************************************/
bool
UITextBlock::Render(GLuint uiMVPMatrixLoc)
{
    return false;
}

bool
UITextBlock::Text()
{
    return true;
}