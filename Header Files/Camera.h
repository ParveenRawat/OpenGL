#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

#include "ShaderClass.h"

class Camera {
public:
  glm::vec3 Position;
  glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

  int width;
  int height;

  bool firstClick = true;

  float speed = 0.1f;
  float sensitivity = 100.0f;

  Camera(int width, int height, glm::vec3 postion);

  void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader,
              const char *uniform);
  void Inputs(GLFWwindow *window);
};

#endif // !CAMERA_CLASS_H
