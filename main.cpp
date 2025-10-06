#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "Header Files/stb_image.h"

#include "Header Files/EBO.h"
#include "Header Files/ShaderClass.h"
#include "Header Files/Texture.h"
#include "Header Files/VAO.h"
#include "Header Files/VBO.h"

int main() {

  GLfloat vertices[] = {
      // Vertices_3 + Colors_3 + Texture Data_2
      0.5f, 0.5f, 0.0f,  0.3f, 0.1f, 0.2f,  1.0f,  1.0f, 0.5f, -0.5f, 0.0f,
      0.2f, 0.7f, 1.0f,  1.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.8f, 0.3f,  0.4f,
      0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.8f,  0.3f,  0.4f, 0.0f, 1.0f,
  };

  GLuint indices[] = {0, 1, 2, 2, 3, 0};

  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Window Creation
  GLFWwindow *window = glfwCreateWindow(600, 600, "MyApp", NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // glew Instanciation = OpenGL context creation
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to load glew" << std::endl;
    return -1;
  }

  int fbWidth, fbHeight;
  glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  Shader shaderProgram("resources/shaders/vertexShader.glsl",
                       "resources/shaders/fragmentShader.glsl");

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float),
                  (void *)(3 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
                  (void *)(6 * sizeof(float)));

  VBO1.Unbind();
  VAO1.Unbind();
  EBO1.Unbind();

  Texture cat("./resources/textures/cat.png", GL_TEXTURE_2D, GL_TEXTURE0,
              GL_RGBA, GL_UNSIGNED_BYTE);
  cat.texUnit(shaderProgram, "tex0", 0);

  GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.Activate();
    glUniform1f(uniID, 0.5f);

    cat.Bind();

    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();
  cat.Delete();

  glfwTerminate();
  return 0;
}
