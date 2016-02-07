//
//  FigureZ.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "FigureZ.h"
#include "TileManager.h"

//------------------------------------------------------------------------------------------
//--
FigureZ::FigureZ() : Figure(Figure::FT_Z)
{
	create();
}

//------------------------------------------------------------------------------------------
//--
void FigureZ::create()
{
	const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();
	
	ogl_positions.push_back(vec2f(tile_size.y * 0, tile_size.y * 1));
	ogl_positions.push_back(vec2f(tile_size.y * 1, tile_size.y * 1));
	ogl_positions.push_back(vec2f(tile_size.y * 1, tile_size.y * 0));
	ogl_positions.push_back(vec2f(tile_size.y * 2, tile_size.y * 0));

	for (int i = 0; i < 4; ++i)
	{
		OGLObject *obj = new OGLObject();
		obj->SetColor(240, 0, 0);
		objects.push_back(obj);
	}
}