#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

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

  unsigned int vbo;
  unsigned int vao; // vertex array object
  unsigned int ebo; // element buffer object

  glGenVertexArrays(1, &vao);

  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao); // Se guardan las configuraciones que yo haga

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // 2.- Le decimos a OpenGL como tiene que interpretar la información
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  // 3.- Crear los shaders
  const char* vertexShaderSource = "#version 400 core\n"
                                   "layout (location = 1) in vec3 aPos;\n"
                                   "out float variable;\n"
                                   "uniform float mivariable2;\n"
                                   "void main()\n"
                                   "{\n"
                                   "variable = 0.0f;\n"
                                   "gl_Position = vec4(aPos.x + mivariable2, aPos.y, aPos.z, 1.0);\n"
                                   "}\n";

  const char* fragmentShaderSource = "#version 400 core\n"
                                     "out vec4 FragColor;\n"
                                     "in float variable;\n"
                                    "uniform float mivariable2;\n"
                                     "void main()\n"
                                     "{\n"
                                     "FragColor = vec4(mivariable2, 0.5f, 0.2f, 1.0f);\n"
                                     "}\n";

  unsigned int vertexShader;
  unsigned int fragmentShader;

  vertexShader   = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR:\n";
    std::cout << infoLog;
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR:\n";
    std::cout << infoLog;
  }

  // 4.- Crear el shader program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR LINKING\n";
    std::cout << infoLog;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glUseProgram(shaderProgram);
  int location = glGetUniformLocation(shaderProgram, "mivariable2");
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    glUniform1f(location, std::abs(std::sin(time)));

    glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteBuffers(1, &vbo);
  glDeleteProgram(shaderProgram);
  glDeleteVertexArrays(1, &vao);
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}