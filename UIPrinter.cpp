#include "UIPrinter.h"

UIPrinter::UIPrinter()
{
	for ( int i = UIFBold; i <= UIFMedium; i ++ ) {
		UIFont iFont = static_cast<UIFont>(i);
		m_fontMap[iFont] = new CPVRTPrint3D();
	}
}

bool
UIPrinter::LoadFonts(int pvrShellWidth, int pvrShellHeight, bool isRotated)
{
	fprintf(stderr, "Loading fonts \n");
	m_isRotated = isRotated;
	for ( int i = UIFBold; i <= UIFMedium; i ++ ) {
		UIFont iFont = static_cast<UIFont>(i);
		CPVRTPrint3D* print3D = m_fontMap[iFont];
		switch(iFont) {
			case UIFBold:
				if (print3D->SetTextures(0, (void *) _CustomMontserratBold_pvr, pvrShellWidth, pvrShellHeight, isRotated) != PVR_SUCCESS) {
					fprintf(stderr, "Error loading print3D\n");
					return false;
				}
				break;
			case UIFMedium:
				if (print3D->SetTextures(0, (void *) _MontserratMedium_pvr, pvrShellWidth, pvrShellHeight, isRotated) != PVR_SUCCESS) {
					fprintf(stderr, "Error loading print3D\n");
					return false;
				}
			// 	break;
			// case UIFRegular:
			// 	if (print3D->SetTextures(0, (void *) _MontserratRegular_pvr, pvrShellWidth, pvrShellHeight, isRotated) != PVR_SUCCESS) {
			// 		fprintf(stderr, "Error loading print3D\n");
			// 		return false;
			// 	}
			// 	break;
			// case UIFThin:
			// 	if (print3D->SetTextures(0, (void *) _MontserratThin_pvr, pvrShellWidth, pvrShellHeight, isRotated) != PVR_SUCCESS) {
			// 		fprintf(stderr, "Error loading print3D\n");
			// 		return false;
			// 	}
			// 	break;
			// case UIFLight:
			// 	if (print3D->SetTextures(0, (void *) _MontserratLight_pvr, pvrShellWidth, pvrShellHeight, isRotated) != PVR_SUCCESS) {
			// 		fprintf(stderr, "Error loading print3D\n");
			// 		return false;
			// 	}
			// 	break;
		}
	}
	return true;
}

void
UIPrinter::Print(float x, float y, float scale, GLuint color, UIFont font, char* text)
{
	if (!m_fontMap.Exists(font)) {
		fprintf(stderr, "Invalid call to UIPrinter::Print\n");
		return;
	}
	// fprintf(stderr, "UIPrinter::Print called \n");
    GLint viewport[4];
    GLint vWidth;                           // Viewport width
    GLint vHeight;                          // Viewport height
	glGetIntegerv(GL_VIEWPORT, viewport);

	vWidth = viewport[2];
	vHeight = viewport[3];

	CPVRTPrint3D* print3D = m_fontMap[font];

	float textWidth;
	float textHeight;

	print3D->MeasureText(&textWidth, &textHeight, scale, text);

    if (print3D->Print3D((100*(x - (textWidth)/2)/vWidth)+50, -(100*(y + (textHeight)/2)/vHeight)+50, scale, color, text) != PVR_SUCCESS) {
		fprintf(stderr, "UIPrint failed \n");
	}
	print3D->Flush();
}

void
UIPrinter::Measure(float* width, float* height, float scale, UIFont font, char* text)
{
	if (!m_fontMap.Exists(font)) {
		fprintf(stderr, "Invalid call to UIPrinter::Measure\n");
		return;
	}

	CPVRTPrint3D* print3D = m_fontMap[font];
	print3D->MeasureText(width, height, scale, text);
} 