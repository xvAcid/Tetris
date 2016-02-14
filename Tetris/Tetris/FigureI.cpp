//
//  FigureI.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "FigureI.h"
#include "TileManager.h"

//------------------------------------------------------------------------------------------
//--
FigureI::FigureI() : Figure(Figure::FT_I)
{
	create();
}

//------------------------------------------------------------------------------------------
//--
void FigureI::create()
{
	const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();
	
	for (unsigned int i = 0; i < 4; ++i)
	{
		OGLObject *obj = new OGLObject();
		obj->SetColor(0, 240, 240);
		
		ogl_positions.push_back(vec2f(0.0f, tile_size.y * i));
		objects.push_back(obj);
	}
	
	calculateSize();
}

//------------------------------------------------------------------------------------------
//--
void FigureI::rotate(bool _ccw)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		vec2f &position = ogl_positions[i];
		position		= vec2f(position.y, position.x);
	}
	
	calculateSize();
}