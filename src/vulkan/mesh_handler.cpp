#include "vulkan/mesh_handler.h"

#include <vulkan/vulkan.h>

#include "vulkan/object_info.h"
#include "vulkan/command_buffer.h"
#include "vulkan/index_buffer.h"
#include "vulkan/vertex_buffer.h"

#include "mesh.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		MeshHandler::MeshHandler() : m_totalInstances{ 0 }  {}
		MeshHandler::~MeshHandler() {}

		void MeshHandler::add_mesh(Mesh& a_rMesh, uint32_t a_instanceCount)
		{
			size_t i{ 0 };
			for (auto mesh : m_meshes)
			{
				if (*mesh == a_rMesh)
				{
					insert_existing_mesh(i, a_instanceCount);
					return;
				}
				i++;
			}
			insert_new_mesh(a_rMesh, a_instanceCount);
		}
		void MeshHandler::remove_mesh(Mesh& a_rMesh, uint32_t a_instanceCount)
		{
			for (auto it = m_meshes.begin(); it != m_meshes.end(); it++)
			{
				if (**it == a_rMesh)
				{
					size_t index = std::distance(m_meshes.begin(), it);
					if (m_bufferData[index].instanceCount > 1)
					{
						m_bufferData[index].instanceCount--;
					}
					else
					{
						m_bufferData.erase(m_bufferData.begin() + index);
						m_meshes.erase(it);
					}
					break;
				}
			}
		}
		void MeshHandler::insert_existing_mesh(size_t a_meshIndex, uint32_t a_instanceCount)
		{
			m_bufferData[a_meshIndex].instanceCount += a_instanceCount;
		}
		void MeshHandler::insert_new_mesh(Mesh& a_rMesh, uint32_t a_instanceCount)
		{
			m_meshes.push_back(&a_rMesh);
			m_bufferData.push_back(
				{
					static_cast<uint32_t>(oi.pIndexBuffer->m_bufferEnd),
					static_cast<uint32_t>(a_rMesh.indices().size()),
					m_totalInstances,
					a_instanceCount,
					static_cast<uint32_t>(oi.pVertexBuffer->m_bufferEnd)
				}
			);

			m_totalInstances += a_instanceCount;
			oi.pIndexBuffer->insert(a_rMesh.indices());
			oi.pVertexBuffer->insert(a_rMesh.vertices());
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
					m_bufferData[i].vertexStart,
					m_bufferData[i].instanceStart
				);
			}
		}

	} // namespace vulkan

} // namespace dragonbyte_engine