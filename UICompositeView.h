#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"
#include "Print2D.h"

#ifndef _UICOMPVIEW_H
#define _UICOMPVIEW_H

const char c_bgTexDefault[] = "basicBox.pvr";
const float c_bgWidthDefault = 220;
const float c_bgHeightDefault = 70;

struct UITextSpec {
	char* text;
	GLuint color;
	float xRel, yRel, scale;
	UITextType updateKey;
};

class UICompositeView : public UIElement
{
	protected:
		bool m_hidden;
		UIImage m_bg;
		float m_x, m_y, m_width, m_height;
		CPVRTArray<UIElement*> m_children;
		CPVRTArray<UITextSpec> m_text;
	public:
		UICompositeView(float x, float y);
		UICompositeView(char* bgTex, float x, float y, float width, float height);
		void AddImage(char* textureName, float xRel, float yRel, float width, float height);
		void AddText(char* text, GLuint color, float xRel, float yRel, float scale, UITextType updateKey);
        virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer) { return true; };
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
};

#endif