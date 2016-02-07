//
//  TileManager.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "TileManager.h"
#include "Figure.h"
#include "FigureI.h"

//------------------------------------------------------------------------------------------
//--
TileManager::TileManager()
{
}

//------------------------------------------------------------------------------------------
//--
TileManager::~TileManager()
{
	for (int i = 0; i < tile_objects.size(); ++i)
	{
		delete tile_objects[i].draw_object;
	}
	
	tile_objects.clear();
	
	delete test;
}

//------------------------------------------------------------------------------------------
//--
void TileManager::create()
{
	OpenGLHelper *ogl	= OpenGLHelper::getSingleton();
	board_size			= vec2i(ogl->getScreenWidth() / tile_size.x, ogl->getScreenHeight() / tile_size.y);
	
	for (int x = 0; x < board_size.x; ++x)
	{
		for (int y = 0; y < board_size.y; ++y)
		{
			Tile tile;
			tile.state			= (x == 0 || x == board_size.x - 1 || y == 0) ? TS_WALL : TS_FREE;
			tile.position		= vec2f(x * tile_size.x, y * tile_size.y);
			tile.size			= tile_size;
			tile.draw_object	= tile.state == TS_WALL ? new OGLObject() : nullptr;

			tile_objects.push_back(tile);
		}
	}
}

//------------------------------------------------------------------------------------------
//--
void TileManager::refresh()
{
}

//------------------------------------------------------------------------------------------
//--
void TileManager::draw()
{
	OpenGLHelper *ogl = OpenGLHelper::getSingleton();
	
	for (auto tile : tile_objects)
	{
		if (tile.draw_object)
		{
			float mview[16] = {0};
			ogl->createModelView(tile.position, tile.size, &mview[0]);
			ogl->drawBuffer(tile.draw_object, &mview[0]);
		}
	}
}
