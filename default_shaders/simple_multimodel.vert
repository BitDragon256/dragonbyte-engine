#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

struct MVP
{
	mat4 model;
	mat4 view;
	mat4 proj;
};

layout(std140, set = 0, binding = 0) readonly buffer MVPBuffer {
	MVP mvps[];
} mvpBuffer;

void main()
{
	MVP mvp = mvpBuffer.mvps[0];
	gl_Position = mvp.proj * mvp.view * mvp.model * vec4(inPos, 1.0);
	fragColor = inColor;
}