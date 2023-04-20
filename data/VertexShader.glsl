#version 330 core
in vec3 position;
uniform float z;
uniform mat4 projectionMatrix;
uniform mat4 ModelMatrix;
void main()
{
    gl_Position = projectionMatrix*ModelMatrix*vec4(position, 1.0);
}