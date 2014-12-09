//
//  Map.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include <vector>
#include "Obstacle.h"
using namespace std;
#ifndef Rafaat_Elhagan_Map_h
#define Rafaat_Elhagan_Map_h

class Map {
    
private:
    
    int length, width;
    vector<Obstacle> obstacles;
    
public:
    
    int get_length();
    int get_width();
    vector<Obstacle> get_obstacles();
    void add_obstacle(vector<Obstacle> obstacle);
    Map(int length, int width);
    
};

#endif
