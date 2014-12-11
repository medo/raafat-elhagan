//
//  Person.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/11/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Person.h"
#include <math.h>
#include "Util.h"
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif
#include <iostream>
#include "Map.h"


Person::Person(Point pos, double look_depth, double motion_speed, double height, Map *map) {
    this->pos = pos;
    this->look_depth = look_depth;
    this->motion_speed = motion_speed;
    this->height = height;
    this->map = map;
    this->length = 1;
    this->width = 1;
}

double Person::set_horizontal_angle(double angle) {
    this->horizontal_angle = angle;
    return horizontal_angle;
}

double Person::set_vertical_angle(double angle) {
    this->vertical_angle = angle;
    return this->vertical_angle;
}

double Person::get_horizontal_angle(){
    return this->horizontal_angle;
}


double Person::get_vertical_angle(){
    return this->vertical_angle;
}

Point Person::set_position(Point pos) {
    this->pos = pos;
    return this->pos;
}

Point Person::get_look_at() {
    
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    double center_z = pos.z + look_depth * cos(horizontal_radians) * cos(vertical_radians);
    double center_x = pos.x + look_depth * sin(horizontal_radians) * cos(vertical_radians);
    double center_y = pos.y + look_depth * sin(vertical_radians);
    return Point(center_x, center_y, center_z);
}

Point Person::get_position() {
    
    return pos;
}


bool Person::intersects(Point p) {
    return p.x >= pos.x - width/2.0 && p.x <= pos.x + width/2.0 && p.y >= pos.z - length/2.0 && p.y <= pos.z + length/2.0;
}

double Person::add_to_position_y(double y) {
    set_position(Point(pos.x, pos.y + y, pos.z));
    return y;
}


double Person::get_position_y() {

    return pos.y;
}

double Person::get_height() {
    return height;
}

void Person::draw() {
    
    glPushMatrix();

    glScaled(width, height, length);
    glTranslated(pos.x / width , pos.y / height, pos.z / length);
    glRotated(horizontal_angle, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();
}

bool Person::move_forward() {
    
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    double z = pos.z + motion_speed * cos(horizontal_radians);
    double x = pos.x + motion_speed * sin(horizontal_radians);
    if (map->intersects(Point(x + sin(horizontal_radians), pos.y - height/2.0, z + cos(horizontal_radians))))
        return false;
    pos.z = z;
    pos.x = x;
    return true;
}

bool Person::move_back() {
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    double z = pos.z - motion_speed * cos(horizontal_radians);
    double x = pos.x - motion_speed * sin(horizontal_radians);
    if (map->intersects(Point(x - sin(horizontal_radians), pos.y, z - cos(horizontal_radians))))
        return false;

    
    pos.z = z;
    pos.x = x;
    return true;
}

bool Person::move_right() {
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    double z = pos.z + motion_speed * sin(horizontal_radians);
    double x = pos.x - motion_speed * cos(horizontal_radians);
    if (map->intersects(Point(x - cos(horizontal_radians),  pos.y, z + sin(horizontal_radians))))
        return false;

    pos.z = z;
    pos.x = x;
    return true;
}

bool Person::move_left() {
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    double z = pos.z - motion_speed * sin(horizontal_radians);
    double x = pos.x + motion_speed * cos(horizontal_radians);
    if (map->intersects(Point(x + cos(horizontal_radians),  pos.y, z - sin(horizontal_radians))))
        return false;
    pos.z = z;
    pos.x = x;
    
    return true;
}

bool Person::move_down() {
    if (map->intersects(Point(pos.x, pos.y - height/2.0, pos.z))) {
        velocity = 0;
        pos.y = height/2.0;
        return false;
    }
    
    velocity -= 0.02;
    pos.y += velocity;
    return true;
}

bool Person::move_up() {
    velocity = 0.4;
    pos.y += velocity;
    return true;
}



