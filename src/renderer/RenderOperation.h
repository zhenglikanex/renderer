#ifndef RENDER_OPERATION_H_
#define RENDER_OPERATION_H_

#include "AuroraDef.h"
#include "glSupport.h"
namespace aurora
{
	struct RenderOperation
	{
		GLenum render_type;
		VertexArrayObjectPtr vao;
	};
}

#endif
