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
    //bool pause;
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    //SDL_Event m_event;
    float angle;
};

#endif /* OBJECT_H */
