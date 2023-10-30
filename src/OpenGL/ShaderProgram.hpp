#ifndef __SHADERPROGRAM_HPP__
#define __SHADERPROGRAM_HPP__

#include <glad/glad.h>
#include <string>

class ShaderProgram {
  public:
  GLuint programId = 0;
  std::string vertexShaderSource;
  std::string fragmentShaderSource;

  void use();
  void deleteprogram();
  void setFloat(const std::string& name, float value);
  GLuint Id();
  ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
  ~ShaderProgram();
};

#endif // __SHADERPROGRAM_HPP__