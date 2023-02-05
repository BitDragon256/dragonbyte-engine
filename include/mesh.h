#pragma once

#include <vector>

#include "vulkan/vertex.h"

#include "vulkan/vertex_buffer.h"
#include "vulkan/index_buffer.h"

namespace dragonbyte_engine
{

	class Mesh
	{
	public:

		const std::vector<vulkan::Vertex>& vertices();
		const std::vector<vulkan::Index>& indices();

		void set_mesh(const std::vector<vulkan::Vertex>& vertices, const std::vector<vulkan::Index>& indices);
		void set_vertices(const std::vector<vulkan::Vertex>& vertices);
		void set_indices(const std::vector<vulkan::Index>& indices);

		void add_vertex(vulkan::Vertex vertex);
		void add_vertices(const std::vector<vulkan::Vertex>& vertices);

		void add_indices(const std::vector<vulkan::Index>& indices);

		void change_vertex(size_t index, vulkan::Vertex vertex);

	private:

		std::vector<vulkan::Vertex> m_vertices;
		std::vector<vulkan::Index> m_indices;

		vulkan::VertexBuffer& m_rVertexBuffer;
		vulkan::IndexBuffer& m_rIndexBuffer;

		void change_vertices();
		void change_indices();

	};

} // namespace dragonbyte_engine