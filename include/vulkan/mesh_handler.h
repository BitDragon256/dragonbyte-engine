#pragma once

#include <vector>

#include "vertex.h"

namespace dragonbyte_engine
{

	class Mesh;

	namespace vulkan
	{

		struct MeshBufferData
		{
			MeshBufferData(uint32_t indexStart, uint32_t indexCount, uint32_t instanceStart, uint32_t instanceCount) :
				indexStart{ indexStart }, indexCount{ indexCount }, instanceStart{ instanceStart }, instanceCount{ instanceCount } {}

			uint32_t indexStart;
			uint32_t indexCount;
			uint32_t instanceStart;
			uint32_t instanceCount;
		};

		class MeshHandler
		{
		public:

			MeshHandler();
			~MeshHandler();

			void add_mesh(Mesh& mesh, uint32_t instanceCount);
			void draw_all_meshes();

		private:

			uint32_t m_totalInstances;

			std::vector<Mesh> m_meshes;
			std::vector<MeshBufferData> m_bufferData;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine