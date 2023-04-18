#version 330 core
in vec3 position;
uniform float z;
uniform mat4 projectionMatrix;
void main()
{
    vec3 pos = position - vec3(0,z,5);
    gl_Position = projectionMatrix*vec4(pos, 1.0);
}