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

#include <time.h>
#include <random>

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
	
	generateFigure();
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::generateFigure()
{
	unique_ptr<Figure> figure = std::move(createFigure());
	
	if (figure.get())
	{
		const vec2f &tile_size		= TileManager::getSingleton()->getTileSize();
		const vec2i &board_size		= TileManager::getSingleton()->getBoardSize();
		const vec2f &figure_size	= figure.get()->getSize();
		
		float start_position_x		= (board_size.x * tile_size.x) * 0.5f - figure_size.x * 0.5f;
		float start_position_y		= (board_size.y + 1) * tile_size.y;
		
		figure.get()->setObjectId(figures.size());
		figure.get()->setPosition(vec2f(start_position_x, start_position_y));
		
		figures.push_back(std::move(figure));
	}
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::refresh()
{
	updateControl();
	
	if (time_drop < 0.0f || control_state == CS_DROP_DOWN)
	{
		time_drop		= 1.0f;
		Figure *figure	= getMovingFigure();
		
		if (figure)
		{
			const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();
			
			TileManager::getSingleton()->clearTiles(figure);
		
			//----------------------------------------------------------------
			//-- детектим по У
			figure->setPosition(figure->getPosition() - vec2f(0.0f, tile_size.y));
			
			if (TileManager::getSingleton()->detectCollision(figure))
			{
				figure->setPosition(figure->getPosition() + vec2f(0.0f, tile_size.y));
				figure->setState(Figure::FS_WAIT);
				control_state = CS_COUNT;
			}
			
			TileManager::getSingleton()->fillTiles(figure);
		}
		
		//----------------------------------------------------------------
		//-- ищем что нет фигур которые движутся
		unsigned int move_objects = 0;
		
		for (int i = 0; i < figures.size(); ++i)
		{
			Figure *figure = figures[i].get();
			
			if (figure->getState() == Figure::FS_MOVE)
				++move_objects;
		}
		
		if (move_objects == 0)
		{
			generateFigure();
		}
		
	}
	else
	{
		time_drop -= 0.05f;
	}
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::draw()
{
	for_each(figures.begin(), figures.end(), [](unique_ptr<Figure> const &_figure)
	{
		_figure.get()->draw();
	});
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::updateControl()
{
	if (is_touch)
	{
		constexpr float timeout = 1.0f / 30.0f;
		
		if (time_slide > timeout)
		{
			time_slide			= 0.0f;
			float slide_down	= end_touch.y - start_touch.y;
			direction			= end_touch - start_touch;
			direction.y			= 0.0f;
			float length		= direction.length();
			start_touch			= end_touch;
			
			if (control_state != CS_DROP_DOWN && length > 5.0f)
			{
				control_state	= CS_MOVE;
				Figure *figure	= getMovingFigure();
				
				if (figure)
				{
					direction.normalize();
					
					const vec2f &tile_size = TileManager::getSingleton()->getTileSize();
					
					TileManager::getSingleton()->clearTiles(figure);
					
					float value = direction.x > 0.1f ? -1.0f : direction.x < 0.1f ? 1.0f : 0.0f;
					figure->setPosition(figure->getPosition() - vec2f(value * tile_size.x, 0.0f));
					
					if (TileManager::getSingleton()->detectCollision(figure))
					{
						figure->setPosition(figure->getPosition() + vec2f(value * tile_size.x, 0.0f));
					}
					
					TileManager::getSingleton()->fillTiles(figure);
				}
			}
			else if (control_state != CS_DROP_DOWN && slide_down > 2.0f)
			{
				control_state = CS_DROP_DOWN;
			}
			else if (control_state != CS_MOVE && control_state != CS_DROP_DOWN)
			{
				control_state = CS_ROTATE;
			}
		}
		else
		{
			time_slide += 0.05f;
		}
	}
	else if (control_state != CS_DROP_DOWN)
	{
		if (control_state == CS_ROTATE)
		{
			Figure *figure = getMovingFigure();
			
			if (figure)
			{
				TileManager::getSingleton()->clearTiles(figure);
				
				figure->rotate();

				if (TileManager::getSingleton()->detectCollision(figure))
				{
					figure->rotate(false);
				}
				
				TileManager::getSingleton()->fillTiles(figure);
			}
		}
		
		control_state	= CS_COUNT;
		direction		= vec2f_zero;
	}
}

//------------------------------------------------------------------------------------------
//--
unique_ptr<Figure> FigureManager::createFigure()
{
	int seed = static_cast<int>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::mt19937 mt_rand(seed);
	std::uniform_int_distribution<int> dist{0, Figure::FT_COUNT - 1};
	int value = dist(mt_rand);
	
	unique_ptr<Figure> figure;
	
	value = 0;
	switch (value)
	{
		case Figure::FT_I:
			figure = std::make_unique<FigureI>();
			break;
			
		case Figure::FT_J:
			figure = std::make_unique<FigureJ>();
			break;
			
		case Figure::FT_L:
			figure = std::make_unique<FigureL>();
			break;
			
		case Figure::FT_O:
			figure = std::make_unique<FigureO>();
			break;
			
		case Figure::FT_S:
			figure = std::make_unique<FigureS>();
			break;
			
		case Figure::FT_T:
			figure = std::make_unique<FigureT>();
			break;
			
		case Figure::FT_Z:
			figure = std::make_unique<FigureZ>();
			break;
			
		default:
			break;
	}
	
	return figure;
}

//------------------------------------------------------------------------------------------
//--
Figure *FigureManager::getMovingFigure()
{
	auto it = find_if(figures.begin(), figures.end(), [](unique_ptr<Figure> const &_figure)
	{
		return _figure.get()->getState() == Figure::FS_MOVE;
	});
	
	return it != figures.end() ? (*it).get() : nullptr;
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::eraseFigureBlock(const vec2f &_position, unsigned int _object_id)
{
	Figure *figure = getFigure(_object_id);
	
	if (figure && figure->getState() == Figure::FS_WAIT)
	{
		TileManager::getSingleton()->clearTiles(figure);
		
		figure->eraseBlock(_position);

		TileManager::getSingleton()->fillTiles(figure);
		
		if (figure->getBlockCount() == 0)
		{
//			figures.erase(remove(figures.begin(), figures.end(), it), figures.end());
		}
	}
}

//------------------------------------------------------------------------------------------
//--
Figure *FigureManager::getFigure(unsigned int _object_id) const
{
	auto it = find_if(figures.begin(), figures.end(), [=](unique_ptr<Figure> const &_figure)
	{
		return _figure.get()->getObjectId() == _object_id;
	});
	
	return it != figures.end() ? (*it).get() : nullptr;
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::moveDownAllFigures()
{
	for_each(figures.begin(), figures.end(), [=](unique_ptr<Figure> const &_figure)
	{
		updateMoving(_figure.get());
	});
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::updateMoving(Figure *_figure)
{
	const vec2f &tile_size = TileManager::getSingleton()->getTileSize();
	
	TileManager::getSingleton()->clearTiles(_figure);
	
	//----------------------------------------------------------------
	//-- детектим по У
	_figure->setPosition(_figure->getPosition() - vec2f(0.0f, tile_size.y));
	
	if (TileManager::getSingleton()->detectCollision(_figure))
	{
		_figure->setPosition(_figure->getPosition() + vec2f(0.0f, tile_size.y));
	}
	
	TileManager::getSingleton()->fillTiles(_figure);
}

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--


//------------------------------------------------------------------------------------------
//--