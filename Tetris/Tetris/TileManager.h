//
//  TileManager.hpp
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#ifndef TileManager_hpp
#define TileManager_hpp

#include <stdio.h>
#include "OpenGLHelper.h"


class TileManager
{
public:
	TileManager();
	~TileManager();
	
	void Create();
	
	void Refresh();
	void Draw();
	
	
protected:
	OpenGLHelper::ShaderDesc	shader;
	OpenGLHelper::BufferDesc	buffer;
	
};

#endif /* TileManager_hpp */
