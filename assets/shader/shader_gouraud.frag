#version 430 core
in vec3 vFragColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vFragColor, 1.0f);
}