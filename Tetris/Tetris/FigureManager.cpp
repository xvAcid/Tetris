//
//  FigureManager.cpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#include "FigureManager.h"
#include "TileManager.h"
#include "FigureI.h"
#include "FigureZ.h"
#include "FigureT.h"
#include "FigureS.h"
#include "FigureO.h"
#include "FigureL.h"
#include "FigureJ.h"

//------------------------------------------------------------------------------------------
//--
FigureManager::FigureManager()
{
}

//------------------------------------------------------------------------------------------
//--
FigureManager::~FigureManager()
{
	figures.clear();
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::create()
{
	figures.reserve(512);
	
	unique_ptr<FigureJ> figure	= std::make_unique<FigureJ>();
	
	const vec2f &tile_size		= TileManager::getSingleton()->getTileSize();
	const vec2i &board_size		= TileManager::getSingleton()->getBoardSize();
	
	float start_position_x		= (board_size.x * tile_size.x) * 0.5f;
	float start_position_y		= (board_size.y + 1) * tile_size.y;

	figure.get()->setPosition(vec2f(start_position_x, start_position_y));
	
	figures.push_back(std::move(figure));
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::refresh()
{
	const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();

	for (unsigned int i = 0; i < figures.size(); ++i)
	{
		Figure *figure = figures[i].get();
		
		if (figure->getState() == Figure::FS_MOVE)
		{
			figure->setPosition(figure->getPosition() - vec2f(0.0f, tile_size.y * level_speed));
		
			TileManager::getSingleton()->detectIntersect(figure);
		}
	}
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::draw()
{
	for (unsigned int i = 0; i < figures.size(); ++i)
	{
		figures[i].get()->draw();
	}
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