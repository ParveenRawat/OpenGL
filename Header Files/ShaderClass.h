#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>

std::string get_file_contents(const char *filename);

class Shader {
public:
  GLuint ID;
  Shader(const char *vertexFile, const char *fragmentFile);

  void Activate();
  void Delete();
};

#endif
