//
//  OpenGLHelper.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include "OpenGLHelper.h"
#include "OGLObject.h"

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
bool OpenGLHelper::createShader(const string &_shader_name, OGLObject *_obj)
{
    _obj->shader.program_id = glCreateProgram();
	
	if (!compileShader(&_obj->shader.vertex_shader, _shader_name, GL_VERTEX_SHADER))
	{
		if (_obj->shader.program_id)
		{
			glDeleteProgram(_obj->shader.program_id);
			_obj->shader.program_id = 0;
		}
		
		NSLog(@"Failed to compile vertex shader");
		return false;
	}

	if (!compileShader(&_obj->shader.fragment_shader, _shader_name, GL_FRAGMENT_SHADER))
	{
		if (_obj->shader.program_id)
		{
			glDeleteProgram(_obj->shader.program_id);
			_obj->shader.program_id = 0;
		}
		
		if (_obj->shader.vertex_shader)
		{
			glDeleteShader(_obj->shader.vertex_shader);
			_obj->shader.vertex_shader = 0;
		}
		
		if (_obj->shader.program_id)
		{
			glDeleteProgram(_obj->shader.program_id);
			_obj->shader.program_id = 0;
		}
		
        NSLog(@"Failed to compile fragment shader");
		return false;
	}

    glAttachShader(_obj->shader.program_id, _obj->shader.vertex_shader);
    glAttachShader(_obj->shader.program_id, _obj->shader.fragment_shader);

    if (!linkProgram(_obj->shader.program_id))
	{
        NSLog(@"Failed to link program: %d", _obj->shader.program_id);

        if (_obj->shader.vertex_shader)
		{
            glDeleteShader(_obj->shader.vertex_shader);
            _obj->shader.vertex_shader = 0;
        }
		
        if (_obj->shader.fragment_shader)
		{
            glDeleteShader(_obj->shader.fragment_shader);
            _obj->shader.fragment_shader = 0;
        }
		
        if (_obj->shader.program_id)
		{
            glDeleteProgram(_obj->shader.program_id);
            _obj->shader.program_id = 0;
        }

        return false;
    }
	
    if (_obj->shader.vertex_shader)
	{
        glDetachShader(_obj->shader.program_id, _obj->shader.vertex_shader);
        glDeleteShader(_obj->shader.vertex_shader);
    }
	
    if (_obj->shader.fragment_shader)
	{
        glDetachShader(_obj->shader.program_id, _obj->shader.fragment_shader);
        glDeleteShader(_obj->shader.fragment_shader);
    }

    return true;
}

//------------------------------------------------------------------------------------------
//--
void OpenGLHelper::deleteShader(OGLObject *_obj)
{
	if (_obj->shader.program_id)
	{
		glDeleteProgram(_obj->shader.program_id);
		_obj->shader.program_id = 0;
	}
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
void OpenGLHelper::createBuffer(OGLObject *_obj)
{
	VertexDesc vertices[] =
	{
		{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
	};
	
	static GLubyte indices[] = {0, 1, 2, 3};
	
	glGenBuffers(1, &_obj->buffer.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, _obj->buffer.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &_obj->buffer.index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _obj->buffer.index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//------------------------------------------------------------------------------------------
//--
void OpenGLHelper::deleteBuffer(OGLObject *_obj)
{
	if (_obj->buffer.vertex_buffer)
	{
		glDeleteBuffers(1, &_obj->buffer.vertex_buffer);
		_obj->buffer.vertex_buffer = 0;
	}
	
	if (_obj->buffer.index_buffer)
	{
		glDeleteBuffers(1, &_obj->buffer.index_buffer);
		_obj->buffer.index_buffer = 0;
	}
}

//------------------------------------------------------------------------------------------
//--
void OpenGLHelper::drawBuffer(const OGLObject *_obj, const float _model_view[16])
{
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
	
	if (_obj)
	{
		glUseProgram(_obj->shader.program_id);
		
		GLuint position_attr	= glGetAttribLocation(_obj->shader.program_id,	"Position");
		GLuint color_attr		= glGetUniformLocation(_obj->shader.program_id,	"SourceColor");
		GLuint proj_uniform		= glGetUniformLocation(_obj->shader.program_id,	"Projection");
		GLuint model_view		= glGetUniformLocation(_obj->shader.program_id,	"ModelView");
		
		glUniform4f(color_attr, _obj->color[0], _obj->color[1], _obj->color[2], _obj->color[3]);
		
		glUniformMatrix4fv(proj_uniform, 1, 0, projection);
		glUniformMatrix4fv(model_view, 1, 0, _model_view);
		
		glEnableVertexAttribArray(position_attr);
		glEnableVertexAttribArray(color_attr);
		
		glBindBuffer(GL_ARRAY_BUFFER,			_obj->buffer.vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,	_obj->buffer.index_buffer);
		
		glVertexAttribPointer(position_attr, 3, GL_FLOAT, GL_FALSE, sizeof(OpenGLHelper::VertexDesc), 0);
		glVertexAttribPointer(color_attr, 4, GL_FLOAT, GL_FALSE, sizeof(OpenGLHelper::VertexDesc), BUFFER_OFFSET(sizeof(float) * 3));
		
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, 0);
		
		glDisableVertexAttribArray(position_attr);
		glDisableVertexAttribArray(color_attr);
		
		glBindBuffer(GL_ARRAY_BUFFER,			0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,	0);
	}
	
#undef BUFFER_OFFSET
}

//------------------------------------------------------------------------------------------
//--
void OpenGLHelper::createOrtho()
{
	float fan	= -2000.0f;
	float fsn	= 2000.0f;
	float m[16] =
	{
		2.0f / screen_width,
		0.0f,
		0.0f,
		0.0f,
		
		0.0f,
		2.0f / screen_height,
		0.0f,
		0.0f,
		
		0.0f,
		0.0f,
		-2.0f / fsn,
		0.0f,
		
		-screen_width / screen_width,
		-screen_height / screen_height,
		-fan / fsn,
		1.0f
	};

	memcpy(projection, m, sizeof(m));
}

//------------------------------------------------------------------------------------------
//--
void OpenGLHelper::createModelView(const vec2f &_position, const vec2f &_scale, float *_result)
{
	float m[16] =
	{
		_scale.x, 0.0f, 0.0f, 0.0f,
		0.0f, _scale.y, 0.0f, 0.0f,
		0.0f,     0.0f, 1.0f, 0.0f,
		_position.x, _position.y, 0.0f, 1.0f
	};
	
	memcpy(_result, m, sizeof(m));
}

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--
