#version 400 core

out vec4 FragColor;

in float variable;

uniform float mivariable2;

void main() { FragColor = vec4(mivariable2, 0.5f, 0.2f, 1.0f); }