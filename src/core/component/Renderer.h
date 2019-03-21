#ifndef RENDERER_H_
#define RENDERER_H_

#include "IComponent.h"

namespace aurora
{
	// äÖÈ¾×é¼þ
	class Renderer : public IComponent
	{
	public:
		virtual ~Renderer() = 0;

		IComponentPtr Clone() override;
		void Copy(const IComponentPtr& component) override;

		void Start() override;
		void Update() override;
		void Dispose() override;
	private:

	};
}

#endif
