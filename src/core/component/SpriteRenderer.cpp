#include "SpriteRenderer.h"
#include "Resources.h"

namespace aurora
{
	SpriteRenderer::~SpriteRenderer()
	{

	}

	IComponentPtr SpriteRenderer::Clone()
	{
		return MakeSpriteRendererPtr();
	}

	void SpriteRenderer::Copy(const IComponentPtr& component)
	{
		
	}

	void SpriteRenderer::Start()
	{

	}

	void SpriteRenderer::Update()
	{

	}

	void SpriteRenderer::Dispose()
	{

	}

	void SpriteRenderer::LoadFile(const std::string& file_name)
	{
		texture_ = LoadTexture2D(file_name);
	}
}