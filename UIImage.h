/******************************************************************************

 @File          UIImage.h

 @Title         UIImage Header File 

 @Author        Siddharth Hathi

 @Description   Header file for UIImage.cpp

******************************************************************************/

#include "PVRShell.h"
#include "OGLES2Tools.h"
#include "../file.h"
#include "UIElement.h"

#include <stdio.h>
#include <stddef.h>

#ifndef _UIIMAGE_H
#define _UIIMAGE_H

// Index to bind the attributes to vertex shaders
#define VERTEX_ARRAY	0
#define NORMAL_ARRAY	1
#define COLOR_ARRAY		2
#define TEXCOORD_ARRAY	3

// From OGLES2Coverflow
const float g_FOV = 0.78539819f;

// Struct used to store Vertex info
struct SVertex
{
	PVRTVec3	p;
	PVRTVec3	n;
	PVRTVec4	c;
	PVRTVec2	t;
};

// Class Constant
const unsigned int NormalOffset = (unsigned int)sizeof(PVRTVec3);
const unsigned int ColorOffset = NormalOffset+(unsigned int)sizeof(PVRTVec3);
const unsigned int TexCoordOffset = ColorOffset+(unsigned int)sizeof(PVRTVec4);

/*!****************************************************************************
 Object class. A UIImage is a prototype C++ class used to load, build, render,
 and display a 2d image UI component using OpenGL ES 2.0 tools. The class, 
 implemented in UIImage.cpp, constructs and stores OpenGL images with modular, 
 user defined heights, widths, positions, and textures. The UIImage respresents an
 evolution on the original StaticImage class in that it supports pixel coordinate
 specifications and dynamic frame-by-frame scaling and movement.
******************************************************************************/
class UIImage : public UIElement
{
    protected:
		// Instance variables
		GLuint  m_uiImgTex;
        GLuint	m_uiVbo;
        GLuint	m_uiOpaqueIndexVbo;
        SVertex m_vertices[32];
        unsigned short m_indicesOpaque[6];
	    int m_iNumOpaque;
        PVRTMat4		m_mProjection, m_mView;

		const char* m_texName;
		float m_x, m_y, m_width, m_height;
        PVRTVec3 m_scale;

		bool m_hidden;

		// Local Function
        bool loadTextureFromFile(FILE* pvr, GLuint* texture, PVR_Texture_Header* header);

    public:
		UIImage();
        UIImage(const char* textureName, float x, float y, float width, float height);
		virtual bool LoadTextures(CPVRTString* const pErrorStr);
		virtual void BuildVertices();
		virtual PVRTMat4* GetProjection();
		virtual PVRTMat4* GetView();
		virtual PVRTVec2 GetPosition();
        virtual void Move(float x, float y);
		virtual void SetPosition(float x, float y);
        virtual void Scale(float scaleX, float scaleY, float scaleZ);
        virtual void Draw(GLuint uiMVPMatrixLoc);
		virtual void DrawMesh();
		virtual bool Render(GLuint uiMVPMatrixLoc);
		virtual bool Render(GLuint uiMVPMatrixLoc, CPVRTPrint3D* print3D, bool isRotated);
        virtual bool Render(GLuint uiMVPMatrixLoc, UIPrinter* printer) { return true; };
		virtual void CreateAndDisplay(GLuint uiMVPMatrixLoc);
		virtual void Update(UIMessage updateMessage);
		virtual void Hide();
		virtual void Show();
		virtual bool Text();
        
};

#endif _UIIMAGE_H
