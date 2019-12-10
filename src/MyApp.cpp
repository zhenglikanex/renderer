#include "MyApp.h"
#include "Context.h"
#include "GameObjectFactory.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "Resources.h"
#include "DrawComponent.h"

MyApp::~MyApp()
{

}
bool MyApp::OnCreate()
{
	auto mesh = LoadMesh("model/mayaCube.obj");

	GameObjectPtr go = CREATE_GAMEOBJECT(GameObjectFactory::s_kMeshGameObject);
	auto mesh_renderer = go->GetComponent<MeshRenderer>();
	mesh_renderer->set_mesh(mesh);
	/*GameObjectPtr go = CREATE_GAMEOBJECT(GameObjectFactory::s_kNodeGameObject);
	go->AddComponent<DrawComponent>();*/

	Context::GetInstance()->scene_manager()->AddToRootNode(go);

	return true;
}
void MyApp::OnDestory()
{

}
void MyApp::OnUpdate()
{

}