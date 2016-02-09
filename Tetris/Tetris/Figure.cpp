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
		const OGLObject *obj = objects[i];
		if (obj)
		{
			float mview[16]				= {0};
			const vec2f &ogl_position	= position + ogl_positions[i];
			
			ogl->createModelView(ogl_position, TileManager::getSingleton()->getTileSize(), &mview[0]);
			ogl->drawBuffer(obj, &mview[0]);
		}
	}
}

//------------------------------------------------------------------------------------------
//--
void Figure::eraseBlock(const vec2f &_tile_position)
{
	const vec2f &half_tile_size		= TileManager::getSingleton()->getTileSize() * 0.5f;
	const vec2f &tile_center_pos	= _tile_position + half_tile_size;
	
	unsigned int index = 0;
	for (auto it = ogl_positions.begin(); it != ogl_positions.end(); ++index)
	{
		const vec2f &block_center_position	= (position + (*it)) + half_tile_size;
		const vec2f &distance				= block_center_position - tile_center_pos;
		
		if (fabsf(distance.x) < half_tile_size.x && fabsf(distance.y) < half_tile_size.y)
		{
			it = ogl_positions.erase(it);
			delete objects[index];
			objects[index] = nullptr;
		}
		else
		{
			++it;
		}
	}
	
	objects.erase(remove(objects.begin(), objects.end(), nullptr), objects.end());
}

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--

//------------------------------------------------------------------------------------------
//--