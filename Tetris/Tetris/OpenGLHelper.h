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
#include "Singleton.h"

#include "Vec2f.h"
#include "Vec2i.h"

using namespace std;

class OGLObject;

class OpenGLHelper : public Singleton<OpenGLHelper>
{
	SINGLETON_DECLARATION(OpenGLHelper);
	
public:	
	struct VertexDesc
	{
		float Position[3];
		float Color[4];
	};
	
public:
	void setup(float _width, float _height);
	
	bool createShader(const string &_shader_name, OGLObject *_obj);
	void deleteShader(OGLObject *_obj);
	
	void createBuffer(OGLObject *_obj);
	void deleteBuffer(OGLObject *_obj);
	
	void drawBuffer(const OGLObject *_obj, const float _model_view[16]);
	
	void createModelView(const vec2f &_position, const vec2f &_scale, float *_result);
	
	float getScreenWidth() const;
	float getScreenHeight() const;
	
protected:
	bool compileShader(GLuint *_shader_id, const string &_shader_name, GLenum _type);
	bool linkProgram(GLuint _program_id);
	
	void createOrtho();
	
protected:
	float		projection[16];
	
	float		screen_width	= 0.0f;
	float		screen_height	= 0.0f;
	
};

inline void OpenGLHelper::setup(float _width, float _height)
{
	screen_width	= _width;
	screen_height	= _height;
	
	createOrtho();
}

inline float OpenGLHelper::getScreenWidth() const
{
	return screen_width;
}

inline float OpenGLHelper::getScreenHeight() const
{
	return screen_height;
}

#endif /* OpenGLHelper_hpp */
