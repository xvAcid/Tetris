//
//  FigureO.h
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef FigureO_hpp
#define FigureO_hpp

#include "Figure.h"

class FigureO : public Figure
{
public:
	FigureO();
	
	virtual void create();
	virtual void rotate(bool _ccw = true);
};

#endif /* FigureO_hpp */
