#version 330 core
in vec3 position;
out vec4 vert_color;
uniform vec4 uvert_c;
uniform mat4 projectionMatrix;
void main()
{
    gl_Position = projectionMatrix*mat4(1.0)*vec4(position, 1.0);
    vert_color = uvert_c;
}