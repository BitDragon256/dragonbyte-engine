#include "vulkan/mesh_handler.h"

#include <vulkan/vulkan.h>

#include "vulkan/object_info.h"
#include "vulkan/command_buffer.h"

#include "mesh.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		MeshHandler::MeshHandler() : m_totalInstances{ 0 }  {}
		MeshHandler::~MeshHandler() {}

		void MeshHandler::add_mesh(Mesh& a_rMesh, uint32_t a_instanceCount)
		{
			m_meshes.push_back(a_rMesh);
			m_bufferData.push_back(
				{
					oi.pIndexBuffer->m_indices.size(),
					a_rMesh.indices().size(),
					m_totalInstances,
					a_instanceCount
				}
			);

			m_totalInstances += a_instanceCount;
			oi.pIndexBuffer->m_indices.insert(oi.pIndexBuffer->m_indices.end(), a_rMesh.indices().begin(), a_rMesh.indices().end());
			oi.pVertexBuffer->m_vertices.insert(oi.pVertexBuffer->m_vertices.end(), a_rMesh.vertices().begin(), a_rMesh.vertices().end());
		}
		void MeshHandler::draw_all_meshes()
		{
			for (size_t i = 0; i < m_meshes.size(); i++)
			{
				vkCmdDrawIndexed(
					vulkan::oi.pCommandBuffer->m_commandBuffer,
					m_bufferData[i].indexCount,
					m_bufferData[i].instanceCount,
					m_bufferData[i].indexStart,
					0,
					m_bufferData[i].instanceStart
				);
			}
		}

	} // namespace vulkan

} // namespace dragonbyte_engine