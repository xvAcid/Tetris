//
//  OpenGLHelper.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "OpenGLHelper.h"

//------------------------------------------------------------------------------------------
//--
OpenGLHelper::OpenGLHelper()
{
}

//------------------------------------------------------------------------------------------
//--
OpenGLHelper::~OpenGLHelper()
{
}

//------------------------------------------------------------------------------------------
//--
bool OpenGLHelper::loadShader(const string &_shader_name, OpenGLHelper::ShaderDesc *_shader)
{
    _shader->program_id = glCreateProgram();
	
	if (!compileShader(&_shader->vertex_shader, _shader_name, GL_VERTEX_SHADER))
	{
		glDeleteProgram(_shader->program_id);
		NSLog(@"Failed to compile vertex shader");
		return false;
	}

	if (!compileShader(&_shader->fragment_shader, _shader_name, GL_FRAGMENT_SHADER))
	{
		if (_shader->vertex_shader)
		{
			glDeleteShader(_shader->vertex_shader);
			_shader->vertex_shader = 0;
		}
		
		if (_shader->program_id)
		{
			glDeleteProgram(_shader->program_id);
			_shader->program_id = 0;
		}
		
        NSLog(@"Failed to compile fragment shader");
		return false;
	}

    glAttachShader(_shader->program_id, _shader->vertex_shader);
    glAttachShader(_shader->program_id, _shader->fragment_shader);

    if (!linkProgram(_shader->program_id))
	{
        NSLog(@"Failed to link program: %d", _shader->program_id);

        if (_shader->vertex_shader)
		{
            glDeleteShader(_shader->vertex_shader);
            _shader->vertex_shader = 0;
        }
		
        if (_shader->fragment_shader)
		{
            glDeleteShader(_shader->fragment_shader);
            _shader->fragment_shader = 0;
        }
		
        if (_shader->program_id)
		{
            glDeleteProgram(_shader->program_id);
            _shader->program_id = 0;
        }

        return false;
    }
	
//    if (_shader->vertex_shader)
//	{
//        glDetachShader(_shader->program_id, _shader->vertex_shader);
//        glDeleteShader(_shader->vertex_shader);
//    }
//	
//    if (_shader->fragment_shader)
//	{
//        glDetachShader(_shader->program_id, _shader->fragment_shader);
//        glDeleteShader(_shader->fragment_shader);
//    }

    return true;
}

//------------------------------------------------------------------------------------------
//--
bool OpenGLHelper::compileShader(GLuint *_shader_id, const string &_shader_name, GLenum _type)
{
    GLint status;
    const GLchar *source;

	NSString *file_name		= [NSString stringWithUTF8String:_shader_name.c_str()];
	NSString *shader_path	= _type == GL_VERTEX_SHADER ?
	[[NSBundle mainBundle] pathForResource:file_name ofType:@"vsh"] :
	[[NSBundle mainBundle] pathForResource:file_name ofType:@"fsh"];
	
    source = (GLchar*)[[NSString stringWithContentsOfFile:shader_path encoding:NSUTF8StringEncoding error:nil] UTF8String];
	
    if (!source)
	{
        NSLog(@"Failed to load vertex shader");
        return false;
    }

    *_shader_id = glCreateShader(_type);
    glShaderSource(*_shader_id, 1, &source, NULL);
    glCompileShader(*_shader_id);

#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*_shader_id, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
	{
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*_shader_id, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif

    glGetShaderiv(*_shader_id, GL_COMPILE_STATUS, &status);
    if (status == 0)
	{
        glDeleteShader(*_shader_id);
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------------------
//--
bool OpenGLHelper::linkProgram(GLuint _program_id)
{
    GLint status;
    glLinkProgram(_program_id);

#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &logLength);
	
    if (logLength > 0)
	{
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(_program_id, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif

    glGetProgramiv(_program_id, GL_LINK_STATUS, &status);
	return status == 0 ? false : true;
}

//------------------------------------------------------------------------------------------
//--
void OpenGLHelper::createBuffer(OpenGLHelper::BufferDesc *_buffer, float _size)
{
	VertexDesc vertices[] =
	{
		{{-1.0f * _size, -1.0f * _size, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{ 1.0f * _size, -1.0f * _size, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{ 1.0f * _size,  1.0f * _size, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{-1.0f * _size,  1.0f * _size, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	};
	
	static GLubyte indices[] = {0, 1, 2, 3};
	
	glGenBuffers(1, &_buffer->vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer->vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &_buffer->index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer->index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}