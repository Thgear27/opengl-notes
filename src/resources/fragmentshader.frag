#version 400 core

out vec4 FragColor;

in vec3 vColor;
in vec2 vTexCoord;

uniform float mivariable2;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
  // FragColor = vec4(mivariable2, 0.5, 0.2, 1.0);
  FragColor = mix(texture(texture1, vTexCoord) * vec4(vColor, 1.0), texture(texture2, vTexCoord) * vec4(vColor, 1.0), mivariable2);
  // FragColor = texture(texture2, vTexCoord);
}