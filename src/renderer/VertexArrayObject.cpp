#include "VertexArrayObject.h"
#include "Renderer.h"
#include "RendererState.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"

namespace aurora
{
	VertexArrayObject::VertexArrayObject(uint32_t vertex_size,uint32_t vertex_count,const void* data)
		: use_index_(false)
		, vertex_buffer_(MakeVertexGpuBufferPtr(vertex_size,vertex_count,data))
		, update_attrib_(false)
	{
		glGenVertexArrays(1, &id_);
	}

	VertexArrayObject::VertexArrayObject(uint32_t vertex_size, uint32_t vertex_count,const void* vertex_data,uint32_t index_size,uint32_t index_count,const void* index_data)
		: use_index_(true)
		, vertex_buffer_(MakeVertexGpuBufferPtr(vertex_size, vertex_count,vertex_data))
		, index_buffer_(MakeIndexGpuBufferPtr(index_size,index_count,index_data))
		, update_attrib_(false)
	{
		glGenVertexArrays(1, &id_);
	}

	VertexArrayObject::~VertexArrayObject()
	{

	}

	void VertexArrayObject::Bind()
	{
		renderer_->renderer_state()->BindVAO(id_);
	}

	void VertexArrayObject::UnBind()
	{
		renderer_->renderer_state()->BindVAO(0);
	}

	void VertexArrayObject::BindVertexAttrib(const VertexAttrib& attrib)
	{
		auto iter = attrib_map_.find(attrib.format);
		if (iter != attrib_map_.end())
		{
			return;
		}
		attrib_map_.insert(std::make_pair(attrib.format, attrib));
		update_attrib_ = true;
	}

	void VertexArrayObject::UpdateVertexAttrib()
	{
		if (update_attrib_)
		{
			Bind();
			
			vertex_buffer_->Bind();
			if (use_index_) index_buffer_->Bind();

			for (auto & entry : attrib_map_)
			{
				VertexAttribFormat format = entry.second.format;
				glVertexAttribPointer()
			}
		}
	}
}

