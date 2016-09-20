#include "object.h"
#include "engine.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  planetAngle = 0.0f;
  moonAngle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt, int &keystroke, int &mouseclick)
{
  // if nothing is pressed or pressed same key twice --> normal mode
  if (keystroke == 0 && mouseclick == 0) 
  {
	planetAngle += dt * M_PI/1000;
	orbitAngle += dt * M_PI/1000;
	moonAngle += dt * M_PI/500;
  }
  // if right ALT or left mouse button is pressed --> reverse planet and moon orbit 
  else if (keystroke == 2 || mouseclick == 2)
  {
	planetAngle -= dt * M_PI/1000;
	orbitAngle -= dt * M_PI/1000;
	moonAngle -= dt * M_PI/500;
  }
  // if right CTRL pressed or right mouse button is pressed --> stop spin and continue orbit
  else if (keystroke == 3 || mouseclick == 3) 
  {
	planetAngle += dt * M_PI/1000;
	moonAngle += dt * M_PI/500;
  }
  // if DELETE is pressed --> spin planet at last updated position with no orbit
  else if (keystroke == 4) 
  {
	orbitAngle += dt * M_PI/1000;
	moonAngle += dt * M_PI/500;
  }
  // if TAB pressed --> reverse only moon orbit
  else if (keystroke == 5) 
  {
	planetAngle += dt * M_PI/1000;
	orbitAngle += dt * M_PI/1000;
	moonAngle -= dt * M_PI/500;
  }

  model = glm::rotate(glm::mat4(1.0f), (planetAngle), glm::vec3(0.0, 1.0, 0.0))*glm::translate(glm::mat4(1.0f), glm::vec3(5.0, 1.0, 0.0))*
										glm::rotate(glm::mat4(1.0f), (orbitAngle), glm::vec3(0.0, 1.0, 0.0));
  moon = glm::rotate(glm::mat4(model), (moonAngle), glm::vec3(0.0, 1.0, 0.0))*glm::translate(glm::mat4(1.0f), glm::vec3(3.0, 0.0, 0.0))*
										glm::rotate(glm::mat4(1.0f), (moonAngle), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Object::GetModel()
{
  return model;

}

glm::mat4 Object::GetMoon()
{
  return moon;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}


















