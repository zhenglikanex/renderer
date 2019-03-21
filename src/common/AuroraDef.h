#ifndef AURORA_DEF_H_
#define AURORA_DEF_H_

#include <iostream>
#include <memory>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdint>

#ifndef AURORA_ASSERT
#include <assert.h>
#define AURORA_ASSERT(x) assert(x)
#endif

#include "LogManager.h"

#define MAKE_SHARED_PTR(class_name) \
template<typename ... Args> \
class_name##Ptr Make##class_name##Ptr(Args&& ... args) \
{	\
	return std::make_shared<class_name##>(std::forward<Args>(args)...); \
}

namespace aurora
{
	class Window;
	using WindowPtr = std::shared_ptr<Window>;

	class GLFW3Window;
	using GLFW3WindowPtr = std::shared_ptr<GLFW3Window>;
	MAKE_SHARED_PTR(GLFW3Window);

	class RenderSystem;
	using RenderSystemPtr = std::shared_ptr<RenderSystem>;
	MAKE_SHARED_PTR(RenderSystem);

	class DeviceContext;
	using DeviceContextPtr = std::shared_ptr<DeviceContext>;
	MAKE_SHARED_PTR(DeviceContext);

	class RenderState;
	using RenderStatePtr = std::shared_ptr<RenderState>;
	MAKE_SHARED_PTR(RenderState);

	class Context;
	using ContextPtr = std::shared_ptr<Context>;
	MAKE_SHARED_PTR(Context);

	class GpuBuffer;
	using GpuBufferPtr = std::shared_ptr<GpuBuffer>;
	MAKE_SHARED_PTR(GpuBuffer);

	class VertexGpuBuffer;
	using VertexGpuBufferPtr = std::shared_ptr<VertexGpuBuffer>;
	MAKE_SHARED_PTR(VertexGpuBuffer);

	class IndexGpuBuffer;
	using IndexGpuBufferPtr = std::shared_ptr<IndexGpuBuffer>;
	MAKE_SHARED_PTR(IndexGpuBuffer);
	
	class VertexAttrib;
	using VertexAttribPtr = std::shared_ptr<VertexAttrib>;
	MAKE_SHARED_PTR(VertexAttrib);

	class VertexArrayObject;
	using VertexArrayObjectPtr = std::shared_ptr<VertexArrayObject>;
	MAKE_SHARED_PTR(VertexArrayObject);

	class Mesh;
	using MeshPtr = std::shared_ptr<Mesh>;
	using MeshWeakPtr = std::weak_ptr<Mesh>;
	MAKE_SHARED_PTR(Mesh);

	class SubMesh;
	using SubMeshPtr = std::shared_ptr<SubMesh>;
	using SubMeshWeakPtr = std::weak_ptr<SubMesh>;
	MAKE_SHARED_PTR(SubMesh);

	class Image;
	using ImagePtr = std::shared_ptr<Image>;
	MAKE_SHARED_PTR(Image);

	class Texture;
	using TexturePtr = std::shared_ptr<Texture>;
	MAKE_SHARED_PTR(Texture);

	class Texture2D;
	using Texture2DPtr = std::shared_ptr<Texture2D>;
	MAKE_SHARED_PTR(Texture2D);

	class TextureCube;
	using TextureCubePtr = std::shared_ptr<TextureCube>;
	MAKE_SHARED_PTR(TextureCube);

	class Material;
	using MaterialPtr = std::shared_ptr<Material>;
	MAKE_SHARED_PTR(Material);

	class Shader;
	using ShaderPtr = std::shared_ptr<Shader>;
	MAKE_SHARED_PTR(Shader);

	class FrameBufferAttachment;
	using FrameBufferAttachmentPtr = std::shared_ptr<FrameBufferAttachment>;
	MAKE_SHARED_PTR(FrameBufferAttachment);

	class TextureBufferAttachment;
	using TextureBufferAttachmentPtr = std::shared_ptr<TextureBufferAttachment>;
	MAKE_SHARED_PTR(TextureBufferAttachment);

	class RenderBufferAttachment;
	using RenderBufferAttachmentPtr = std::shared_ptr<RenderBufferAttachment>;
	MAKE_SHARED_PTR(RenderBufferAttachment);

	class FrameBufferObject;
	using FrameBufferObjectPtr = std::shared_ptr<FrameBufferObject>;
	MAKE_SHARED_PTR(FrameBufferObject);

	class BaseRenderTexture;
	using BaseRenderTexturePtr = std::shared_ptr<BaseRenderTexture>;
	MAKE_SHARED_PTR(BaseRenderTexture);

	class RenderTexture;
	using RenderTexturePtr = std::shared_ptr<RenderTexture>;
	MAKE_SHARED_PTR(RenderTexture);

	class RenderTextureCube;
	using RenderTextureCubePtr = std::shared_ptr<RenderTextureCube>;
	MAKE_SHARED_PTR(RenderTextureCube);

	class IComponent;
	using IComponentPtr = std::shared_ptr<IComponent>;
	MAKE_SHARED_PTR(IComponent);

	class SceneManager;
	using SceneManagerPtr = std::shared_ptr<SceneManager>;
	MAKE_SHARED_PTR(SceneManager);

	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	using GameObjectWeakPtr = std::weak_ptr<GameObject>;
	MAKE_SHARED_PTR(GameObject);

	class SceneNode;
	using SceneNodePtr = std::shared_ptr<SceneNode>;
	using SceneNodeWeakPtr = std::weak_ptr<SceneNode>;
	MAKE_SHARED_PTR(SceneNode);

	class MeshRenderer;
	using MeshRendererPtr = std::shared_ptr<MeshRenderer>;
	using MeshRendererWeakPtr = std::weak_ptr<MeshRenderer>;
	MAKE_SHARED_PTR(MeshRenderer);

	class Camera;
	using CameraPtr = std::shared_ptr<Camera>;
	using CameraWeakPtr = std::weak_ptr<Camera>;
	MAKE_SHARED_PTR(Camera);

	class Light;
	using LightPtr = std::shared_ptr<Light>;
	using LightWeakPtr = std::weak_ptr<Light>;
	MAKE_SHARED_PTR(Light);

	class PointLight;
	using PointLightPtr = std::shared_ptr<PointLight>;
	using PointLightWeakPtr = std::weak_ptr<PointLight>;
	MAKE_SHARED_PTR(PointLight);

	class DirectionalLight;
	using DirectionalLightPtr = std::shared_ptr<DirectionalLight>;
	using DirectionalLightWeakPtr = std::weak_ptr<DirectionalLight>;
	MAKE_SHARED_PTR(DirectionalLight);

	class Plane;
	using PlanePtr = std::shared_ptr<Plane>;
	using PlaneWeakPtr = std::weak_ptr<Plane>;
	MAKE_SHARED_PTR(Plane);
}

#endif
