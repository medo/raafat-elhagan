//
//  main.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//


#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include "Wall.h"
#include "Point.h"

using namespace std;

void display() {
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, 640/480.0, 0.1, 115);
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, -10, 0, 0, 1000, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    Point p(0, 1, 0);
    Wall w(4, 4, 4, p);
    w.draw();
    
    glPopMatrix();
    glFlush();

}

int main(int argc, char ** argv) {
    
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set
    //display mode
    glutInitWindowSize(640, 480); // set window size
    glutInitWindowPosition(200, 150); // set window position on
    //screen
    glutCreateWindow("Raafat Elhagan"); // open the screen window
    glutDisplayFunc(display); // register redraw
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //set the light source properties
    GLfloat lightIntensity[] = { 0.3f, 0.9f, 1, 1.0f };
    GLfloat light_position[] = { 0, 0.3f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glEnable(GL_COLOR_MATERIAL);
    glutMainLoop(); // go into a perpetual loop
    
}



