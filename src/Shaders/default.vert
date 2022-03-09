#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;
uniform mat4 mTransform;
uniform mat4 vTransform;

void main()
{
  gl_Position = mTransform * vTransform * vec4(aPos, 1.0f);
  texCoord = aTexCoord;
}
