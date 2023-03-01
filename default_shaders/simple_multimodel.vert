#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

struct ObjectData {
	mat4 model;
};

layout(std140, set = 0, binding = 0) readonly buffer ObjectBuffer {
	ObjectData objects[];
} objectBuffer;

layout(push_constant) uniform ViewProjectionData
{
	mat4 view;
	mat4 projection;
} viewProjectionData;

void main()
{
	ObjectData objectData = objectBuffer.objects[gl_InstanceIndex];
	gl_Position = viewProjectionData.projection * viewProjectionData.view * objectData.model * vec4(inPos, 1.0);
	// fragColor = vec3(objectData.model[0][0], objectData.model[1][1], objectData.model[2][2]);
	fragColor = inColor;
}