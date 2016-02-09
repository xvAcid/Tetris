//
//  FigureManager.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef FigureManager_hpp
#define FigureManager_hpp

#include "Singleton.h"
#include "Figure.h"

#include <vector>
#include <algorithm>
#include <memory>

class FigureManager : public Singleton<FigureManager>
{
	SINGLETON_DECLARATION(FigureManager);
	
	enum ControlState
	{
		CS_MOVE,
		CS_ROTATE,
		CS_DROP_DOWN,
		CS_COUNT
	};
	
public:
	void create();
	
	void refresh();
	void draw();
	
	void startTouch(const vec2f &_position);
	void moveTouch(const vec2f &_position);
	void endTouch(const vec2f &_position);
	
	void moveDownAllFigures();
	void eraseFigureBlock(const vec2f &_position, unsigned int _object_id);
	Figure *getFigure(unsigned int _object_id) const;
	
protected:
	void generateFigure();
	unique_ptr<Figure> createFigure();
	Figure *getMovingFigure();
	
	void updateMoving(Figure *_figure);
	
	void updateControl();
	
protected:
	typedef vector<unique_ptr<Figure> >	FigureContainer;
	FigureContainer						figures;

	ControlState						control_state	= CS_COUNT;
	vec2f								start_touch		= vec2f_zero;
	vec2f								end_touch		= vec2f_zero;
	vec2f								direction		= vec2f_zero;
	
	float								level_speed		= 0.05f;
	float								time_drop		= 1.0f;
	float								time_slide		= 0.0f;
	
	bool								is_touch		= false;
};

//------------------------------------------------------------------------------------------
//--
inline void FigureManager::startTouch(const vec2f &_position)
{
	is_touch	= true;
	start_touch = _position;
	end_touch	= _position;
}

inline void FigureManager::moveTouch(const vec2f &_position)
{
	is_touch	= true;
	end_touch	= _position;
}

inline void FigureManager::endTouch(const vec2f &_position)
{
	is_touch	= false;
	start_touch = vec2f_zero;
	end_touch	= vec2f_zero;
}


#endif /* FigureManager_hpp */
