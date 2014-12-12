#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "../Point.h"
#include <vector>

class objloader{

  public:
  bool loadOBJ(
          const char * path, 
          std::vector<Point> & out_vertices, 
          std::vector<Point> & out_uvs, 
          std::vector<Point> & out_normals
  );

  void draw(std::vector<Point> & out_vertices);
  GLuint loadBMP_custom(const char * imagepath)l

};

#endif
