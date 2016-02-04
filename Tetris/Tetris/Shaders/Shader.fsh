//
//  Shader.fsh
//  Tetris
//
//  Created by Vitaliy Ishutin on 04.02.16.
//  Copyright © 2016 Vitaliy Ishutin. All rights reserved.
//

varying lowp vec4 DestinationColor;

void main()
{
    gl_FragColor = DestinationColor;
}
