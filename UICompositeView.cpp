#include "UICompositeVIew.h"

UICompositeView::UICompositeView(float x, float y)
{
	m_bg = UIImage(c_bgTexDefault, x, y, c_bgWidthDefault, c_bgHeightDefault);
	m_x = x;
	m_y = y;
	m_width = c_bgWidthDefault;
	m_height = c_bgHeightDefault;
	m_children = CPVRTArray<UIElement*>();
	m_text = CPVRTArray<UIText>();
}

UICompositeView::UICompositeView(char* bgTex, float x, float y, float width, float height)
{
	m_bg = UIImage(bgTex, x, y, width, height);
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	m_children = CPVRTArray<UIElement*>();
	m_text = CPVRTArray<UIText>();
}

void
UICompositeView::AddImage(char* textureName, float xRel, float yRel, float width, float height)
{
	UIElement* newImage = new UIImage(textureName, m_x + xRel, m_y + yRel, width, height);
	m_children.Append(newImage);
}

void
UICompositeView::AddText(char* text, float xRel, float yRel, float scale)
{
	UIText newText = { text, xRel, yRel, scale };
	m_text.Append(newText);
}

