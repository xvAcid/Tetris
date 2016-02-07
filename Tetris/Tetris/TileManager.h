//
//  TileManager.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef TileManager_hpp
#define TileManager_hpp

#include "OpenGLHelper.h"
#include "OGLObject.h"
#include "Singleton.h"

#include <vector>

class Figure;
class TileManager : public Singleton<TileManager>
{
	SINGLETON_DECLARATION(TileManager);
	
	enum TileState
	{
		TS_WALL,
		TS_FREE,
		TS_BUSY,
		TS_COUNT,
	};
	
	struct Tile
	{
		OGLObject	*draw_object;
		vec2f		position	= vec2f_zero;
		vec2f		size		= vec2f_zero;
		TileState	state		= TS_COUNT;
	};
	
public:
	void create();
	
	void refresh();
	void draw();
	
	const vec2f &getTileSize() const;
	
	Figure *test;
	
protected:
	vector<Tile>	tile_objects;
	
	vec2f			tile_size	= vec2f(64);
	vec2i			board_size	= vec2i_zero;
};

inline const vec2f &TileManager::getTileSize() const
{
	return tile_size;
}

#endif /* TileManager_hpp */
