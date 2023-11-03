#version 400 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 vColor;
out vec2 vTexCoord;

uniform float mivariable2;

void main() {
  vColor = aColor;
  vTexCoord = aTexCoord;

  gl_Position = vec4(aPos.x + mivariable2 - 0.5, aPos.y + mivariable2 - 0.5, aPos.z, 1.0);
}