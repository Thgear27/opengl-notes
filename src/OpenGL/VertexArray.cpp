#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include <cstddef>
#include <stdexcept>

VertexArray::VertexArray() { glGenVertexArrays(1, &Id); }

VertexArray::VertexArray(VertexBuffer* vbo) {
  glGenVertexArrays(1, &Id);
  m_vbo = vbo;
}

VertexArray::VertexArray(VertexBuffer* vbo, ElementBuffer* ebo) {
  glGenVertexArrays(1, &Id);
  m_vbo = vbo;
  m_ebo = ebo;
}

VertexArray::~VertexArray() {
  if (Id != 0) {
    glDeleteVertexArrays(1, &Id);
  }
}

void VertexArray::deleteVertexArray() {
  if (Id != 0) {
    glDeleteVertexArrays(1, &Id);
    Id = 0;
  }
}

void VertexArray::bind() { glBindVertexArray(Id); }

void VertexArray::unbind() { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(VertexBuffer* vbo) { m_vbo = vbo; }

void VertexArray::addeElementBuffer(ElementBuffer* ebo) { m_ebo = ebo; }

void VertexArray::linkBuffers() {
  bind();
  if (m_vbo == nullptr) throw std::runtime_error("No vertex buffer object binded to vertex array object");

  // Bind buffers to vertex array object
  m_vbo->bind();
  if (m_ebo != nullptr) m_ebo->bind();

  int offset = 0;
  for (int i = 0; i < m_vbo->m_vertexAttribCount; i++) {
    glVertexAttribPointer(
        i,                                                     // layout index
        m_vbo->m_AttribLayouts[i].count,                       // amount of components
        m_vbo->m_AttribLayouts[i].type,                        // type of components
        m_vbo->m_AttribLayouts[i].normalized, m_vbo->m_stride, // stride
        (const void*)(std::size_t)offset                       // offset
    );
    glEnableVertexAttribArray(i);
    offset += m_vbo->m_AttribLayouts[i].count * VertexBuffer::getTypeSize(m_vbo->m_AttribLayouts[i].type);
  }
  unbind();
}
