#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoord;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoord = aPos;
    vec4 pos = projection * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    gl_Position = pos.xyww;
}