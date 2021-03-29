#include "GameScene.h"

GameScene::GameScene() :shape(nullptr)
{
}

GameScene::~GameScene()
{
	model = nullptr;
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Game scene", __FILE__, __LINE__);

	EngineCore::GetInstance()->SetCamera(new Camera());
	EngineCore::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	EngineCore::GetInstance()->GetCamera()->AddLightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	model = new Model("Resources/Models/Apple.obj",
		"Resources/Materials/Apple.mtl",
		ShaderHandler::GetInstance()->GetShader("basicShader"));
	//model->SetScale(glm::vec3(0.75f));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(EngineCore::GetInstance()->GetCamera());
}
