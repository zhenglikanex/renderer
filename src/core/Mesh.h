#ifndef MESH_H_
#define MESH_H_

#include <vector>

#include "AuroraDef.h"

namespace aurora
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void AddSubMesh(const SubMeshPtr& submesh_ptr);
		const SubMeshPtr& GetSubMeshByIndex(size_t index) const;

		uint32_t GetSubMeshCount() const { return submeshs_.size(); }

		const std::vector<SubMeshPtr>& submeshs() const { return submeshs_; }
	private:
		std::vector<SubMeshPtr> submeshs_;
	};
}

#endif
