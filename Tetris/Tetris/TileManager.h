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
#include "Figure.h"

#include <vector>

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
		OGLObject		*draw_object;
		vec2f			position	= vec2f_zero;
		vec2f			size		= vec2f_zero;
		TileState		state		= TS_COUNT;
		unsigned int	object_id	= 0xFFFFFFFF;
		unsigned int	block_index	= 0xFFFFFFFF;
	};
	
public:
	void create();
	
	void refresh();
	void draw();
	
	void fillTiles(Figure *_figure);
	
	bool detectCollision(Figure *_figure);
	
	const vec2f &getTileSize() const;
	const vec2i &getBoardSize() const;
	
	void clearAllTiles();
	
	bool isGameEnd(void) const;
	
	void restart();
	
protected:
	vector<Tile>	tile_objects;
	
	vec2f			tile_size	= vec2f(64);
	vec2i			board_size	= vec2i_zero;
	unsigned int	scores		= 0;
};

inline const vec2f &TileManager::getTileSize() const
{
	return tile_size;
}

inline const vec2i &TileManager::getBoardSize() const
{
	return  board_size;
}

inline void TileManager::restart()
{
	scores = 0;

	clearAllTiles();
}

#endif /* TileManager_hpp */
