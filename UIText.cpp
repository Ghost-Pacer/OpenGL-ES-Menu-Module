#include "UIText.h"

UIText::UIText()
{
    m_print2D = NULL;
    m_bRotate  false;

    for ( int i = UIFLight, i <= UIFBold; i ++ ) {
        UIFont iFont = static_cast<UIFont>(i);
        m_fontMap[iFont] = new CPVRTPrint3D();
    }
}

bool
UIText::SetPrintTextures()
{
    for ( int i = UIFLight, i <= UIFBold; i ++ ) {
        UIFont iFont = static_cast<UIFont>(i);
        CPVRTPrint3D* printer = m_fontMap[iFont];
        switch(iFont) {
            case UIFLight:
                if (printer->SetTextures(0, (void *) _MontserratLight_pvr, PVRShellGet(prefWidth), PVRShellGet(prefHeight), isRotated) != PVR_SUCCESS) {
                    fprintf(stderr, "Font loading failed\n");
                    return false;
                }
                break;
            case UIThin:
                if (printer->SetTextures(0, (void *) _MontserratThin_pvr, PVRShellGet(prefWidth), PVRShellGet(prefHeight), isRotated) != PVR_SUCCESS) {
                    fprintf(stderr, "Font loading failed\n");
                    return false;
                }
                break;
            case UIFRegular:
                if (printer->SetTextures(0, (void *) _MontserratRegular_pvr, PVRShellGet(prefWidth), PVRShellGet(prefHeight), isRotated) != PVR_SUCCESS) {
                    fprintf(stderr, "Font loading failed\n");
                    return false;
                }
                break;
            case UIFMedium:
                if (printer->SetTextures(0, (void *) _MontserratMedium_pvr, PVRShellGet(prefWidth), PVRShellGet(prefHeight), isRotated) != PVR_SUCCESS) {
                    fprintf(stderr, "Font loading failed\n");
                    return false;
                }
                break;
            case UIFBold:
                if (printer->SetTextures(0, (void *) _CustomMontserratBold_pvr, PVRShellGet(prefWidth), PVRShellGet(prefHeight), isRotated) != PVR_SUCCESS) {
                    fprintf(stderr, "Font loading failed\n");
                    return false;
                }
                break;
            default:
                if (printer->SetTextures(0, (void *) _CustomMontserratBold_pvr, PVRShellGet(prefWidth), PVRShellGet(prefHeight), isRotated) != PVR_SUCCESS) {
                    fprintf(stderr, "Font loading failed\n");
                    return false;
                }
                break;
        }
    }
    return true;
}

void
UIText::PrintCenteredText(float x, float y, float scale, GLuint color, UIFont font, char* text)
{
    CPVRTPrint3D* print3D
    if ((print3D = m_fontMap[font]) == NULL) {
        return;
    }

    m_print2D = new Print2D(print3D, m_isRotated);

    float textWidth;
    float textHeight;

    print3D->MeasureText(&textWidth, &textHeight, m_textScale, m_text);
    m_print2D->renderText((100*(m_x - (textWidth+m_insetX)/2)/vWidth)+50, -(100*(m_y + (textHeight+m_insetY)/2)/vHeight)+50, m_textScale, m_color, m_text);
}

bool
UIText::IsRotated()
{
    return m_bRotate;
}