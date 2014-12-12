//
//  Map.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include <vector>
#include "Obstacle.h"
#include "Wall.h"
using namespace std;
#ifndef Rafaat_Elhagan_Map_h
#define Rafaat_Elhagan_Map_h

class Map {
    
private:
    
    int length, width;
    vector<Obstacle *> obstacles;
    
    void init_map();
    
public:
    
    int get_length();
    int get_width();
    void draw();
    bool intersects(Point p);
    double get_height(Point p);
    vector<Obstacle *> get_obstacles();
    void add_obstacle(Obstacle *obstacle);
    int shoot(Point pos, double h_angle, double v_angle);
    Map(int length, int width);
    
};

#endif
