//
//  FigureI.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 07.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef FigureI_hpp
#define FigureI_hpp

#include "Figure.h"

class FigureI : public Figure
{
public:
	FigureI();
	
	virtual void create();
};

#endif /* FigureI_hpp */
