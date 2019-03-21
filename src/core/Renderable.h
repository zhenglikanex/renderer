#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "AuroraDef.h"

namespace aurora
{
	class Renderable
	{
	public:
		Renderable();
		virtual ~Renderable();

		void ClearInstance();
		void AddInstance(const GameObjectPtr& go);
		void GetInstanceNum();

		// œÚRenderSystemÃ·Ωª‰÷»æ
		virtual void Render();
	private:
		std::vector<GameObjectPtr> instances_;
		
	};
}

#endif
