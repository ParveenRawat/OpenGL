#include "../Header Files/Mesh.h"
#include <string>

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices,
           std::vector<Texture> &textures) {
  Mesh::vertices = vertices;
  Mesh::indices = indices;
  Mesh::textures = textures;

  VAOx.Bind();

  VBO VBOx(vertices);
  EBO EBOx(indices);

  VAOx.LinkAttrib(VBOx, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
  VAOx.LinkAttrib(VBOx, 1, 3, GL_FLOAT, sizeof(Vertex),
                  (void *)(3 * sizeof(float)));
  VAOx.LinkAttrib(VBOx, 2, 3, GL_FLOAT, sizeof(Vertex),
                  (void *)(6 * sizeof(float)));
  VAOx.LinkAttrib(VBOx, 3, 2, GL_FLOAT, sizeof(Vertex),
                  (void *)(9 * sizeof(float)));
  VAOx.Unbind();
  VBOx.Unbind();
  EBOx.Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera) {
  shader.Activate();
  VAOx.Bind();
  unsigned int numDiffuse = 0;
  unsigned int numSpecular = 0;
  for (unsigned int i = 0; i < textures.size(); i++) {
    std::string num;
    std::string type = textures[i].type;

    if (type == "diffuse") {
      num = std::to_string(numDiffuse++);
    } else if (type == "specular") {
      num = std::to_string(numSpecular++);
    }

    textures[i].texUnit(shader, (type + num).c_str(), i);
    textures[i].Bind();
  }

  glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x,
              camera.Position.y, camera.Position.z);

  camera.Matrix(shader, "camMatrix");

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
