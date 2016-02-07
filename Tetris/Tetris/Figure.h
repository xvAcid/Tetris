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
	
	Figure(FigureType _type);
	virtual ~Figure();
	
	virtual void create() = 0;
	virtual void draw();
	
	void setPosition(const vec2f &_position);
	const vec2f &getPosition() const;
	
	FigureState getState() const;
	
protected:
	vector<OGLObject*>	objects;
	vector<vec2f>		ogl_positions;
	
	FigureType			type		= FT_COUNT;
	FigureState			state		= FS_MOVE;
	vec2f				position	= vec2f_zero;
};

inline void Figure::setPosition(const vec2f &_position)
{
	position = _position;
}

inline const vec2f &Figure::getPosition() const
{
	return position;
}

inline Figure::FigureState Figure::getState() const
{
	return state;
}

#endif /* Figure_hpp */
