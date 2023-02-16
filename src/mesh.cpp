#include "mesh.h"

#include <iostream>

namespace dragonbyte_engine
{

	const std::vector<vulkan::Vertex>& Mesh::vertices()
	{
		return m_vertices;
	}
	const std::vector<vulkan::Index>& Mesh::indices()
	{
		return m_indices;
	}

	Mesh::Mesh()
	{
	
	}

	void Mesh::set_mesh(const std::vector<vulkan::Vertex>& a_krVertices, const std::vector<vulkan::Index>& a_krIndices)
	{
		set_vertices(a_krVertices);
		set_indices(a_krIndices);
	}
	void Mesh::set_vertices(const std::vector<vulkan::Vertex>& a_krVertices)
	{
		m_vertices = a_krVertices;
		change_vertices();
	}
	void Mesh::set_indices(const std::vector<vulkan::Index>& a_krIndices)
	{
		if (a_krIndices.size() % 3 != 0)
		{
			std::cout << "size of indices must be dividable by 3 at Mesh::set_indices\n";
			return;
		}
		m_indices = a_krIndices;
		change_vertices();
	}
	void Mesh::add_vertex(vulkan::Vertex a_vertex)
	{
		m_vertices.push_back(a_vertex);
		change_vertices();
	}
	void Mesh::add_vertices(const std::vector<vulkan::Vertex>& a_krVertices)
	{
		m_vertices.insert(m_vertices.end(), a_krVertices.begin(), a_krVertices.end());
		change_vertices();
	}
	void Mesh::add_indices(const std::vector<vulkan::Index>& a_krIndices)
	{
		if (a_krIndices.size() % 3 != 0)
		{
			std::cout << "size of indices must be dividable by 3 at Mesh::set_indices\n";
			return;
		}
		m_indices.insert(m_indices.end(), a_krIndices.begin(), a_krIndices.end());
		change_vertices();
	}
	void Mesh::change_vertex(size_t a_index, vulkan::Vertex a_vertex)
	{
		if (a_index > m_vertices.size())
		{
			std::cout << "index is out of bounds at Mesh::change_vertex\n";
			return;
		}
		m_vertices[a_index] = a_vertex;
		change_vertices();
	}

	void Mesh::change_vertices()
	{
		vulkan::oi.pVertexBuffer->m_hasChanged = true;
	}
	void Mesh::change_indices()
	{
		vulkan::oi.pIndexBuffer->m_hasChanged = true;
	}

} // namespace dragonbyte_engine