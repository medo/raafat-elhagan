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
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
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
    
    return 0;
}

double Wall::get_width() {
    
    return 0;
}

double Wall::get_length() {

    return 0;
}

bool Wall::intersects(Point p) {
    
    return p.x >= position.x - width/2 && p.x <= position.x + width/2 && p.y >= position.y - length/2 && p.y <= position.y + length/2 && p.z >= position.z - height/2 && p.z <= position.z + height/2;
    
}

void Wall::draw() {
    glPushMatrix();
    glScaled(width, length, height);
    glTranslated(position.x / width, position.y / length, position.z / height);
    glutSolidCube(1);
    glPopMatrix();
}

