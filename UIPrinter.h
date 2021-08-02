#include "OGLES2Tools.h"
// #include "Fonts/MontserratRegular.h"
// #include "Fonts/MontserratThin.h"
// #include "Fonts/MontserratLight.h"

#ifndef _UIPRINTER_H
#define _UIPRINTER_H

#include "Fonts/CustomMontserratBold.h"
#include "Fonts/MontserratMedium.h"

enum UIFont {
	UIFBold,
	UIFMedium
	// UIFRegular,
	// UIFThin,
	// UIFLight
};

class UIPrinter
{
	private:
	 	bool m_isRotated;
		CPVRTMap<UIFont, CPVRTPrint3D*> m_fontMap;
	public:
		UIPrinter();
		bool LoadFonts(int pvrShellWidth, int pvrShellHeight, bool isRotated);
		void Print(float x, float y, float scale, GLuint color, UIFont font, char* text);
		void Measure(float* width, float* height, float scale, UIFont font, char* text);
		void Delete();
};

#endif