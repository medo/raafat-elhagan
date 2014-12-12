//
//  Obstacle.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Point.h"

#ifndef Rafaat_Elhagan_Obstacle_h
#define Rafaat_Elhagan_Obstacle_h

class Obstacle {
    
public:
    virtual bool intersects(Point p) { return false;};
    void set_position(Point p);
    virtual void draw() = 0;
    virtual double get_height() = 0;
    
};

#endif
