//
//  Map.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Map.h"
#include "Wall.h"
#include "Point.h"
#include <iostream>


Map::Map(int width, int length) {
    this->width = width;
    this->length = length;
    init_map();
}

void Map::draw() {
    
    for (int i = 0; i < this->obstacles.size(); i++) {
        this->obstacles[i].draw();
    }
    
}

void Map::init_map() {
    
    Point p(0, 0, 10);
    Wall w(4, 4, 4, p);
    this->obstacles.push_back(w);
    
}


