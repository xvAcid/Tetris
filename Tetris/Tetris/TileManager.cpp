//
//  TileManager.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "TileManager.h"

//------------------------------------------------------------------------------------------
//--
TileManager::TileManager()
{
}

//------------------------------------------------------------------------------------------
//--
TileManager::~TileManager()
{
}

//------------------------------------------------------------------------------------------
//--
void TileManager::Create()
{
	OpenGLHelper ogl;
	ogl.loadShader("Shader", &shader);
	ogl.createBuffer(&buffer, 50);
}

//------------------------------------------------------------------------------------------
//--
void TileManager::Refresh()
{
}

//------------------------------------------------------------------------------------------
//--
void TileManager::Draw()
{
	glUseProgram(shader.program_id);
	GLuint position_attr		= glGetAttribLocation(shader.program_id,	"Position");
	GLuint color_attr			= glGetAttribLocation(shader.program_id,	"SourceColor");
	GLuint proj_uniform			= glGetUniformLocation(shader.program_id,	"Projection");
	GLuint model_view_uniform	= glGetUniformLocation(shader.program_id,	"ModelView");

	
	float view[16]			=
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	
	float proj[16]			=
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	
	float far_plane			= 1000.0f;
	float near_plane		= 1.0f;
	float projection_bottom	= 0.0f;
	float projection_left	= 0.0f;
	float projection_top	= 568.0f;//static_cast<float>(rect.size.height);
	float projection_right	= 320.0f;//static_cast<float>(rect.size.width);
	
	proj[0]					= 2.0f / (projection_right - projection_left);
	proj[5]					= 2.0f / (projection_top - projection_bottom);
	proj[10]				= 2.0f / (far_plane - near_plane);
	proj[12]				= -(projection_right + projection_left) / (projection_right - projection_left);
	proj[13]				= -(projection_top + projection_bottom) / (projection_top - projection_bottom);
	proj[14]				= (far_plane + near_plane) / (far_plane - near_plane);
	proj[15]				= 1.0f;
	
	glUniformMatrix4fv(proj_uniform, 1, 0, proj);
	glUniformMatrix4fv(model_view_uniform, 1, 0, view);

	glEnableVertexAttribArray(position_attr);
	glEnableVertexAttribArray(color_attr);

	glBindBuffer(GL_ARRAY_BUFFER,			buffer.vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,	buffer.index_buffer);
	
	glVertexAttribPointer(position_attr, 3, GL_FLOAT, GL_FALSE, sizeof(OpenGLHelper::VertexDesc), 0);
	glVertexAttribPointer(color_attr, 4, GL_FLOAT, GL_FALSE, sizeof(OpenGLHelper::VertexDesc), (GLvoid*)(sizeof(float) * 3));

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
	
	glDisableVertexAttribArray(position_attr);
	glDisableVertexAttribArray(color_attr);
	
	glBindBuffer(GL_ARRAY_BUFFER,			0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,	0);

}
