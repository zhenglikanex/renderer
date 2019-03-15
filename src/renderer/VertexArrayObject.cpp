#include "VertexArrayObject.h"
#include "Renderer.h"
#include "RendererState.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"

namespace aurora
{
	VertexAttrib::VertexAttrib(VertexAttribFormat format, size_t offset)
		:format_(format)
		,offset_(offset)
	{
		index_ = AttribIndex(format_);
		component_num_ = AttribCompoentNum(format_);
		type_ = AttribType(format_);
		normalized_ = AttribNormalized(format_);
	}

	VertexArrayObject::VertexArrayObject(VertexType vertex_type, uint32_t vertex_count,const void* data)
		: use_index_(false)
		, vertex_buffer_(MakeVertexGpuBufferPtr(vertex_type,vertex_count,data))
		, update_attrib_(false)
	{
		CHECK_GL_ERROR(glGenVertexArrays(1, &id_));
	}

	VertexArrayObject::VertexArrayObject(VertexType vertex_type, uint32_t vertex_count,const void* vertex_data,IndexType index_type,uint32_t index_count,const void* index_data)
		: use_index_(true)
		, vertex_buffer_(MakeVertexGpuBufferPtr(vertex_type, vertex_count,vertex_data))
		, index_buffer_(MakeIndexGpuBufferPtr(index_type,index_count,index_data))
		, update_attrib_(false)
	{
		CHECK_GL_ERROR(glGenVertexArrays(1, &id_));
	}

	VertexArrayObject::~VertexArrayObject()
	{
		CHECK_GL_ERROR(glDeleteVertexArrays(1, &id_));
	}

	void VertexArrayObject::Bind()
	{
		renderer_->renderer_state()->BindVAO(id_);
	}

	void VertexArrayObject::UnBind()
	{
		renderer_->renderer_state()->BindVAO(0);
	}

	void VertexArrayObject::BindVertexAttrib(VertexAttribFormat format,size_t offset)
	{
		auto iter = attrib_map_.find(format);
		if (iter != attrib_map_.end())
		{
			return;
		}

		update_attrib_ = true;
		attrib_map_.insert(std::make_pair(format, VertexAttrib(format, offset)));
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
				auto attrib = entry.second;
			 	CHECK_GL_ERROR(glVertexAttribPointer(attrib.inex(), attrib.component_num(), attrib.type(), attrib.normalized(), vertex_buffer_->vertex_size(), (void*)attrib.offfset()));
			}

			update_attrib_ = false;
		}
	}
}

