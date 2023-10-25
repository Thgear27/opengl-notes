#ifndef __SHADERPROGRAM_HPP__
#define __SHADERPROGRAM_HPP__

#include <glad/glad.h>
#include <string>

struct ShaderProgram {
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