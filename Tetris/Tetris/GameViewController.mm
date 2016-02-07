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
    
    GLKView *view				= (GLKView *)self.view;
    view.context				= self.context;
    view.drawableDepthFormat	= GLKViewDrawableDepthFormat24;
    
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
	
	opengl_helper = OpenGLHelper::getSingleton();
	opengl_helper->setup(screen_rect.size.width * scale, screen_rect.size.height * scale);
	
	tile_manager = TileManager::getSingleton();
	tile_manager->create();
}

//------------------------------------------------------------------------------------------
//--
- (void)tearDownGL
{
	opengl_helper->deleteSingleton();
	opengl_helper = nullptr;
	
	tile_manager->deleteSingleton();
	tile_manager = nullptr;
	
    [EAGLContext setCurrentContext:self.context];
}

//------------------------------------------------------------------------------------------
//--
- (void)update
{
	tile_manager->refresh();
}

//------------------------------------------------------------------------------------------
//--
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, opengl_helper->getScreenWidth(), opengl_helper->getScreenHeight());

	tile_manager->draw();
}

@end
