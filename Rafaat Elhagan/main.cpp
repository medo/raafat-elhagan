//
//  main.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//


#include <GLUT/GLUT.h>
#include <iostream>
#include <stdlib.h>
#include "Wall.h"
#include "Point.h"
#include <math.h>
#include "Util.h"
#include "Map.h"


using namespace std;


void move();
void calculate_camera_direction();

double camera_x, camera_y, camera_z, max_jump, velocity_y, center_x, center_y, center_z, window_width, window_height, init_mouse_x, init_mouse_y, mouse_sensitivity, look_depth, horizontal_angle, vertical_angle, horizontal_angle_previous, vertical_angle_previous, motion_speed;

int screen_width, screen_height;
bool jump, move_right, move_left, move_forward, move_back;
Map map(100, 100);

void display() {
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, window_width/window_height, 0.1, 115);
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    move();
    calculate_camera_direction();
    gluLookAt(camera_x, camera_y, camera_z, center_x, center_y, center_z, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    map.draw();
    glPopMatrix();
    glFlush();


}


void calculate_camera_direction() {
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    center_z = camera_z + look_depth * cos(horizontal_radians) * cos(vertical_radians);
    center_x = camera_x + look_depth * sin(horizontal_radians) * cos(vertical_radians);
    center_y = camera_y + look_depth * sin(vertical_radians);
    
}

void move() {
    
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    camera_y += velocity_y; //jump
    if (camera_y > 0) velocity_y -= 0.02; else velocity_y = 0;
    //moving
    cout << camera_x << " " << camera_z << "\n";
    if (move_forward){
        camera_z += motion_speed * cos(horizontal_radians);
        camera_x += motion_speed * sin(horizontal_radians);
    }
    if (move_back){
        camera_z -= motion_speed * cos(horizontal_radians);
        camera_x -= motion_speed * sin(horizontal_radians);
    }
    if (move_right){
        camera_z += motion_speed * sin(horizontal_radians);
        camera_x -= motion_speed * cos(horizontal_radians);
    }
    if (move_left){
        camera_z -= motion_speed * sin(horizontal_radians);
        camera_x += motion_speed * cos(horizontal_radians);
    }
}

void keyboard(unsigned char key, int x, int y) {
   
    if (key == ' ') {
        velocity_y = 0.3;
    }
}

void keyboard_up(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_UP:
            move_forward = false;
            break;
        case GLUT_KEY_DOWN:
            move_back = false;
            break;
        case GLUT_KEY_RIGHT:
            move_right = false;
            break;
        case GLUT_KEY_LEFT:
            move_left = false;
            break;
        default:
            break;
    }

}

void special_keyboard(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_UP:
            move_forward = true;
            break;
        case GLUT_KEY_DOWN:
            move_back = true;
            break;
        case GLUT_KEY_RIGHT:
            move_right = true;
            break;
        case GLUT_KEY_LEFT:
            move_left = true;
            break;
        default:
            break;
    }
}

void mouse_motion(int x, int y) {
    
    vertical_angle = -(y - window_height / 2.0) / mouse_sensitivity;
    horizontal_angle = -(x - window_width / 2.0) / mouse_sensitivity;
    if (x >= window_width) {
        glutWarpPointer(0, 0);
    }
}

void loop() {
    
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set
    //display mode
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    window_width = 640;
    window_height = 480;
    glutInitWindowSize(window_width, window_height); // set window size
    glutInitWindowPosition(300, 150); // set window position on
    //screen
    glutCreateWindow("Raafat Elhagan"); // open the screen window
    glutDisplayFunc(display); // register redraw
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    glutSpecialUpFunc(keyboard_up);
    glutIdleFunc(loop);
    glutPassiveMotionFunc(mouse_motion);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    cout << cos(2 * acos(-1));
    camera_z = 0.0;
    center_x = 0.0;
    max_jump = 2.0;
    center_x = 0.0;
    center_y = 0.0;
    look_depth = 20.0;
    center_z = look_depth;
    mouse_sensitivity = 5;
    init_mouse_x = -999999999;
    init_mouse_y = -999999999;
    motion_speed = 0.1;
    horizontal_angle = 0;
    vertical_angle = 0;
    //set the light source properties
    GLfloat lightIntensity[] = { 0.3f, 0.9f, 1, 1.0f };
    GLfloat light_position[] = { 0, 0.3f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glEnable(GL_COLOR_MATERIAL);
    glutMainLoop(); // go into a perpetual loop
    
}



