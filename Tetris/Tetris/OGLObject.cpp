//
//  OGLObject.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "OGLObject.h"

//------------------------------------------------------------------------------------------
//--
OGLObject::OGLObject()
{
	OpenGLHelper::getSingleton()->createShader("Shader", this);
	OpenGLHelper::getSingleton()->createBuffer(this);
	SetColor(255, 255, 255);
}

//------------------------------------------------------------------------------------------
//--
OGLObject::~OGLObject()
{
	OpenGLHelper::getSingleton()->deleteBuffer(this);
	OpenGLHelper::getSingleton()->deleteShader(this);
}
