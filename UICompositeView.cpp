#include "UICompositeView.h"

UICompositeView::UICompositeView(float x, float y)
{
	m_bg = UIImage(c_bgTexDefault, x, y, c_bgWidthDefault, c_bgHeightDefault);
	m_x = x;
	m_y = y;
	m_width = c_bgWidthDefault;
	m_height = c_bgHeightDefault;
	m_children = CPVRTArray<UIElement*>();
	m_text = CPVRTArray<UITextSpec>();
	m_hidden = false;
}

UICompositeView::UICompositeView(char* bgTex, float x, float y, float width, float height)
{
	m_bg = UIImage(bgTex, x, y, width, height);
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_children = CPVRTArray<UIElement*>();
	m_text = CPVRTArray<UITextSpec>();
	m_hidden = false;
}

void
UICompositeView::AddImage(char* textureName, float xRel, float yRel, float width, float height)
{
	UIElement* newImage = new UIImage(textureName, m_x + xRel, m_y + yRel, width, height);
	m_children.Append(newImage);
}

void
UICompositeView::AddText(char* text, GLuint color, float xRel, float yRel, float scale, UITextType updateKey, UIFont font)
{
	UITextSpec newText = { text, color, xRel, yRel, scale, updateKey, font };
	m_text.Append(newText);
}

bool
UICompositeView::LoadTextures(CPVRTString* const pErrorStr)
{
	if (!m_bg.LoadTextures(pErrorStr)) {
		fprintf(stderr, "UICompositeView texture failed to load\n");
		return false;
	}
	for ( int i = 0; i < m_children.GetSize(); i ++ ) {
		if (m_children[i] == NULL) {
			continue;
		} else {
			if (!m_children[i]->LoadTextures(pErrorStr)) {
				fprintf(stderr, "UICompositeView texture failed to load\n");
				return false;
			}
		}
	}
	return true;
}

void
UICompositeView::BuildVertices()
{
	m_bg.BuildVertices();
	for ( int i = 0; i < m_children.GetSize(); i ++ ) {
		if (m_children[i] == NULL) {
			continue;
		} else {
			m_children[i]->BuildVertices();
		}
	}
}

bool
UICompositeView::Render(GLuint uiMVPMatrixLoc, UIPrinter* printer)
{
	if (m_hidden) {
		return true;
	}
    GLint viewport[4];
    GLint vWidth;                           // Viewport width
    GLint vHeight;                          // Viewport height
	glGetIntegerv(GL_VIEWPORT, viewport);

	vWidth = viewport[2];
	vHeight = viewport[3];

	m_bg.Render(uiMVPMatrixLoc, printer);

	if (m_children.GetSize() > 0) {
		for ( int i = 0; i < m_children.GetSize(); i ++ ) {
			if (m_children[i] == NULL) {
				continue;
			} else {
				if (!m_children[i]->Render(uiMVPMatrixLoc, printer)) {
					fprintf(stderr, "UICompositeView render failed\n");
				}
			}
		}
	}

	if (m_text.GetSize() > 0){
		float textWidth, textHeight;
		for ( int i = 0; i < m_text.GetSize(); i ++ ) {
			UITextSpec iText = m_text[i];
			printer->Print(m_x + iText.xRel, m_y + iText.yRel, iText.scale, iText.color, iText.font, iText.text);
		}
	}

	return true;
}

void
UICompositeView::Update(UIMessage updateMessage)
{
	if (m_text.GetSize() > 0) {
		for ( int i = 0; i < m_text.GetSize(); i ++ ){
			UITextType updateKey = m_text[i].updateKey;
			if (updateMessage.Read(updateKey) == NULL) {
				continue;
			} else {
				m_text[i].text = updateMessage.Read(updateKey);
			}
		}
	}
}

void
UICompositeView::Hide()
{
	m_hidden = true;
}

void
UICompositeView::Show()
{
	m_hidden = false;
}

void UICompositeView::Delete()
{
	if (m_children.GetSize() > 0) {
		for ( int i = 0; i < m_children.GetSize(); i++ ) {
			m_children[i]->Delete();
			delete m_children[i];
			m_children[i] = NULL;
		}
	}
}