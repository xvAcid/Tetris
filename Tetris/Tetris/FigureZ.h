//
//  FigureZ.h
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef FigureZ_hpp
#define FigureZ_hpp

#include "Figure.h"

class FigureZ : public Figure
{
public:
	FigureZ();
	
	virtual void create();
	virtual void rotate(bool _ccw = true);
};

#endif /* FigureZ_hpp */
