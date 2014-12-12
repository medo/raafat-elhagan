//
//  main.cpp
//  Rafaat Elhagan
//
//  Created by Mohamed Farghal on 12/7/14.
//  Copyright (c) 2014 GUC. All rights reserved.
//
#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#elif defined __linux__
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include "Wall.h"
#include "util/objloader.h"

#include "Point.h"
#include <math.h>
#include "Util.h"
#include "Map.h"
#include <stdlib.h>
#include "Person.h"
#include <thread>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

void move();
void calculate_camera_direction();

double camera_x, camera_y, camera_z, max_jump, velocity_y, center_x, center_y, center_z, window_width, window_height, init_mouse_x, init_mouse_y, mouse_sensitivity, look_depth, horizontal_angle, vertical_angle, horizontal_angle_previous, vertical_angle_previous, motion_speed;
double prev_v_angle = 0, prev_h_angle=0;


int screen_width, screen_height;
bool jump, move_right, move_left, move_forward, move_back, is_shooting, is_hit, is_reset;
int vibrate_camera = 0;
Map map(100, 100);
Person *my_player, *other_player;

Point starting_positions[] = { Point(-10,10,0), Point(10,10,0) };
int player_id;

void reset_game();

void print(double x, double y, char *string){
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++){
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,string[i]);
  }
}

void render_overlay()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, window_width,0, window_height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    // Render 2D elements here
    stringstream ss1,ss2,ss3;

    // Game Information
    ss1 << "Your Score : " << my_player->get_score() << " , Other player score : " << other_player->get_score();
    ss2 << "Health : " << my_player->get_health();
    ss3 << "Opponent Health : " << other_player->get_health();


    glPushMatrix();
    glColor3d(1,1,1);
    print( 9, window_height - 15, (char *)ss1.str().c_str() );
    if( my_player->get_health() < 50 ){
        glColor3d(1,0,0);
    }
    print( window_width - ss2.str().size()*9 - 9, window_height - 15, (char *)ss2.str().c_str() );
    glColor3d(1,1,1);
    if( other_player->get_health() < 50 ){
        glColor3d(1,0,0);
    }
    print( window_width - ss3.str().size()*9 - 9, window_height - 35, (char *)ss3.str().c_str() );
    glPopMatrix();


    glBegin(GL_LINES);
    glColor3d(0.5,0.5,0.5);
    glVertex2d(window_width/2.0, window_height/2.0 - 10);
    glVertex2d(window_width/2.0, window_height/2.0 + 10);
    glEnd();


    glBegin(GL_LINES);
    glColor3d(0.5,0.5,0.5);
    glVertex2d(window_width/2.0 - 10, window_height/2.0);
    glVertex2d(window_width/2.0 + 10, window_height/2.0);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, window_width/window_height, 0.1, 1000);
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    move();
    Point looking_at = my_player->get_look_at();
    Point position = my_player->get_position();
    
    if( vibrate_camera ){
      gluLookAt(position.x + rand()%100/500.0, position.y + rand()%100/500.0, position.z + rand()%100/500.0, looking_at.x, looking_at.y, looking_at.z, 0, 1, 0);
      vibrate_camera --;
    }else{

      gluLookAt(position.x , position.y, position.z, looking_at.x, looking_at.y, looking_at.z, 0, 1, 0);
    }
    GLfloat lightIntensity[] = {0, 1,};
    GLfloat light_position[] = { 0, 0.3f, 0.0f, 1.0f };
    //    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightIntensity);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    map.draw();

    render_overlay();
    glFlush();

}

