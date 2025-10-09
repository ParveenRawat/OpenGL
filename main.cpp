#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "Header Files/stb_image.h"

#include "Header Files/Camera.h"
#include "Header Files/EBO.h"
#include "Header Files/ShaderClass.h"
#include "Header Files/Texture.h"
#include "Header Files/VAO.h"
#include "Header Files/VBO.h"

const unsigned int width = 600;
const unsigned int height = 600;

// Vertices coordinates
GLfloat vertices[] = { //     COORDINATES     /        COLORS        / TexCoord
                       //     /       NORMALS     //
    -1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    1.0f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3};

GLfloat lightVertices[] = {-0.1f, -0.1f, 0.1f,  -0.1f, -0.1f, -0.1f,
                           0.1f,  -0.1f, -0.1f, 0.1f,  -0.1f, 0.1f,
                           -0.1f, 0.1f,  0.1f,  -0.1f, 0.1f,  -0.1f,
                           0.1f,  0.1f,  -0.1f, 0.1f,  0.1f,  0.1f};

GLuint lightIndices[] = {0, 1, 2, 0, 2, 3, 0, 4, 7, 0, 7, 3, 3, 7, 6, 3, 6, 2,
                         2, 6, 5, 2, 5, 1, 1, 5, 4, 1, 4, 0, 4, 5, 6, 4, 6, 7};

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(width, height, "MyApp", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to load glew" << std::endl;
    return -1;
  }

  glViewport(0, 0, width, height);

  Shader shaderProgram("./resources/shaders/vertexShader.glsl",
                       "./resources/shaders/fragmentShader.glsl");

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float),
                  (void *)(3 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float),
                  (void *)(6 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float),
                  (void *)(8 * sizeof(float)));
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  Shader lightShader("./resources/shaders/lightVert.glsl",
                     "./resources/shaders/lightFrag.glsl");

  VAO lightVAO;
  lightVAO.Bind();

  VBO lightVBO(lightVertices, sizeof(lightVertices));
  EBO lightEBO(lightIndices, sizeof(lightIndices));

  lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);

  lightVAO.Unbind();
  lightVBO.Unbind();
  lightEBO.Unbind();

  glm::vec4 lightColor = glm::vec4(1.0f);

  glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::mat4 lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  glm::vec3 pyramidPos = glm::vec3(0.0f, -1.0f, 0.0f);
  glm::mat4 pyramidModel = glm::mat4(1.0f);
  pyramidModel = glm::translate(pyramidModel, pyramidPos);

  shaderProgram.Activate();
  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"),
              lightColor.x, lightColor.y, lightColor.z, lightColor.w);
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1,
                     GL_FALSE, glm::value_ptr(pyramidModel));
  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x,
              lightPos.y, lightPos.z);

  lightShader.Activate();
  glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x,
              lightColor.y, lightColor.z, lightColor.w);
  glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE,
                     glm::value_ptr(lightModel));

  // GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

  Texture plankTex("./resources/textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE);
  plankTex.texUnit(shaderProgram, "tex0", 0);

  Texture plankSpec("./resources/textures/planksSpec.png", GL_TEXTURE_2D, 1,
                    GL_RED, GL_UNSIGNED_BYTE);
  plankSpec.texUnit(shaderProgram, "tex1", 1);

  glEnable(GL_DEPTH_TEST);

  Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.4f, 0.7f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.Inputs(window);

    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    shaderProgram.Activate();
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"),
                camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shaderProgram, "camMatrix");

    glUniform1f(glGetUniformLocation(shaderProgram.ID, "scale"), -0.1f);

    plankTex.Bind();
    plankSpec.Bind();
    VAO1.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT,
                   0);

    lightShader.Activate();
    camera.Matrix(lightShader, "camMatrix");

    lightVAO.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int),
                   GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  plankTex.Delete();
  shaderProgram.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
