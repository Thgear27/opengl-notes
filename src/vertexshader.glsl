#version 400 core

layout(location = 0) in vec3 aPos;

out vec3 variable;

void main() {
  variable = vec3(1.0, 1.0, 1.0);
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}