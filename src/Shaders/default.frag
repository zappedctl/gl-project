#version 330 core

in vec2 texCoord;
out vec4 fColor;

uniform sampler2D sampTexture;

void main()
{
  fColor = texture(sampTexture, texCoord);
}
