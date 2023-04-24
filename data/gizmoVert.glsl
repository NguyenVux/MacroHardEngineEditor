#version 330 core
in float length;

out vec4 vert_color;

uniform vec4 axis[3];
uniform mat4 projectionMatrix;
void main()
{
    vec4 position = length*axis[gl_InstanceID];
    position.w = 1.0;
    gl_Position = projectionMatrix*mat4(1.0)*position;
    vert_color = axis[gl_InstanceID];
}