#include "mesh.h"

#include <stdlib.h>     
#include <time.h> 

#include <iostream>
#include<stdexcept>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace dragonbyte_engine
{

	const std::vector<vulkan::Vertex>& Mesh::vertices() const
	{
		return m_vertices;
	}
	const std::vector<vulkan::Index>& Mesh::indices() const
	{
		return m_indices;
	}
	std::vector<vulkan::Vertex>& Mesh::vertices()
	{
		return m_vertices;
	}
	std::vector<vulkan::Index>& Mesh::indices()
	{
		return m_indices;
	}

	Mesh::Mesh()
	{
		m_vertices = {  };
		m_indices = {  };
	}
	Mesh::~Mesh()
	{
		
	}

	void Mesh::set_mesh(const std::vector<vulkan::Vertex>& a_krVertices, const std::vector<vulkan::Index>& a_krIndices)
	{
		set_vertices(a_krVertices);
		set_indices(a_krIndices);
	}
	void Mesh::set_vertices(const std::vector<vulkan::Vertex>& a_krVertices)
	{
		vertices() = a_krVertices;
		change_vertices();
	}
	void Mesh::set_indices(const std::vector<vulkan::Index>& a_krIndices)
	{
		if (a_krIndices.size() % 3 != 0)
		{
			std::cout << "size of indices must be dividable by 3 at Mesh::set_indices\n";
			return;
		}
		indices() = a_krIndices;
		change_vertices();
	}
	void Mesh::add_vertex(vulkan::Vertex a_vertex)
	{
		vertices().push_back(a_vertex);
		change_vertices();
	}
	void Mesh::add_vertices(const std::vector<vulkan::Vertex>& a_krVertices)
	{
		vertices().insert(vertices().end(), a_krVertices.begin(), a_krVertices.end());
		change_vertices();
	}
	void Mesh::add_indices(const std::vector<vulkan::Index>& a_krIndices)
	{
		if (a_krIndices.size() % 3 != 0)
		{
			std::cout << "size of indices must be dividable by 3 at Mesh::set_indices\n";
			return;
		}
		indices().insert(indices().end(), a_krIndices.begin(), a_krIndices.end());
		change_vertices();
	}
	void Mesh::change_vertex(size_t a_index, vulkan::Vertex a_vertex)
	{
		if (a_index > vertices().size())
		{
			std::cout << "index is out of bounds at Mesh::change_vertex\n";
			return;
		}
		vertices().at(a_index) = a_vertex;
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

	Mesh& Mesh::operator=(Mesh& a_rOther)
	{
		set_vertices(a_rOther.vertices());
		set_indices(a_rOther.indices());
		return *this;
	}
	Mesh& Mesh::operator=(const Mesh& a_krOther)
	{
		set_vertices(a_krOther.vertices());
		set_indices(a_krOther.indices());
		return *this;
	}

	Mesh Mesh::load_mesh(std::string a_file)
	{
		// loading .obj file
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warnings, errors;

		std::cout << "Loading obj " << a_file << '\n';
		auto result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warnings, &errors, a_file.c_str());
		if (!result)
		{
			throw std::runtime_error("Failed to load obj:\n" + warnings + '\n' + errors);
		}

		Mesh mesh;
		std::vector<vulkan::Index> meshIndices;
		std::vector<vulkan::Vertex> meshVertices;

		// extracting indices
		for (const auto& shape : shapes)
		{
			meshIndices.resize(shape.mesh.indices.size());
			for (size_t i = 0; i < meshIndices.size(); i++)
			{
				meshIndices[i] = shape.mesh.indices[i].vertex_index;
			}
			mesh.add_indices(meshIndices);
		}
		
		// random colors
		srand(time(0));

		// extracting vertices
		meshVertices.resize(attrib.vertices.size() / 3);
		for (size_t i = 0; i < meshVertices.size(); i++)
		{
			meshVertices[i] = {
				attrib.vertices[i * 3 + 0],
				attrib.vertices[i * 3 + 1],
				attrib.vertices[i * 3 + 2],
				rand() % 255 / 255.f,
				rand() % 255 / 255.f,
				rand() % 255 / 255.f
			};
		}
		mesh.set_vertices(meshVertices);

		return mesh;
	}

} // namespace dragonbyte_engine