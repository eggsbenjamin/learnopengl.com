#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec4 xPosOffset;

void main()
{
    gl_Position = vec4(aPos.x + xPosOffset.x, aPos.y, aPos.z, 1.0);
}
