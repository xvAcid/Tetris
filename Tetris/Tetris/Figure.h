//
//  Figure.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef Figure_hpp
#define Figure_hpp

#include "OGLObject.h"
#include <vector>
#include <algorithm>

class Figure
{
public:
	enum FigureType
	{
		FT_I,
		FT_J,
		FT_L,
		FT_O,
		FT_S,
		FT_T,
		FT_Z,
		FT_COUNT
	};
	
	enum FigureState
	{
		FS_MOVE,
		FS_WAIT,
		FS_COUNT
	};
	
public:
	Figure(FigureType _type);
	virtual ~Figure();
	
	virtual void create() = 0;
	virtual void rotate(bool _ccw = true) = 0;
	
	virtual void draw();
	
	void setPosition(const vec2f &_position);
	const vec2f &getPosition() const;
	
	const vec2f &getSize() const;
	
	FigureState getState() const;
	void setState(FigureState _state);
	
	void setObjectId(unsigned int _object_id);
	unsigned int getObjectId() const;
	
	const vec2f &getBlockPosition(unsigned int _index) const;
	unsigned int getBlockCount() const;
	
	void eraseBlock(const vec2f &_tile_position);
	
protected:
	void calculateSize();
	
protected:
	vector<OGLObject*>	objects;
	vector<vec2f>		ogl_positions;
	
	FigureType			type			= FT_COUNT;
	FigureState			state			= FS_MOVE;
	vec2f				position		= vec2f_zero;
	vec2f				size			= vec2f_zero;
	
	unsigned int		object_id		= 0xFFFFFFFF;
	unsigned int		index_rotate	= 0;
};

inline void Figure::setPosition(const vec2f &_position)
{
	position = _position;
}

inline const vec2f &Figure::getPosition() const
{
	return position;
}

inline const vec2f &Figure::getSize() const
{
	return size;
}

inline void Figure::setState(FigureState _state)
{
	state = _state;
}

inline Figure::FigureState Figure::getState() const
{
	return state;
}

inline void Figure::setObjectId(unsigned int _object_id)
{
	object_id = _object_id;
}

inline unsigned int Figure::getObjectId() const
{
	return object_id;
}

inline const vec2f &Figure::getBlockPosition(unsigned int _index) const
{
	return (_index < ogl_positions.size()) ? ogl_positions[_index] : vec2f_zero;
}

inline unsigned int Figure::getBlockCount() const
{
	return ogl_positions.size();
}

inline void Figure::calculateSize()
{
	for (unsigned int i = 0; i < ogl_positions.size(); ++i)
	{
		const vec2f &position = ogl_positions[i];
		
		if (size.x < position.x) size.x = position.x;
		if (size.y < position.y) size.y = position.y;
	}
}

#endif /* Figure_hpp */
