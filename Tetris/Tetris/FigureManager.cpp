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
		float start_position_y		= board_size.y * tile_size.y;
		
		figure.get()->setObjectId(static_cast<int>(figures.size()));
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
		time_drop		= game_speed;
		Figure *figure	= getMovingFigure();
		
		if (figure)
		{
			//----------------------------------------------------------------
			//-- детектим по У
			const vec2f &tile_size = TileManager::getSingleton()->getTileSize();
			figure->setPosition(figure->getPosition() - vec2f(0.0f, tile_size.y));
			
			if (TileManager::getSingleton()->detectCollision(figure))
			{
				figure->setPosition(figure->getPosition() + vec2f(0.0f, tile_size.y));
				figure->setState(Figure::FS_WAIT);
				control_state = CS_COUNT;
				
				TileManager::getSingleton()->fillTiles(figure);
			}
		}
		
		//----------------------------------------------------------------
		//-- ищем что нет фигур которые движутся
		unsigned int move_objects = static_cast<unsigned int>(std::count_if(
																			figures.begin(),
																			figures.end(),
																			[](unique_ptr<Figure> const &_figure)
		{
			return _figure.get()->getState() == Figure::FS_MOVE;
		}));
		
		if (move_objects == 0)
		{
			++object_counts;
			generateFigure();
			
			//----------------------------------------------------------------
			//-- увеличиваем скорость, после определенного кол-ва фигур
			if (object_counts >= 10)
			{
				object_counts	= 0;
				game_speed		-= 0.1f;
				game_speed		= game_speed < 0.1f ? 0.1f : game_speed;
			}
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
		constexpr float timeout = 1.0f / 10.0f;
		
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
					
					const vec2f &tile_size	= TileManager::getSingleton()->getTileSize();
					float value				= direction.x > 0.1f ? -1.0f : direction.x < 0.1f ? 1.0f : 0.0f;
					
					figure->setPosition(figure->getPosition() - vec2f(value * tile_size.x, 0.0f));
					
					if (TileManager::getSingleton()->detectCollision(figure))
					{
						figure->setPosition(figure->getPosition() + vec2f(value * tile_size.x, 0.0f));
					}
				}
			}
			else if (control_state != CS_DROP_DOWN && slide_down > 8.0f)
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
			time_slide += 0.1f;
		}
	}
	else if (control_state != CS_DROP_DOWN)
	{
		if (control_state == CS_ROTATE)
		{
			Figure *figure = getMovingFigure();
			
			if (figure)
			{
				figure->rotate();

				if (TileManager::getSingleton()->detectCollision(figure))
				{
					figure->rotate(false);
				}
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
void FigureManager::eraseFigureBlock(unsigned int _block_id, unsigned int _object_id)
{
	Figure *figure = getFigure(_object_id);
	
	if (figure && figure->getState() == Figure::FS_WAIT)
	{
		figure->eraseBlock(_block_id);
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
void FigureManager::rebuildAllFigures()
{
	for_each(figures.begin(), figures.end(), [=](unique_ptr<Figure> const &_figure)
	{
		if (_figure.get()->getState() == Figure::FS_WAIT)
		{
			TileManager::getSingleton()->fillTiles(_figure.get());
		}
	});
}

//------------------------------------------------------------------------------------------
//--
Figure *FigureManager::findFigure(const vec2f &_position, unsigned int *_block_id) const
{
	Figure *result					= nullptr;
	const vec2f &tile_size			= TileManager::getSingleton()->getTileSize();
	const vec2f &half_tile_size		= tile_size * 0.5f;
	const vec2f &tile_center_pos	= _position + half_tile_size;
	
	for (unsigned int i = 0; i < figures.size() && !result; ++i)
	{
		Figure *figure = figures[i].get();
		
		for (unsigned int j = 0; j < figure->getBlockCount(); ++j)
		{
			const vec2f &block_center_position	= (figure->getPosition() + figure->getBlockPosition(j)) + half_tile_size;
			const vec2f &distance				= block_center_position - tile_center_pos;
			
			if (fabsf(distance.x) < half_tile_size.x && fabsf(distance.y) < half_tile_size.y)
			{
				(*_block_id)	= j;
				result			= figure;
			}
		}
	}
	
	return result;
}

//------------------------------------------------------------------------------------------
//--
void FigureManager::moveDownFigure(const vec2f &_position)
{
	unsigned int block_id	= 0xFFFFFFFF;
	Figure *figure			= FigureManager::getSingleton()->findFigure(_position, &block_id);
	
	if (figure && figure->getState() == Figure::FS_WAIT && block_id != 0xFFFFFFFF)
	{
		figure->moveDown(block_id, TileManager::getSingleton()->getTileSize().y);
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