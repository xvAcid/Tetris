//
//  FigureT.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "FigureT.h"
#include "TileManager.h"

//------------------------------------------------------------------------------------------
//--
FigureT::FigureT() : Figure(Figure::FT_T)
{
	create();
}

//------------------------------------------------------------------------------------------
//--
void FigureT::create()
{
	const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();
	
	ogl_positions.push_back(vec2f(tile_size.y * 0, tile_size.y * 0));
	ogl_positions.push_back(vec2f(tile_size.y * 1, tile_size.y * 0));
	ogl_positions.push_back(vec2f(tile_size.y * 2, tile_size.y * 0));
	ogl_positions.push_back(vec2f(tile_size.y * 1, tile_size.y * 1));

	for (int i = 0; i < 4; ++i)
	{
		OGLObject *obj = new OGLObject();
		obj->SetColor(160, 0, 240);
		objects.push_back(obj);
	}
	
	calculateSize();
}

//------------------------------------------------------------------------------------------
//--
void FigureT::rotate(bool _ccw)
{
	vec2f pos_0[] ={ vec2f(0.0f, 0.0f), vec2f(1.0f, 0.0f), vec2f(2.0f, 1.0f), vec2f(0.0f, 2.0f) };
	vec2f pos_1[] ={ vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f), vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f) };
	vec2f pos_2[] ={ vec2f(2.0f, 0.0f), vec2f(1.0f, 2.0f), vec2f(0.0f, 1.0f), vec2f(0.0f, 0.0f) };
	vec2f pos_3[] ={ vec2f(1.0f, 1.0f), vec2f(0.0f, 1.0f), vec2f(1.0f, 0.0f), vec2f(1.0f, 1.0f) };
	
	const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();
	index_rotate			= _ccw ? (index_rotate + 1) % 4 : (index_rotate - 1) % 4;
	ogl_positions[0]		= pos_0[index_rotate] * tile_size;
	ogl_positions[1]		= pos_1[index_rotate] * tile_size;
	ogl_positions[2]		= pos_2[index_rotate] * tile_size;
	ogl_positions[3]		= pos_3[index_rotate] * tile_size;
}