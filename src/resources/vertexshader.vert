#version 400 core

layout(location = 0) in vec3 aPos;

out float variable;

uniform float mivariable2;

void main() {
  variable    = 0.0f;
  gl_Position = vec4(aPos.x + mivariable2 - 0.5, aPos.y + mivariable2 - 0.5, aPos.z, 1.0);
}