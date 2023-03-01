#pragma once

#include <string>
#include <vector>

#include "component.h"

#include "vulkan/vertex.h"

#include "vulkan/vertex_buffer.h"
#include "vulkan/index_buffer.h"

namespace dragonbyte_engine
{

	class Mesh : public Component
	{
	public:

		/* -------------------------------
		*			Mesh Declaration
		*  -------------------------------
		*/

		Mesh();
		~Mesh();

		const std::vector<vulkan::Vertex>& vertices() const;
		const std::vector<vulkan::Index>& indices() const;
		uint32_t m_id; 

		std::vector<vulkan::Vertex>& vertices();
		std::vector<vulkan::Index>& indices();

		void set_mesh(const std::vector<vulkan::Vertex>& vertices, const std::vector<vulkan::Index>& indices);
		void set_vertices(const std::vector<vulkan::Vertex>& vertices);
		void set_indices(const std::vector<vulkan::Index>& indices);

		void add_vertex(vulkan::Vertex vertex);
		void add_vertices(const std::vector<vulkan::Vertex>& vertices);

		void add_indices(const std::vector<vulkan::Index>& indices);

		void change_vertex(size_t index, vulkan::Vertex vertex);

		Mesh& operator=(Mesh& other);
		Mesh& operator=(const Mesh& other);
		bool operator==(const Mesh& other);

		/* --------------------------------
		*			Load Meshes
		*  --------------------------------
		*/

		static Mesh load_mesh(std::string file);

	private:

		std::vector<vulkan::Index> m_indices;
		std::vector<vulkan::Vertex> m_vertices;

		void change_vertices();
		void change_indices();
		void change_id();

		static uint32_t hash_mesh(const std::vector<vulkan::Index>& krIndices, const std::vector<vulkan::Vertex>& krVertices);

	};

} // namespace dragonbyte_engine