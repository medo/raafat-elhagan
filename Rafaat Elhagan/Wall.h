//
//  Wall.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Point.h"
#include "Obstacle.h"

#ifndef Rafaat_Elhagan_Wall_h
#define Rafaat_Elhagan_Wall_h

class Wall : public Obstacle {
    
private:
    
    double length, width, height;
    Point position;
    
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

};



#endif
