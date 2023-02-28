#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

layout(location = 1) in vec2 vPos;

void main()
{
	outColor = vec4(vPos, 1.0, 1.0);
}