//
//  GameViewController.m
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

#import "GameViewController.h"
#import <OpenGLES/ES2/glext.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

enum
{
    ATTRIB_VERTEX,
    NUM_ATTRIBUTES
};

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

	
	tile_manager = new TileManager();
	tile_manager->Create();
}

//------------------------------------------------------------------------------------------
//--
- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

//------------------------------------------------------------------------------------------
//--
- (void)update
{
	tile_manager->Refresh();
}

//------------------------------------------------------------------------------------------
//--
- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	
	glViewport(0, 0, rect.size.width, rect.size.height);

	tile_manager->Draw();
	
}

@end
