#include "object.h"

Object::Object()
{ 
  angle = 0.0f;
  
  std::vector<glm::vec3> normals;
  
  load_obj("/home/nirmit/Desktop/CS480/computer-graphics/PA4/src/box.obj", Vertices, normals, Indices);
/*
  printf("\n");
  for (int i = 0; i < Vertices.size(); i++)
	printf ("%f %f %f\n", Vertices[i].x, Vertices[i].y, Vertices[i].z);
 
  printf("\n");
  for (int i = 0; i < Indices.size(); i++)
	printf ("%d\n", Indices[i]);
*/
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

void Object::load_obj(const char* filename, std::vector<glm::vec3> &Vertices, std::vector<glm::vec3> &normals, std::vector<unsigned int> &Indices)
{
    char ignore;
    int ignoreNum;
    std::ifstream fin;

    fin.open (filename);
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
            glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
            Vertices.push_back(v);
        }
        else if (line.substr(0,2) == "f ")
        {
            std::istringstream s(line.substr(2));
            GLuint a,b,c;
	    
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
            Indices.push_back(a); Indices.push_back(b); Indices.push_back(c);
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

    normals.resize(Vertices.size(), glm::vec3(0.0, 0.0, 0.0));
    for (int i = 0; i < Indices.size(); i+=3)
    {
        GLuint ia = Indices[i];
        GLuint ib = Indices[i+1];
        GLuint ic = Indices[i+2];
        glm::vec3 normal = glm::normalize(glm::cross(
        glm::vec3(Vertices[ib]) - glm::vec3(Vertices[ia]),
        glm::vec3(Vertices[ic]) - glm::vec3(Vertices[ia])));
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













