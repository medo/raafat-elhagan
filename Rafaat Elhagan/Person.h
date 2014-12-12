//
//  Person.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/11/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#ifndef __Rafaat_Elhagan__Person__
#define __Rafaat_Elhagan__Person__

#include <stdio.h>
#include "Obstacle.h"
#include "Map.h"

class Person : public Obstacle {
    
private:
    
    double horizontal_angle, vertical_angle, look_depth, motion_speed, height, width, length, velocity;
    Point pos;
    int score=0,health=100;
    Map *map;
    
public:
    
    Person();
    Person(Point pos, double look_depth, double motion_speed, double height, Map *map);
    double set_horizontal_angle(double angle);
    double set_vertical_angle(double angle);
    double add_to_position_y(double y);
    double get_position_y();
    double get_height();
    Point get_look_at();
    Point get_position();
    Point set_position(Point pos);
    double get_horizontal_angle();
    double get_vertical_angle();
    bool intersect(double x, double y);
    bool move_forward();
    bool move_back();
    bool move_right();
    bool move_left();
    bool move_down();
    bool move_up();
    bool intersects(Point p);
    void draw();
    int get_score();
    int get_health();
    bool is_dead();
    void hit(int val);
    
};


#endif /* defined(__Rafaat_Elhagan__Person__) */
