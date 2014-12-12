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
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif
#include "TextureBuilder.h"
#include <stdlib.h>
#include <iostream>
#include "Util.h"
#include <cmath>


GLuint Map::eboxTexture;

Map::Map(int width, int length) {
    this->width = width;
    this->length = length;
    init_map();
}

void Map::load_texture() {
    Map::eboxTexture = LoadTexture("sky_.ppm", 1200, 812, false);
}

void Map::draw() {
    
    
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glRotated(-90,1,0,0);
    GLUquadricObj* esphere = gluNewQuadric();
    gluQuadricOrientation(esphere, GLU_INSIDE);
    gluQuadricTexture(esphere, true);
    gluQuadricNormals(esphere, GLU_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, eboxTexture);
    glEnable(GL_CULL_FACE);
    gluSphere(esphere, 400, 100, 100); //universe sphere
    gluDeleteQuadric(esphere);
    glPopMatrix();
    
    

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

int Map::shoot(Point pos, double h_angle, double v_angle){
  
    double horizontal_radians = Util::to_radians(h_angle);
    double vertical_radians = Util::to_radians(v_angle);

    pos.z = pos.z + 1 * cos(horizontal_radians);
    pos.x = pos.x + 1 * sin(horizontal_radians);
    pos.y = pos.y + 1 * sin(vertical_radians);
    
    while(pos.x > -width/2.0 && pos.x < width/2.0 && pos.z > -length/2.0 && pos.z < length/2.0 && pos.y >= 0 && pos.y < 1000){
        for (int i = 0; i < this->obstacles.size(); i++) {
            if(this->obstacles[i]->intersects(pos)){
                if(this->obstacles[i]->get_type() == 0){
                  return 0;
                }else{
                  return 1;
                }
            }
        }

        pos.z = pos.z + 1 * cos(horizontal_radians);
        pos.x = pos.x + 1 * sin(horizontal_radians);
        pos.y = pos.y + 1 * sin(vertical_radians);

    }

    return -1;
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

