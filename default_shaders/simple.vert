#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

/*
layout(binding = 0) uniform UniformBufferObject {
	mat4 model;
	mat4 view;
	mat4 proj;
} ubo;
*/

struct ObjectData {
	mat4 model;
	mat4 view;
	mat4 proj;
};

layout(std140, set = 0, binding = 0) readonly buffer ObjectBuffer {
	ObjectData objects[];
} objectBuffer;

void main()
{
	ObjectData mvp = objectBuffer.objects[0];
	gl_Position = mvp.proj * mvp.view * mvp.model * vec4(inPos, 1.0);
	fragColor = inColor;
}