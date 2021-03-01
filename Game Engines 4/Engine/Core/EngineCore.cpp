#include "EngineCore.h"

std::unique_ptr<EngineCore> EngineCore::engineInstance = nullptr;

EngineCore::EngineCore()
{
	window = nullptr;
	isRunning = false;
	fps = 120;
	gameInterface = nullptr;
	currentSceneNum = 0;
}

EngineCore::~EngineCore()
{

}

EngineCore* EngineCore::GetInstance()
{
	if (engineInstance.get() == nullptr)
		engineInstance.reset(new EngineCore);

	return engineInstance.get();
}

bool EngineCore::OnCreate(std::string name_, int width_, int height_)
{
	Debug::OnCreate();
	window = new Window();
	if (window->OnCreate(name_, width_, height_) == false)
	{
		Debug::FatalError("Failed to create window", __FILE__, __LINE__);
		OnDestroy();
		return false;
	}

	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl", 
		"Engine/Shaders/ColourFragmentShader.glsl");

	if (gameInterface)
		if (gameInterface->OnCreate() == false)
		{
			Debug::FatalError("Game failed to initialize", __FILE__, __LINE__);
			OnDestroy();
			return isRunning = false;
		}

	Debug::Info("Working as intended", __FILE__, __LINE__);
	timer.Start();
	return isRunning = true;
}

void EngineCore::Run()
{
	while (isRunning)
	{
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
}

void EngineCore::Exit()
{
	isRunning = false;
}

bool EngineCore::GetIsRunning()
{
	return isRunning;
}

int EngineCore::GetCurrentScene() const
{
	return currentSceneNum;
}

float EngineCore::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float EngineCore::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* EngineCore::GetCamera() const
{
	return camera;
}

void EngineCore::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void EngineCore::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void EngineCore::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void EngineCore::Update(const float deltaTime_)
{
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
		std::cout << deltaTime_ << std::endl;
	}
}

void EngineCore::Render()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (gameInterface)
		gameInterface->Render();
	SDL_GL_SwapWindow(window->GetWindow());
}

void EngineCore::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
}