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
	
public:
	void create();
	
	void refresh();
	void draw();
	
protected:
	typedef vector<unique_ptr<Figure> >	FigureContainer;
	FigureContainer						figures;
	
	float								level_speed	= 0.05f;
};

#endif /* FigureManager_hpp */
