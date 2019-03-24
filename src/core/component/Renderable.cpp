#include "Renderable.h"

#include "RenderSystem.h"
#include "GpuBuffer.h"
#include "VertexArrayObject.h"
#include "GameObject.h"
#include "SceneNode.h"
#include "Context.h"
#include "Material.h"

#include "glm/glm.hpp"

namespace aurora
{
	Renderable::Renderable()
		:instance_buffer_(MakeGpuBufferPtr())
	{
		
	}

	Renderable::~Renderable()
	{

	}

	void Renderable::BeginRender()
	{
		GLsizeiptr size = instances_.size() * sizeof(glm::mat4);
		if (instance_buffer_ == nullptr)
		{
			instance_buffer_ = MakeGpuBufferPtr(GL_ARRAY_BUFFER, size, GL_DYNAMIC_DRAW);
		}
		else
		{
			instance_buffer_->Resize(size);
		}

		{
			
		}

		vao_->Bind();
	}

	void Renderable::Render()
	{
		BeginRender();

		Context::GetInstance()->render_system()->Render(material_,vao_);

		EndRender();
	}

	void Renderable::EndRender()
	{

	}

	void Renderable::ClearInstance()
	{
		
	}

	void Renderable::AddInstance(const GameObjectPtr& go)
	{
		instances_.push_back(go);

		
	}

	void Renderable::GetInstanceNum()
	{

	}
}