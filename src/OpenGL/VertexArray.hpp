#ifndef __VERTEXARRAY_HPP__
#define __VERTEXARRAY_HPP__

#include "ElementBuffer.hpp"
#include "VertexBuffer.hpp"
class VertexArray {
  public:
  VertexArray(const VertexArray&) = delete;
  VertexArray& operator=(const VertexArray&) = delete;

  VertexArray();
  VertexArray(VertexBuffer* vbo);
  VertexArray(VertexBuffer* vbo, ElementBuffer* ebo);
  ~VertexArray();

  void deleteVertexArray();
  void bind();
  void unbind();
  void addVertexBuffer(VertexBuffer* vbo);
  void addeElementBuffer(ElementBuffer* ebo);
  void linkBuffers();

  GLuint Id = 0;

  ElementBuffer* m_ebo = nullptr;
  VertexBuffer* m_vbo = nullptr;
};

#endif // __VERTEXARRAY_HPP__