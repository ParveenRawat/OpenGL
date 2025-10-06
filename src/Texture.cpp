#include "../Header Files/Texture.h"

Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format,
                 GLenum pixelType) {
  type = texType;
  int widthImg, heightImg, numColCh;

  stbi_set_flip_vertically_on_load(true);
  unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
  if (!bytes) {
    std::cerr << "Failed to load texture" << std::endl;
    return;
  }

  glGenTextures(1, &ID);
  glActiveTexture(slot);
  glBindTexture(texType, ID);

  glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // flat flatcolor[] = {1.0f,1.0f,1.0f,1.0f};
  // glTexParameteri(texType,GL_TEXTURE_BORDER_COLOR,flatcolor);
  //
  // TODO : format isnt required to be passed in the constructor as it is auto
  // detected
  // // GLenum imgFormat = ...
  format = (numColCh == 4) ? GL_RGBA : GL_RGB;
  glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType,
               bytes);

  glGenerateMipmap(texType);

  stbi_image_free(bytes);
  glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char *uniform, GLuint unit) {
  GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
  shader.Activate();
  glUniform1i(tex0Uni, unit);
}

void Texture::Bind() { glBindTexture(type, ID); }

void Texture::Unbind() { glBindTexture(type, 0); }

void Texture::Delete() { glDeleteTextures(1, &ID); }
