//
//  Camera.h
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/11/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//

#ifndef __Rafaat_Elhagan__Camera__
#define __Rafaat_Elhagan__Camera__

#include <stdio.h>
#include "Point.h"

class Camera {
    
private:
    double camera_x, camera_y, camera_z, center_x, center_y, center_z, look_depth;
    
public:
    
    Camera(double look_depth);
    Point simulate_mouse_motion(int mouse_x, int mouse_y);
};

#endif /* defined(__Rafaat_Elhagan__Camera__) */
