//
//  OGLObject.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef OGLObject_hpp
#define OGLObject_hpp

#include "OpenGLHelper.h"

class OGLObject
{
	struct ShaderDesc
	{
		GLuint	program_id;
		GLuint	vertex_shader;
		GLuint	fragment_shader;
	};
	
	struct BufferDesc
	{
		GLuint	vertex_buffer;
		GLuint	index_buffer;
	};

public:
	OGLObject();
	~OGLObject();
	
	void SetColor(unsigned char _r, unsigned char _g, unsigned char _b);
	
protected:
	friend class OpenGLHelper;
	
	ShaderDesc	shader;
	BufferDesc	buffer;
	float		color[4];
};

inline void OGLObject::SetColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
	color[0] = static_cast<float>(_r) / 255;
	color[1] = static_cast<float>(_g) / 255;
	color[2] = static_cast<float>(_b) / 255;
	color[3] = 1.0f;
}


#endif /* OGLObject_hpp */
