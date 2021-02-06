#include "Game1.h"

Game1::Game1() : GameInterface()
{
	currentSceneNum = 0;
	currentScene = nullptr;
}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	if (EngineCore::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::Error("Engine's scene is not initialized to 0", __FILE__, __LINE__);
	return false;
}

void Game1::Update(const float deltaTime_)
{
	if (currentSceneNum != EngineCore::GetInstance()->GetCurrentScene())
		BuildScene();
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (EngineCore::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = EngineCore::GetInstance()->GetCurrentScene();
	if (currentScene->OnCreate() == false)
	{
		Debug::Error("Scene failed to be created", __FILE__, __LINE__);
		EngineCore::GetInstance()->Exit();
	}
}