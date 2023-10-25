#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "OpenGL/ElementBuffer.hpp"
#include "OpenGL/ShaderProgram.hpp"
#include "OpenGL/VertexArray.hpp"
#include "OpenGL/VertexBuffer.hpp"

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
    0.5f,  0.5f,  0.0f, // top right
    0.5f,  -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f  // top left
  };

  unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  VertexArray vao; // vertex array object
  VertexBuffer vbo;
  ElementBuffer ebo;

  vbo.loadData(sizeof(vertices), vertices, GL_STATIC_DRAW);
  vbo.pushVertexAttribLayout(3, GL_FLOAT, GL_FALSE);

  ebo.loadData(sizeof(indices), indices, GL_STATIC_DRAW);
  vao.addeElementBuffer(&ebo);
  vao.addVertexBuffer(&vbo);
  vao.linkBuffers();

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  shaderProgram.use();
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