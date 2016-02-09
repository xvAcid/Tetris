//
//  FigureJ.h
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef FigureJ_hpp
#define FigureJ_hpp

#include "Figure.h"

class FigureJ : public Figure
{
public:
	FigureJ();
	
	virtual void create();
	virtual void rotate(bool _ccw = true);
};

#endif /* FigureJ_hpp */
