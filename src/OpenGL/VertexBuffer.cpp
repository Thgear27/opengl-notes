#include "VertexBuffer.hpp"
#include <stdexcept>

VertexBuffer::VertexBuffer(GLsizeiptr size, const void* data, GLenum usage) {
  glGenBuffers(1, &Id);
  loadData(size, data, usage);
}

VertexBuffer::VertexBuffer() { glGenBuffers(1, &Id); }

void VertexBuffer::loadData(GLsizeiptr size, const void* data, GLenum usage) {
  bind();
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::pushVertexAttribLayout(GLuint count, GLuint type, GLuint normalized) {
  m_AttribLayouts.push_back({ count, type, normalized });
  m_stride += count * getTypeSize(type);
  m_vertexAttribCount++;
}

void VertexBuffer::deleteBuffer() {
  if (Id != 0) {
    glDeleteBuffers(1, &Id);
    Id = 0;
  }
}

int VertexBuffer::getTypeSize(GLuint type) {
  if (type == GL_FLOAT) return sizeof(float);
  if (type == GL_UNSIGNED_INT) return sizeof(unsigned int);
  if (type == GL_UNSIGNED_BYTE) return sizeof(unsigned char);
  throw std::runtime_error("Cannot recognize GL_type in VertexBuffer::getTypeSize()");
}

VertexBuffer::~VertexBuffer() {
  if (Id != 0) deleteBuffer();
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void VertexBuffer::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}