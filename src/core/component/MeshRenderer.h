#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>
#include <unordered_map>

#include "AuroraDef.h"
#include "IComponent.h"

namespace aurora
{
	// äÖÈ¾×é¼þ
	class MeshRenderer : public IComponent
	{
	public:
		MeshRenderer(){}
		virtual ~MeshRenderer();

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override;
		void Update() override;
		void Dispose() override;

		void set_mesh(const MeshPtr& mesh) 
		{
			mesh_ = mesh; 
			ResetMaterial();
		}
		const MeshPtr& mesh() const { return mesh_; }

		uint32_t GetSubMeshCount() const;
		
		MaterialPtr GetMaterialByIndex(uint32_t index) const;
		void AddMaterial(uint32_t index, const MaterialPtr& material);
		void RemoveMaterial(uint32_t index);
		void ResetMaterial();
	private:
		MeshPtr mesh_;
		std::unordered_map<uint32_t, MaterialPtr> material_map_;

		bool instanced_;
	};
}

#endif
