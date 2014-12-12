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

bool Map::intersects(Point p) {
    
    for (int i = 0; i < this->obstacles.size(); i++) {
        if (this->obstacles[i]->intersects(p))
            return true;
    }
    return false;
    
}


double Map::get_height(Point p) {
    double ans = 0;
    for (int i = 0; i < this->obstacles.size(); i++) {
        if (this->obstacles[i]->intersects(p))
          ans = max(ans, this->obstacles[i]->get_height());
    }
    return ans;
    
}

void Map::add_obstacle(Obstacle *obstacle) {
    this->obstacles.push_back(obstacle);
}

void Map::init_map() {
    
    //room
    
    Point center = Point(0, -0.5, 0);
    Wall *floor = new Wall(width, length, 1, center);
    Point p1(0, 2, 40);
    Point p2(14.5, 2, 25);
    Point p3(-14.5, 2, 25);
    Point p4(0, 0.5, 15);
    Wall *w1 = new Wall(30, 1, 4, p1);
    Wall *w2 = new Wall(1, 30, 4, p2);
    Wall *w3 = new Wall(1, 30, 4, p3);
    Wall *step = new Wall(20, 20, 1, p4);
    this->obstacles.push_back(floor);
    this->obstacles.push_back(w1);
    this->obstacles.push_back(w2);
    this->obstacles.push_back(w3);
    this->obstacles.push_back(step);
    
}


