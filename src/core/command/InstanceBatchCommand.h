#ifndef INSTANCEBATCH_COMMAND_H_
#define INSTANCEBATCH_COMMAND_H_

#include <vector>

#include "AuroraDef.h"
#include "RenderCommand.h"
#include "GameObject.h"

namespace aurora
{
	class InstanceBatchCommand : public RenderCommand
	{
	public:
		InstanceBatchCommand(GLenum render_mode, const VertexArrayObjectPtr& vao, const MaterialPtr& material);

		RenderCommandType type() const override { return RenderCommandType::kInstance; }

		void BeginRender() override;
		void EndRender() override;
	private:
		void SetupInstanceStream();
		void SetupShaderUniform();
	};
}

#endif