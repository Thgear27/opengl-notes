#ifndef __VERTEXBUFFER_HPP__
#define __VERTEXBUFFER_HPP__

#include <glad/glad.h>
#include <vector>

// It can have many vertex attributes in a single buffer
class VertexBuffer {
  private:
  // Define a vertex attribute layout
  struct VertexAtribLayout {
    GLuint count;      // Amount of vertex attribute components
    GLuint type;       // Type of vertex attribute components
    GLuint normalized; // Is the vertex attribute normalized?
  };

  public:
  // TODO: Make this class copyable
  VertexBuffer(const VertexBuffer&)            = delete;
  VertexBuffer& operator=(const VertexBuffer&) = delete;

  VertexBuffer(GLsizeiptr size, const void* data, GLenum usage);
  VertexBuffer();
  ~VertexBuffer();

  void loadData(GLsizeiptr size, const void* data, GLenum usage);

  // It pushes a new vertex attribute layout to the buffer
  void pushVertexAttribLayout(GLuint count, GLuint type, GLuint normalized);
  void bind();
  void unbind();
  void deleteBuffer();

  static int getTypeSize(GLuint type);

  GLuint Id               = 0;
  int m_stride            = 0;
  int m_vertexAttribCount = 0; // Amount of vertex attributes in the buffer, the same as m_AttribLayouts.size()
  std::vector<VertexAtribLayout> m_AttribLayouts;
};

#endif // __VERTEXBUFFER_HPP__