#ifndef __ELEMENTBUFFER_HPP__
#define __ELEMENTBUFFER_HPP__

#include <glad/glad.h>

class ElementBuffer {
  public:
  ElementBuffer(const ElementBuffer&)            = delete;
  ElementBuffer& operator=(const ElementBuffer&) = delete;

  ElementBuffer(GLsizeiptr size, const void* data, GLenum usage);
  ElementBuffer();
  ~ElementBuffer();

  void deleteBuffer();
  void loadData(GLsizeiptr size, const void* data, GLenum usage);
  void bind();
  void unbind();

  GLuint Id = 0;
};

#endif // __ELEMENTBUFFER_HPP__