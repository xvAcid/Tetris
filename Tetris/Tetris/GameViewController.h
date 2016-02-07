//
//  GameViewController.h
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include "TileManager.h"
#include "FigureManager.h"
#include "OpenGLHelper.h"

@interface GameViewController : GLKViewController
{
	OpenGLHelper	*opengl_helper;
	TileManager		*tile_manager;
	FigureManager	*figure_manager;
};

@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end
