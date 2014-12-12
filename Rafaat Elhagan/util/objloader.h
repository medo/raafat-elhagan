#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../Point.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#elif defined __linux__
#include <GL/glut.h>
#endif

class objloader{

  public:
  static bool loadOBJ(
          const char * path, 
          std::vector<Point> & out_vertices, 
          std::vector<Point> & out_uvs, 
          std::vector<Point> & out_normals
  );

  static void draw(std::vector<Point> & out_vertices);
  static GLuint loadBMP_custom(const char * imagepath);

};

#endif
