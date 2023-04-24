#version 330 core
in float length;

out vec4 vert_color;

uniform mat4 projectionMatrix;
void main()
{
    float m = mod(gl_InstanceID,11);
    vec3 position = float(gl_InstanceID > 10)*length*vec3(0.0f,0.0f,1.0f) + float(gl_InstanceID < 11)*length*vec3(1.0f,0.0f,0.0f);
    vec3 offset = float(gl_InstanceID > 10)*2.0f*m*vec3(1.0f,0.0f,0.0f) + float(gl_InstanceID < 11)*2.0f*m*vec3(0.0f,0.0f,1.0f) ;
    gl_Position = projectionMatrix*mat4(1.0)*vec4(position+offset+vec3(-10.0f,0.0f,-10.0f),1.0f);
    vert_color = vec4(1.0f,1.0f,1.0f,1.0f);
}