#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "OpenGL/ShaderProgram.hpp"
#include "OpenGL/ElementBuffer.hpp"
#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"
#include "stb_image.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // En esta pedazo de código se cargan las funciones de OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Solo desde aquí podemos utilizar las funciones de OpenGL

  ShaderProgram shaderProgram(
      "./resources/vertexshader.vert",  //
      "./resources/fragmentshader.frag" //
  );

  // 1.- Mandamos la información a la GPU
  float vertices[] = {
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
  };

  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  VertexBuffer vbo;
  ElementBuffer ebo;

  vbo.loadData(sizeof(vertices), vertices, GL_STATIC_DRAW);
  vbo.pushVertexAttribLayout(3, GL_FLOAT, GL_FALSE);
  vbo.pushVertexAttribLayout(3, GL_FLOAT, GL_FALSE);
  vbo.pushVertexAttribLayout(2, GL_FLOAT, GL_FALSE);
  ebo.loadData(sizeof(indices), indices, GL_STATIC_DRAW);

  VertexArray vao(&vbo, &ebo); // vertex array object
  vao.linkBuffers();

  // loading texture
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load("./resources/Profile-photo.png", &width, &height, &nrChannels, 4);
  std::cout << "nrChannels: " << nrChannels << std::endl;

  unsigned int texture1;
  glGenTextures(1, &texture1);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
      GL_TEXTURE_2D,    // target
      0,                // level
      GL_RGBA,          // internal format
      width,            // width
      height,           // height
      0,                // border
      GL_RGBA,          // format
      GL_UNSIGNED_BYTE, // type
      data              // data
  );
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  unsigned char* data2 = stbi_load("./resources/mcblock.jpg", &width, &height, &nrChannels, 4);
  std::cout << "nrChannels: " << nrChannels << std::endl;

  unsigned int texture2;
  glGenTextures(1, &texture2);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(
      GL_TEXTURE_2D,    // target
      0,                // level
      GL_RGBA,          // internal format
      width,            // width
      height,           // height
      0,                // border
      GL_RGBA,          // format
      GL_UNSIGNED_BYTE, // type
      data2             // data
  );
  glGenerateMipmap(GL_TEXTURE_2D);

  // glActiveTexture(GL_TEXTURE0); // activate texture unit first
  // glBindTexture(GL_TEXTURE_2D, texture1);
  // glActiveTexture(GL_TEXTURE1); // activate texture unit first
  // glBindTexture(GL_TEXTURE_2D, texture2);

  stbi_image_free(data2);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  shaderProgram.use();
  shaderProgram.setInt("texture1", 0);
  shaderProgram.setInt("texture2", 1);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    shaderProgram.setFloat("mivariable2", std::abs(std::sin(time)));

    vao.bind();
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vbo.deleteBuffer();
  ebo.deleteBuffer();
  vao.deleteVertexArray();
  shaderProgram.deleteprogram();
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}