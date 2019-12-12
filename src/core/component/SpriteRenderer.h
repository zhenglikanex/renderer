#pragma once

#include <string>

#include "AuroraDef.h"
#include "IComponent.h"

namespace aurora
{
	class SpriteRenderer : public IComponent
	{
	public:
		~SpriteRenderer();

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override;
		void Update() override;
		void Dispose() override;

		void LoadFile(const std::string& file_name);

		void set_texture(const Texture2DPtr& texture) { texture_ = texture; }
		const Texture2DPtr& texture() const { return texture_; }

		void set_material(const MaterialPtr& material) { material_ = material; }
		const MaterialPtr& material() const { return material_; }
	private:
		Texture2DPtr texture_;
		MaterialPtr material_;
	};
}