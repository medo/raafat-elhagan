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
        this->obstacles[i]->draw();
    }
    
}

void Map::init_map() {
    
    //room
    Point p1(0, 0, 40);
    Point p2(14.5, 0, 25);
    Point p3(-14.5, 0, 25);
    Wall *w1 = new Wall(30, 4, 1, p1);
    Wall *w2 = new Wall(1, 4, 30, p2);
    Wall *w3 = new Wall(1, 4, 30, p3);
    this->obstacles.push_back(w1);
    this->obstacles.push_back(w2);
    this->obstacles.push_back(w3);
    
}