void move() {
    
    double horizontal_radians = Util::to_radians(horizontal_angle);
    double vertical_radians = Util::to_radians(vertical_angle);
    my_player->move_down(); //gravity
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

void keyboard_down(unsigned char key, int x, int y) {

    switch(key){

      case 'w':
        move_forward = false;
        break;

      case 's':
        move_back = false;
        break;

      case 'd':
        move_right = false;
        break;

      case 'a':
        move_left = false;
        break;
    }
}

void keyboard_up(unsigned char key, int x, int y) {

    if (key == ' ') {
        my_player->move_up();
    }
    
    switch (key) {
      case 'w':
        move_forward = true;
        break;

      case 's':
        move_back = true;
        break;

      case 'd':
        move_right = true;
        break;

      case 'a':
        move_left = true;
        break;

    }
}

void keyboard_up2(int key, int x, int y) {
    
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


void play_sound(string path){
#ifdef __APPLE__
    string x = "afplay " + path + " > /dev/null 2>&1 &";
#elif defined __linux__
    string x = "mpg321 " + path + " > /dev/null 2>&1 &";
#endif
    system(x.c_str());
}

void shoot(){
    string x = "./assets/rifle_sound.mp3";
    play_sound(x);
    int hit = map.shoot(my_player->get_position(), my_player->get_horizontal_angle(), my_player->get_vertical_angle());
    if( hit == 1 ){
      other_player->hit(30);
      if( other_player->is_dead() ){
        reset_game();
        is_reset = true;
        my_player->inc_score();
      }else{
        is_hit = true;
      }
    }
    is_shooting = true;
}

void mouse_clicks(int button, int state, int x,int y){
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ){
        shoot();
    }
}

void mouse_motion(int x, int y) {
    double prev_vertical = my_player->get_vertical_angle();
    double prev_horizontal = my_player->get_horizontal_angle();

    prev_vertical = -(y - window_height / 2.0) / mouse_sensitivity + prev_v_angle;
    prev_vertical = min(prev_vertical, 90.0);
    prev_vertical = max(prev_vertical, -90.0);
    prev_horizontal = -(x - window_width / 2.0) / mouse_sensitivity + prev_h_angle;

    my_player->set_vertical_angle(prev_vertical);
    my_player->set_horizontal_angle(prev_horizontal);

    if( x < 10 || x > window_width - 10 || y < 10 || y > window_height - 10 ){
      prev_v_angle = prev_vertical;
      prev_h_angle = prev_horizontal;
      glutWarpPointer(window_width/2.0,window_height/2.0);
    }
}

GLint gFramesPerSecond = 0;

void FPS(void) {
    static GLint Frames = 0;         // frames averaged over 1000mS
    static GLuint Clock;             // [milliSeconds]
    static GLuint PreviousClock = 0; // [milliSeconds]
    static GLuint NextClock = 0;     // [milliSeconds]
   
    ++Frames;
    Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
    if ( Clock < NextClock ) return;
   
    gFramesPerSecond = Frames/1; // store the averaged number of frames per second
   
    PreviousClock = Clock;
    NextClock = Clock+1000; // 1000mS=1S in the future
    Frames=0;
}

void loop() {

    #define REGULATE_FPS
    #ifdef REGULATE_FPS
    static GLuint PreviousClock=glutGet(GLUT_ELAPSED_TIME);
    static GLuint Clock=glutGet(GLUT_ELAPSED_TIME);
    static GLfloat deltaT;
   
    Clock = glutGet(GLUT_ELAPSED_TIME);
    deltaT=Clock-PreviousClock;
    if (deltaT < 15) {return;} else {PreviousClock=Clock;}
    #endif
    FPS();
    glutPostRedisplay();
}

void reporter(){
  while(1){
    Point p = my_player->get_position();
    double horizontal_angle = my_player->get_horizontal_angle();
    double vertical_angle = my_player->get_vertical_angle();
    cout << "p" << endl;
    cout << p.x << " " << p.y << " " << p.z << " " << horizontal_angle << " " << vertical_angle << endl;
    if( is_shooting ){
      cout << "s" << endl;
      is_shooting = false;
    }

    if(is_hit){
      cout << "h" << endl;
      cout << other_player->get_health() << endl;
      is_hit= false;
    }

    if(is_reset){
      cout << "r" << endl;
      is_reset= false;
    }

    int milliseconds = 10;
    usleep(milliseconds * 1000);
  }
}

void receiver(){
  while(1){
    double x,y,z,h_angle,v_angle;
    string type;
    cin >> type;
    if( type == "s" ){
      cerr << "Got : s" << endl;
      string x = "./assets/rifle_sound.mp3";
      play_sound(x);
    }else if( type == "h" ){
      int h;
      cin >> h;
      my_player->set_health(h);
      play_sound("./assets/pain.mp3");
      vibrate_camera = 20;
    }else if( type == "r" ){
      my_player->set_health(100);
      my_player->set_position(Point(0,10,-10));
      other_player->set_health(100);
      other_player->inc_score();
    }else{
 
      cin >> x >> y >> z >> h_angle >> v_angle;
      cerr << "Got : " << x << " " << y << " "<< z << " " << h_angle << " " << v_angle << endl;
      other_player->set_position(Point(x,y,z));
      other_player->set_vertical_angle(v_angle);
      other_player->set_horizontal_angle(h_angle);
    }
  }
}

void reset_game(){
    my_player->set_position(starting_positions[player_id]);
    my_player->set_health(100);
    other_player->set_position(starting_positions[player_id^1]);
    other_player->set_health(100);
}

int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // set
    //display mode
    
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    window_width = screen_width;
    window_height = screen_height;
    glutInitWindowSize(window_width, window_height); // set window size
    glutInitWindowPosition(300, 150); // set window position on
    //screen
    glutCreateWindow("Raafat Elhagan"); // open the screen window
    glutFullScreen(); glutDisplayFunc(display); // register redraw glutKeyboardFunc(keyboard_up);
    glutKeyboardFunc(keyboard_up);
    glutKeyboardUpFunc(keyboard_down);
    glutSpecialFunc(special_keyboard);
    glutSpecialUpFunc(keyboard_up2);
    glutMouseFunc(mouse_clicks);
    glutIdleFunc(loop);
    glutPassiveMotionFunc(mouse_motion);
    glutWarpPointer(window_width/2.0,window_height/2.0);
//    system("afplay ~/Desktop/rafat-elhagan.mp3 &");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    string player_type = argv[1];
    if( player_type == "1" ){
      player_id = 0;
    }else{
      player_id = 1;
    }
    my_player = new Person(starting_positions[player_id], 10, 0.1, 2, &map);
    other_player = new Person(starting_positions[player_id^1],10,0.1,2, &map);
    map.add_obstacle(other_player);
//    max_jump = 2.0;
    mouse_sensitivity = 10;
    //set the light source properties
    
    glEnable(GL_COLOR_MATERIAL);
    glutSetCursor(GLUT_CURSOR_NONE);
  
    thread _repoter(reporter);
    thread _receiver(receiver);
    map.load_texture();
    glutMainLoop(); // go into a perpetual loop
    
}



