#include "OGLES2Tools.h"
#include "Print2D.h"
#include "Fonts/MontserratMedium.h"
#include "Fonts/MontserratRegular.h"
#include "Fonts/MontserratThin.h"
#include "Fonts/CustomMontserratBold.pvr"
#include "Fonts/MontserratLight.h"

#ifndef _UITEXT_H
#define _UITEXT_H

enum UIFont {
    UIFLight,
    UIFThin,
    UIFRegular,
    UIFMedium,
    UIFBold
};

class UIText
{
    protected:
        Print2D* m_print2D;
        CPVRTMap<UIFont, CPVRTPrint3D*> m_fontMap;
        bool m_bRotate;
    public:
        UIText();
        bool SetPrintTextures();
        void PrintCenteredText(float x, float y, float scale, GLuint color, UIFont font, char* text);

};

#endif