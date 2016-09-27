#include "object.h"

Object::Object()
{ 
/*  Vertices = {
    {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}
  };

  Indices = {
    1, 2, 3
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }
*/


  angle = 0.0f;
  
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<GLushort> elements;
  
  load_obj("/home/nirmit/Desktop/CS480/computer-graphics/PA4/src/box.obj", vertices, normals, elements);

  for (int i = 0; i < vertices.size(); i++) {
	printf ("%f %f %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
  }
  for (int i = 0; i < elements.size(); i++) {
	printf ("%d %d %d\n", elements[i].a, elements[i].b, elements[i].c);
  }

	//printf("%f\n", vertices);
/*
  glEnableVertexAttribArray(attribute_v_coord);
  // Describe our vertices array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(
    attribute_v_coord,  // attribute
    4,                  // number of elements per vertex, here (x,y,z,w)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  glEnableVertexAttribArray(attribute_v_normal);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(
    attribute_v_normal, // attribute
    3,                  // number of elements per vertex, here (x,y,z)
    GL_FLOAT,           // the type of each element
    GL_FALSE,           // take our values as-is
    0,                  // no extra data between each position
    0                   // offset of first element
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);  
  glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
*/
/*
  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);*/

/*	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("/home/nirmit/Desktop/CS480/computer-graphics/PA4/src/box.obj", vertices, uvs, normals);*/


  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(glm::vec2), &elements[0], GL_STATIC_DRAW);

	// Load it into a VBO
/*
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);*/
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::load_obj(const char* filename, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<GLushort> &elements)
{
    char ignore;
    int ignoreNum;
    std::ifstream fin;

    fin.open (filename);
    //std::ifstream file(filename);
    if (!fin.good()){
    	std::cout << "Couldn't find the file..." << std::endl;
	exit(1);
    }

    std::string line;
    while (getline(fin, line))
    {
        if (line.substr(0,2) == "v ")
        {
            std::istringstream s(line.substr(2));
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z; //v.w = 1.0f;
	    //printf("%f %f %f\n", v.x, v.y, v.z);
            vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            std::istringstream s(line.substr(2));
            GLushort a,b,c;
	    
	    s >> a;
	    s >> ignore;
            if (ignore == '/') {
	    	s >> ignore;
	    	s >> ignoreNum;
		s >> b;
	    }
	    else {
	    	b = ignore;
	    }
	    s >> ignore;
            if (ignore == '/') {
	    	s >> ignore;
	    	s >> ignoreNum;
		s >> c;
	    }
	    else {
	    	c = ignore;
	    }
   	    //printf("%d %d %d\n", a, b, c);
            a--; b--; c--;
            elements.push_back(a); elements.push_back(b); elements.push_back(c);
        }
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
    }

    normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < elements.size(); i+=3)
    {
        GLushort ia = elements[i];
        GLushort ib = elements[i+1];
        GLushort ic = elements[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(
        glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
        glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));
        normals[ia] = normals[ib] = normals[ic] = normal;
    }
}
					
void Object::Update(unsigned int dt)
{
  model = glm::mat4(1.0f);
}

glm::mat4 Object::GetModel()
{
  return model;
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

