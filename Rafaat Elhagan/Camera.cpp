//
//  Camera.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/11/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Camera.h"
#include "Point.h"

Camera::Camera(double look_depth) {
    this->look_depth = look_depth;
    this->camera_x = 0.0;
    this->camera_y = 0.0;
    this->camera_z = 0.0;
    
}

Point Camera::simulate_mouse_motion(int mouse_x, int mouse_y) {
    
    double horizontal_radians = to_radians(horizontal_angle);
    double vertical_radians = to_radians(vertical_angle);
    center_z = camera_z + look_depth * cos(horizontal_radians) * cos(vertical_radians);
    center_x = camera_x + look_depth * sin(horizontal_radians) * cos(vertical_radians);
    center_y = camera_y + look_depth * sin(vertical_radians);
    Point p(center_x, center_y, center_z);
    return p;
    
}
