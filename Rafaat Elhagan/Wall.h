//
//  Wall.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Point.h"
#include "Obstacle.h"
#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#ifndef Rafaat_Elhagan_Wall_h
#define Rafaat_Elhagan_Wall_h

class Wall : public Obstacle {
    
private:
    
    double length, width, height;
    Point position;
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char * data;
    GLuint loadBMP_custom(const char * imagepath);
    
public:
    
    Wall(double width, double length, double height, Point position);
    void set_height(double h);
    void set_width(double w);
    void set_length(double l);
    void set_position(Point p);
    double get_height();
    double get_width();
    double get_length();
    bool intersects(Point p);
    void draw();
    int get_type();

};



#endif
