//
//  TextureBuilder.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/12/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#ifndef Rafaat_Elhagan_TextureBuilder_h
#define Rafaat_Elhagan_TextureBuilder_h

#include <string>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif
typedef unsigned char BYTE;

GLuint LoadTexture( const char * filename, int width, int height, int wrap )
{
    GLuint texture;
    BYTE * data;
    FILE * file;
    
    // open texture data
    file = fopen("Earth.ppm", "rb" );
    if ( file == NULL ) {
        return 0;
    }
    
    // allocate buffer
    data = (BYTE*) malloc( width * height * 3 );
    
    // read texture data
    fread( data, 1, width * height * 3, file );
    fclose( file );
    
    // allocate a texture name
    glGenTextures( 1, &texture );
    
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );
    
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    wrap ? GL_REPEAT : GL_CLAMP );
    
    // build our texture MIP maps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width,
                      height, GL_RGB, GL_UNSIGNED_BYTE, data );
    
    // free buffer
    free( data );
    
    return texture;
    
}

#endif