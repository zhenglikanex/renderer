#include "VertexArrayObject.h"
#include "RenderSystem.h"
#include "RenderState.h"
#include "VertexGpuBuffer.h"
#include "IndexGpuBuffer.h"
#include "Context.h"

namespace aurora
{
	VertexArrayObject::VertexArrayObject()
		:need_update_vertex_stream_(false)
	{
		renderer_ = Context::GetInstance()->render_system();
		glGenVertexArrays(1, &id_);
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

	void VertexArrayObject::UpdateVaoToShader()
	{
		Bind();

		if (need_update_vertex_stream_)
		{
			CHECK_GL_ERROR(int a = 1);

			if (vertex_stream_.attribs.size() > 0 && vertex_stream_.vertex_buffer)
			{
				vertex_stream_.vertex_buffer->Bind();

				for (auto attrib : vertex_stream_.attribs)
				{
					CHECK_GL_ERROR(glEnableVertexAttribArray(attrib.index));
					CHECK_GL_ERROR(glVertexAttribPointer(attrib.index, attrib.component_num, attrib.type, attrib.normalized,vertex_stream_.vertex_buffer->vertex_size(),(void*)attrib.offset));
				}
			}

			if (instance_stream_.attribs.size() > 0 && instance_stream_.instance_buffer)
			{
				instance_stream_.instance_buffer->Bind();
				for (auto attrib : instance_stream_.attribs)
				{
					CHECK_GL_ERROR(glVertexAttribPointer(attrib.index, attrib.component_num, attrib.type, attrib.normalized, instance_stream_.size, (void*)attrib.offset));
					CHECK_GL_ERROR(glEnableVertexAttribArray(attrib.index));
					CHECK_GL_ERROR(glVertexAttribDivisor(attrib.index, 1));
				}
			}

			if (index_buffer_)
			{
				index_buffer_->Bind();
			}

			need_update_vertex_stream_ = false;
		}
	}
}

