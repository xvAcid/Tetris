//
//  GameViewController.m
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>

@implementation GameViewController

//------------------------------------------------------------------------------------------
//--
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context)
	{
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view					= (GLKView *)self.view;
    view.context					= self.context;
    view.drawableDepthFormat		= GLKViewDrawableDepthFormat24;
	self.preferredFramesPerSecond	= 30;
    
    [self setupGL];
}

//------------------------------------------------------------------------------------------
//--
- (void)dealloc
{    
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context)
	{
        [EAGLContext setCurrentContext:nil];
    }
}

//------------------------------------------------------------------------------------------
//--
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil))
	{
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context)
		{
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

//------------------------------------------------------------------------------------------
//--
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

//------------------------------------------------------------------------------------------
//--
- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
	
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	glPixelStorei(GL_PACK_ALIGNMENT,		1);
	glPixelStorei(GL_UNPACK_ALIGNMENT,		1);

	float ver			= [[[UIDevice currentDevice] systemVersion] floatValue];
	float scale			= (ver >= 3.2f) ? [[UIScreen mainScreen] scale] : 1.0f;
	CGRect screen_rect	= [[UIScreen mainScreen] bounds];
	timeout				= 5.0f;
	
	opengl_helper = OpenGLHelper::getSingleton();
	opengl_helper->setup(screen_rect.size.width * scale, screen_rect.size.height * scale);
	
	tile_manager = TileManager::getSingleton();
	tile_manager->create();
	
	figure_manager = FigureManager::getSingleton();
	figure_manager->create();
}

//------------------------------------------------------------------------------------------
//--
- (void)tearDownGL
{
	opengl_helper->deleteSingleton();
	opengl_helper = nullptr;
	
	tile_manager->deleteSingleton();
	tile_manager = nullptr;
	
	figure_manager->deleteSingleton();
	figure_manager = nullptr;
	
    [EAGLContext setCurrentContext:self.context];
}

//------------------------------------------------------------------------------------------
//--
- (void)update
{
	tile_manager->refresh();
	figure_manager->refresh();
	
	if (tile_manager->isGameEnd())
	{
		if (timeout < 0.0f)
		{
			timeout = 5.0f;
			tile_manager->restart();
			figure_manager->restart();
		}
		else
		{
			timeout -= 0.1f;
		}
	}
}

//------------------------------------------------------------------------------------------
//--
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, opengl_helper->getScreenWidth(), opengl_helper->getScreenHeight());

	figure_manager->draw();
	tile_manager->draw();	
}

//------------------------------------------------------------------------------------------
//--
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	for (UITouch *touch in touches)
	{
		CGPoint pos		= [touch locationInView:[self view]];
		float ver		= [[[UIDevice currentDevice] systemVersion] floatValue];
		float scale		= (ver >= 3.2f) ? [[UIScreen mainScreen] scale] : 1.0f;

		if (FigureManager::isAvailable())
		{
			FigureManager::getSingleton()->startTouch(vec2f(pos.x, pos.y) * scale);
			break;
		}
	}
}

//------------------------------------------------------------------------------------------
//--
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	for (UITouch *touch in touches)
	{
		CGPoint pos		= [touch locationInView:[self view]];
		float ver		= [[[UIDevice currentDevice] systemVersion] floatValue];
		float scale		= (ver >= 3.2f) ? [[UIScreen mainScreen] scale] : 1.0f;
		
		if (FigureManager::isAvailable())
		{
			FigureManager::getSingleton()->moveTouch(vec2f(pos.x, pos.y) * scale);
			break;
		}
	}
}

//------------------------------------------------------------------------------------------
//--
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	for (UITouch *touch in touches)
	{
		CGPoint pos		= [touch locationInView:[self view]];
		float ver		= [[[UIDevice currentDevice] systemVersion] floatValue];
		float scale		= (ver >= 3.2f) ? [[UIScreen mainScreen] scale] : 1.0f;
		
		if (FigureManager::isAvailable())
		{
			FigureManager::getSingleton()->endTouch(vec2f(pos.x, pos.y) * scale);
			break;
		}
	}
}

@end
