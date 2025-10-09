#include "../Header Files/Texture.h"
#include "../Header Files/stb_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "./../Header Files/stb_image.h"

Texture::Texture(const char *image, const char *texType, GLuint slot,
                 GLenum format, GLenum pixelType) {
  type = texType;

  int widthImg, heightImg, numColCh;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

  glGenTextures(1, &ID);
  glActiveTexture(GL_TEXTURE0 + slot);
  unit = slot;
  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
  // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

  // format = (numColCh == 4) ? GL_RGBA : GL_RGB;

  // TODO: Why am i still passing format? idk

  switch (numColCh) {
  case 1:
    format = GL_RED;
    break;
  case 3:
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  default:
    format = GL_RGBA;
    break;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format,
               pixelType, bytes);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(bytes);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit) {
  GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
  shader.Activate();
  glUniform1i(tex0Uni, unit);
}

void Texture::Bind() {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture::Delete() { glDeleteTextures(1, &ID); }
