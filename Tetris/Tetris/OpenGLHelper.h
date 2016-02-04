//
//  OpenGLHelper.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef OpenGLHelper_hpp
#define OpenGLHelper_hpp

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include <string>

using namespace std;

class OpenGLHelper
{
public:
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
	
	struct VertexDesc
	{
		float Position[3];
		float Color[4];
	};
	
public:
	OpenGLHelper();
	~OpenGLHelper();
	
	bool loadShader(const string &_shader_name, ShaderDesc *_shader);
	void createBuffer(BufferDesc *_buffer, float _size);
	
protected:
	bool compileShader(GLuint *_shader_id, const string &_shader_name, GLenum _type);
	bool linkProgram(GLuint _program_id);
	
};

#endif /* OpenGLHelper_hpp */
