#include "../Header Files/ShaderClass.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

// Load file contents into a string
std::string get_file_contents(const char *filename) {
  std::ifstream in(filename, std::ios::binary);
  if (!in) {
    throw std::runtime_error(std::string("Failed to open file: ") + filename);
  }
  std::string contents;
  in.seekg(0, std::ios::end);
  contents.resize(in.tellg());
  in.seekg(0, std::ios::beg);
  in.read(&contents[0], contents.size());
  in.close();

  return contents;
}

// Shader constructor with compilation and linking logs
Shader::Shader(const char *vertexFile, const char *fragmentFile) {
  std::string vertexCode = get_file_contents(vertexFile);
  std::string fragmentCode = get_file_contents(fragmentFile);

  const char *vertexSource = vertexCode.c_str();
  const char *fragmentSource = fragmentCode.c_str();

  // Vertex Shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::VERTEX_SHADER_COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Fragment Shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // Shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER_PROGRAM_LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  // Delete shaders (already linked)
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// Activate shader
void Shader::Activate() { glUseProgram(ID); }

// Delete shader program
void Shader::Delete() { glDeleteProgram(ID); }
