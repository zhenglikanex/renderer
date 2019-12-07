#include "RenderCommand.h"

#include "Context.h"
#include "RenderSystem.h"


namespace aurora
{
	RenderCommand::RenderCommand(GLenum render_mode, const VertexArrayObjectPtr& vao, const MaterialPtr& material)
		: render_mode_(render_mode_)
		, vao_(vao)
		, material_(material)
	{
	}

	RenderCommand::~RenderCommand()
	{

	}

	void RenderCommand::Render()
	{
		BeginRender();

		Context::GetInstance()->render_system()->Render(material_, render_mode_, vao_, GetInstanceNum());

		EndRender();
	}
}