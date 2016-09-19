#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
//#include "SDL.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt, int &keystroke, int &mouseclick);
    void Render();
    glm::mat4 GetModel();
    glm::mat4 GetMoon();

  private:
    glm::mat4 model;
    glm::mat4 moon;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    float angle;
};

#endif /* OBJECT_H */
