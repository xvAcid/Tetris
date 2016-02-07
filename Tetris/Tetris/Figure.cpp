//
//  Figure.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "Figure.h"
#include "TileManager.h"

//------------------------------------------------------------------------------------------
//--
Figure::Figure(FigureType _type) : type(_type)
{
	objects.reserve(4);
}

//------------------------------------------------------------------------------------------
//--
Figure::~Figure()
{
	for (int i = 0; i < objects.size(); ++i)
	{
		delete objects[i];
	}
	
	objects.clear();
}

//------------------------------------------------------------------------------------------
//--
void Figure::draw()
{
	OpenGLHelper *ogl = OpenGLHelper::getSingleton();
	
	for (int i = 0; i < objects.size(); ++i)
	{
		const OGLObject *obj		= objects[i];
		const vec2f &ogl_position	= position + ogl_positions[i];
		
		float mview[16] = {0};
		ogl->createModelView(ogl_position, TileManager::getSingleton()->getTileSize(), &mview[0]);
		ogl->drawBuffer(obj, &mview[0]);
	}
}
