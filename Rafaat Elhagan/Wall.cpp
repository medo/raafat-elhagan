//
//  Wall.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Wall.h"
#include <iostream>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "TextureLoader.h"

static GLuint image = LoadTexture("Earth.ppm", 100, 50, false);

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

int Wall::get_type(){
  return 0;
}

bool Wall::intersects(Point p) {
    
    return p.x >= position.x - width/2 && p.x <= position.x + width/2 && p.y >= position.y - height/2 && p.y <= position.y + height/2 && p.z >= position.z - length/2 && p.z <= position.z + length/2;
    
}

void Wall::draw() {
    
    
    
    
    
    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    float mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float no_shininess = 0.0f;
    float low_shininess = 5.0f;
    float high_shininess = 100.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    
    /* draw sphere in first row, first column
     * diffuse reflection only; no ambient or specular
     */
    
    glPushMatrix();
//    glColor3d(1, 0, 1);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
//    glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    
    
    
    glScaled(width, height, length);
    glTranslated(position.x / width, position.y / height, position.z / length);
    
    
    glRotated(45, 0, 0, 1);
    GLUquadricObj *obj = gluNewQuadric();
    
//    gluQuadricOrientation(obj, GLU_INSIDE);
    gluQuadricTexture(obj, true);
//    gluQuadricNormals(obj, GLU_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);
    glEnable(GL_CULL_FACE);
    
    
    gluCylinder(obj, 1, 1, 1, 4, 4);
    gluDisk(obj, 0, 1, 4, 10);
    glTranslated(0, 0, 1);
    gluDisk(obj, 0, 1, 4, 10);
    
    
    
    glPopMatrix();

    
    
    
    
//    glPushMatrix();
//
//    glTranslated(position.x / width, position.y / height, position.z / length);
//    GLUquadricObj *obj = gluNewQuadric();
//    gluCylinder(obj, 0, 1, 1, 2, 2);
//    //    glutSolidCube(1);
//    glPopMatrix();
}


