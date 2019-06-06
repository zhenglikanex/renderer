#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

#include "AuroraDef.h"
#include "IComponent.h"

namespace aurora
{
	// äÖÈ¾×é¼þ
	class MeshRenderer : public IComponent
	{
	public:
		virtual ~MeshRenderer() = 0;

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override;
		void Update() override;
		void Dispose() override;

		void set_mesh(const MeshPtr& mesh) { mesh_ = mesh; }
		const MeshPtr& mesh() const { return mesh_; }

	private:
		MeshPtr mesh_;
		std::vector<MaterialPtr> materials_;
	};
}

#endif
