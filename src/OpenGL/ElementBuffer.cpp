#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer(GLsizeiptr size, const void* data, GLenum usage) {
  glGenBuffers(1, &Id);
  loadData(size, data, usage);
}

ElementBuffer::ElementBuffer() { glGenBuffers(1, &Id); }

ElementBuffer::~ElementBuffer() {
  if (Id != 0) deleteBuffer();
}

void ElementBuffer::deleteBuffer() {
  if (Id != 0) {
    glDeleteBuffers(1, &Id);
    Id = 0;
  }
}

void ElementBuffer::loadData(GLsizeiptr size, const void* data, GLenum usage) {
  bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void ElementBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id); }

void ElementBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
