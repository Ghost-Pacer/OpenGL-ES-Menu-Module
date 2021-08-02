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
    // m_print2D = NULL;
}

UIButton::UIButton(char* text, float x, float y, GLuint activeColor, GLuint inactiveColor)
{
	m_activeBG = UIImage(c_UIBDefaults.activeBG, x, y, c_UIBDefaults.width, c_UIBDefaults.height);
	m_inactiveBG = UIImage(c_UIBDefaults.inactiveBG, x, y, c_UIBDefaults.width, c_UIBDefaults.height);
	m_text = text;
	m_x = x;
	m_y = y;
	m_insetX = c_UIBDefaults.insetX;
	m_insetY = c_UIBDefaults.insetY;
	m_textScale = c_UIBDefaults.textScale;
	m_activeColor = activeColor;
	m_inactiveColor = inactiveColor;
	m_font = c_UIBDefaults.font;
	// m_print2D = NULL;
}

UIButton::UIButton(char* activeBG, char* inactiveBG, char* text, float x, float y, float width, float height, 
	float insetX, float insetY, float textScale, GLuint activeColor, GLuint inactiveColor, UIFont font)
{
    m_activeBG = UIImage(activeBG, x, y, width, height);
	m_inactiveBG = UIImage(inactiveBG, x, y, width, height);
    m_text = text;
    m_x = x;
    m_y = y;
    m_insetX = insetX;
    m_insetY = insetY;
    m_textScale = textScale;
	m_activeColor = activeColor;
	m_inactiveColor = inactiveColor;
    // m_print2D = NULL;
	m_font = font;
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

// bool
// UIButton::Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated)
// {
//     GLint viewport[4];
//     GLint vWidth;                           // Viewport width
//     GLint vHeight;                          // Viewport height
// 	glGetIntegerv(GL_VIEWPORT, viewport);

// 	vWidth = viewport[2];
// 	vHeight = viewport[3];

// 	if (m_active) {
// 		m_activeBG.Render(uiMVPMatrixLoc);
// 	} else {
// 		m_inactiveBG.Render(uiMVPMatrixLoc);
// 	}

//     m_print2D = new Print2D(print3D, isRotated);

// 	float textWidth;
// 	float textHeight;

// 	print3D->MeasureText(&textWidth, &textHeight, m_textScale, m_text);

// 	GLuint textColor;
// 	if (m_active) {
// 		textColor = m_activeColor;
// 		// fprintf(stderr, "Active status + %d\n", m_active);
// 		// fprintf(stderr, "Text color : %x\n", textColor);
// 	} else {
// 		textColor = m_inactiveColor;
// 		// fprintf(stderr, "Text color : %x\n", textColor);
// 	}
//     m_print2D -> renderText((100*(m_x - (textWidth+m_insetX)/2)/vWidth)+50, -(100*(m_y + (textHeight+m_insetY)/2)/vHeight)+50, m_textScale, textColor, m_text);
	
//     return true;
// }

bool
UIButton::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
    GLint viewport[4];
    GLint vWidth;                           // Viewport width
    GLint vHeight;                          // Viewport height
	glGetIntegerv(GL_VIEWPORT, viewport);

	vWidth = viewport[2];
	vHeight = viewport[3];

	if (m_active) {
		m_activeBG.Render(uiMVPMatrixLoc);
	} else {
		m_inactiveBG.Render(uiMVPMatrixLoc);
	}

	GLuint textColor;
	if (m_active) {
		textColor = m_activeColor;
		// fprintf(stderr, "Active status + %d\n", m_active);
		// fprintf(stderr, "Text color : %x\n", textColor);
	} else {
		textColor = m_inactiveColor;
		// fprintf(stderr, "Text color : %x\n", textColor);
	}
    printer -> Print(m_x, m_y, m_textScale, textColor, m_font, m_text);
	
    return true;
}

void
UIButton::Update(UIMessage updateMessage)
{
	m_active = updateMessage.Read(UIButtonActive);
	fprintf(stderr, "Active status + %d\n", m_active);
}

void
UIButton::Hide()
{
	m_hidden = true;
}

void
UIButton::Show()
{
	m_hidden = false;
}

void
UIButton::Delete()
{
	return;
}