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
#include <stdlib.h>
#include "Person.h"


using namespace std;


void move();
void calculate_camera_direction();

double camera_x, camera_y, camera_z, max_jump, velocity_y, center_x, center_y, center_z, window_width, window_height, init_mouse_x, init_mouse_y, mouse_sensitivity, look_depth, horizontal_angle, vertical_angle, horizontal_angle_previous, vertical_angle_previous, motion_speed;

int screen_width, screen_height;
bool jump, move_right, move_left, move_forward, move_back;
Map map(100, 100);
Person *my_player, *other_player;

void display() {
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, window_width/window_height, 0.1, 115);
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    move();
    Point looking_at = my_player->get_look_at();
    Point position = my_player->get_position();
    other_player->draw();
    gluLookAt(position.x, position.y, position.z, looking_at.x, looking_at.y, looking_at.z, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    map.draw();
    glPopMatrix();
    glFlush();


}




void move() {
    
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    my_player->add_to_position_y(velocity_y); //jump
    if (my_player->get_position_y() > my_player->get_height()) velocity_y -= 0.02; else velocity_y = 0;
    if (move_forward){
        my_player->move_forward();
    }
    if (move_back){
        my_player->move_back();
    }
    if (move_right){
        my_player->move_right();
    }
    if (move_left){
        my_player->move_left();
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
    
    my_player->set_vertical_angle(-(y - window_height / 2.0) / mouse_sensitivity);
    my_player->set_horizontal_angle(-(x - window_width / 2.0) / mouse_sensitivity);
    if (x >= window_width) {
//        glutWarpPointer(0, 0);
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
//    system("afplay ~/Desktop/rafat-elhagan.mp3 &");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    cout << cos(2 * acos(-1));
    my_player = new Person(Point(0, 10, 0), 10, 0.1, 2, &map);
    other_player = new Person(Point(0, 10, 0), 10, 0.1, 2, &map);
//    max_jump = 2.0;
    mouse_sensitivity = 5;
    //set the light source properties
    GLfloat lightIntensity[] = { 0.3f, 0.9f, 1, 1.0f };
    GLfloat light_position[] = { 0, 0.3f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    glEnable(GL_COLOR_MATERIAL);
    glutMainLoop(); // go into a perpetual loop
    
}



