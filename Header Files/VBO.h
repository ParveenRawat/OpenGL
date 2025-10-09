#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>

struct Vertex {
  glm::vec3 postion;
  glm::vec3 normal;
  glm::vec3 color;
  glm::vec2 texUV;
};

class VBO {
public:
  GLuint ID;
  VBO(std::vector<Vertex> &vertices);

  void Bind();
  void Unbind();
  void Delete();
};

#endif // !VBO_CLASS_H
