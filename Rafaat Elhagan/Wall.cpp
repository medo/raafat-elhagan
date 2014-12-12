//
//  Wall.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Wall.h"
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

Wall::Wall(double width, double length, double height, Point position) {
    
    this -> position = position;
    this -> width = width;
    this -> length = length;
    this -> height = height;
}

void Wall::set_height(double h) {
    this -> height = h;
}

void Wall::set_width(double w) {
    this -> width = w;
}

void Wall::set_length(double l) {
    this -> length = l;
}

void Wall::set_position(Point p) {
    this -> position = p;
}

double Wall::get_height() {
    
    return height/2.0 + this->position.y;
}

double Wall::get_width() {
    
    return width;
}

double Wall::get_length() {

    return length;
}

bool Wall::intersects(Point p) {
    
    return p.x >= position.x - width/2 && p.x <= position.x + width/2 && p.y >= position.y - height/2 && p.y <= position.y + height/2 && p.z >= position.z - length/2 && p.z <= position.z + length/2;
    
}

void Wall::draw() {
    glPushMatrix();
    glScaled(width, height, length);
    glTranslated(position.x / width, position.y / height, position.z / length);
    glutSolidCube(1);
    glPopMatrix();
}

GLuint Wall::loadBMP_custom(const char *imagepath) {
    FILE * file = fopen(imagepath,"rb");
    if (!file)                              {printf("Image could not be opened\n"); return 0;}
    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }
    if ( header[0]!='B' || header[1]!='M' ){
        printf("Not a correct BMP file\n");
        return 0;
    }
    // Read ints from the byte array
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54;
    // Create a buffer
    data = new unsigned char [imageSize];
    
    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);
    
    //Everything is in memory now, the file can be closed
    fclose(file);
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return 0;

}

