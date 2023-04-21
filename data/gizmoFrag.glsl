#version 330 core
in vec4 vert_color;
out vec4 fragColor;
void main()
{
    fragColor = vert_color; // Red color
}