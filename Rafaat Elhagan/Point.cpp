//
//  Point.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#include "Point.h"

Point::Point() {
    
    this -> x = 0;
    this -> y = 0;
    this -> z = 0;
}

Point::Point(double x, double y, double z) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
}