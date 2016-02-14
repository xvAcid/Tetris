//
//  TileManager.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "TileManager.h"
#include "FigureManager.h"

//------------------------------------------------------------------------------------------
//--
TileManager::TileManager()
{
}

//------------------------------------------------------------------------------------------
//--
TileManager::~TileManager()
{
	for (unsigned int i = 0; i < tile_objects.size(); ++i)
	{
		delete tile_objects[i].draw_object;
	}
	
	tile_objects.clear();
}

//------------------------------------------------------------------------------------------
//--
void TileManager::create()
{
	OpenGLHelper *ogl	= OpenGLHelper::getSingleton();
	board_size			= vec2i(ogl->getScreenWidth() / tile_size.x, ogl->getScreenHeight() / tile_size.y + 2);
	board_size.x		= board_size.x % 2 ? board_size.x - 1 : board_size.x;
	
	for (unsigned int y = 0; y < board_size.y; ++y)
	{
		for (unsigned int x = 0; x < board_size.x; ++x)
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
	for (unsigned int y = 1; y < board_size.y; ++y)
	{
		//------------------------------
		//-- проверям вся линия занята
		unsigned int busy_tiles = 0;
		for (unsigned int x = 1; x < board_size.x - 1; ++x)
		{
			unsigned int tile_index = (y * board_size.x) + x;
			const Tile &tile		= tile_objects[tile_index];
			
			if (tile.state == TS_BUSY)
			{
				Figure *figure = FigureManager::getSingleton()->getFigure(tile.object_id);

				if (figure && figure->getState() == Figure::FS_WAIT)
				{
					++busy_tiles;
				}
			}
		}
		
		//------------------------------
		//-- срезаем линию
		if (busy_tiles == board_size.x - 2)
		{
			scores += board_size.x;
			//------------------------------------------------
			//-- сначала проходимся по фигурам которые срезаем
			//-- и выставляем позиции для срезаных блоков
			for (unsigned int x = 1; x < board_size.x - 1; ++x)
			{
				unsigned int tile_index = (y * board_size.x) + x;
				const Tile &tile		= tile_objects[tile_index];

				if (tile.state == TS_BUSY && tile.block_index != 0xFFFFFFFF)
				{
					FigureManager::getSingleton()->eraseFigureBlock(tile.block_index, tile.object_id);
				}
			}
			
			//------------------------------------------------
			//-- теперь делаем тайлы пустыми и опускаем все
			//-- что выше Y на тайл ниже
			clearAllTiles();
				
			for (unsigned int x = 1; x < board_size.x - 1; ++x)
			{
				for (unsigned int new_y = y; new_y < board_size.y; ++new_y)
				{
					unsigned int tile_index = (new_y * board_size.x) + x;
					const Tile &tile		= tile_objects[tile_index];
					
					FigureManager::getSingleton()->moveDownFigure(tile.position);
				}
			}
			
			FigureManager::getSingleton()->rebuildAllFigures();
		}
	}
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

//------------------------------------------------------------------------------------------
//--
void TileManager::clearAllTiles()
{
	for (unsigned int i = 0; i < tile_objects.size(); ++i)
	{
		Tile &tile = tile_objects[i];
		if (tile.state != TS_WALL)
		{
			tile.object_id		= 0xFFFFFFFF;
			tile.block_index	= 0xFFFFFFFF;
			tile.state			= TileManager::TS_FREE;
		}
	}
}

//------------------------------------------------------------------------------------------
//--
void TileManager::fillTiles(Figure *_figure)
{
	for (unsigned int i = 0; i < tile_objects.size(); ++i)
	{
		Tile &tile = tile_objects[i];
		
		if (tile.state == TileManager::TS_FREE)
		{
			const vec2f &half_tile_size		= tile.size * 0.5f;
			const vec2f &tile_center_pos	= tile.position + half_tile_size;
			
			for (unsigned int j = 0; j < _figure->getBlockCount(); ++j)
			{
				const vec2f &block_center_position	= (_figure->getPosition() + _figure->getBlockPosition(j)) + half_tile_size;
				const vec2f &distance				= block_center_position - tile_center_pos;
				
				if (fabsf(distance.x) < half_tile_size.x && fabsf(distance.y) < half_tile_size.y)
				{
					tile.object_id		= _figure->getObjectId();
					tile.block_index	= j;
					tile.state			= TileManager::TS_BUSY;
				}
			}
		}
	}
}

//------------------------------------------------------------------------------------------
//--
bool TileManager::detectCollision(Figure *_figure)
{
	bool is_collision = false;
	for (unsigned int i = 0; i < tile_objects.size() && !is_collision; ++i)
	{
		Tile &tile = tile_objects[i];
		
		if (tile.state == TileManager::TS_WALL || tile.state == TileManager::TS_BUSY)
		{
			const vec2f &half_tile_size		= tile.size * 0.5f;
			const vec2f &tile_center_pos	= tile.position + half_tile_size;
			
			for (unsigned int j = 0; j < _figure->getBlockCount(); ++j)
			{
				const vec2f &block_center_position	= (_figure->getPosition() + _figure->getBlockPosition(j)) + half_tile_size;
				const vec2f &distance				= block_center_position - tile_center_pos;
				
				if (fabsf(distance.x) < half_tile_size.x && fabsf(distance.y) < half_tile_size.y)
				{
					is_collision = true;
				}
			}
		}
	}
	
	return is_collision;
}

//------------------------------------------------------------------------------------------
//--
bool TileManager::isGameEnd(void) const
{
	for (unsigned int x = 1; x < board_size.x - 1; ++x)
	{
		unsigned int index = ((board_size.y - 1) * board_size.x) + x;
		if (tile_objects[index].state == TS_BUSY)
		{
			return true;
		}
	}
	
	return false;
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