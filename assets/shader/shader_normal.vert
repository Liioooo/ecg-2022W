#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT {
    vec3 normal;
} vsOut;

uniform mat4 model;
uniform mat4 view;


void main()
{
    vsOut.normal = normalize(mat3(transpose(inverse(view * model))) * aNormal);
    gl_Position = view * model * vec4(aPos, 1.0);
}