//
//  FigureL.h
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef FigureL_hpp
#define FigureL_hpp

#include "Figure.h"

class FigureL : public Figure
{
public:
	FigureL();
	
	virtual void create();
	virtual void rotate(bool _ccw = true);
};

#endif /* FigureL_hpp */
