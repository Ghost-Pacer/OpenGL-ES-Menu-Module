#include "OGLES2Tools.h"
#include "UIElement.h"
#include "UIImage.h"

#ifndef _UIBADGES_H
#define _UIBADGES_H

struct UIBadge {
	char* imageName;
	float width, height;
	UIBool identifier;
};

const int c_numBadges = 3;

const UIBadge c_Badges[] = {
	{ "century.pvr", 100, 100, UIBadge1 },
	{ "20weeks.pvr", 100, 100, UIBadge2 },
	{ "badge3.pvr", 80, 80, UIBadge3 }
};

const float c_badgeDim = 40;

class UIBadges : public UIElement
{
	protected:
		float m_x, m_y;
		CPVRTMap<UIBool, UIImage*> m_badges;
		CPVRTArray<UIImage*> m_activeBadges;
		bool m_hidden;
	public:
		UIBadges(float x, float y);
		bool AddBadge(UIBool identifier);
		void Test();
		virtual bool LoadTextures(CPVRTString* const pErrorStr);
        virtual void BuildVertices();
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		virtual void Delete();
};

#endif