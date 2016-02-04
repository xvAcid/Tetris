//
//  Shader.vsh
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//


attribute vec4	Position;
attribute vec4	SourceColor;
varying vec4	DestinationColor;

uniform mat4	Projection;
uniform mat4	ModelView;

void main(void)
{
	DestinationColor	= SourceColor;
	gl_Position			= Projection * ModelView * Position;
}