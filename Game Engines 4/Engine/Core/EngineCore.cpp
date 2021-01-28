#include "EngineCore.h"

std::unique_ptr<EngineCore> EngineCore::engineInstance = nullptr;

EngineCore::EngineCore()
{
	window = nullptr;
	isRunnig = false;
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
	window = new Window();
	if (window->OnCreate(name_, width_, height_) == false)
	{
		std::cout << "Failed to create window" << std::endl;
		OnDestroy();
		return false;
	}
	return isRunnig = true;
}

void EngineCore::Run()
{
	while (isRunnig)
	{
		Update(0.016f);
		Render();
	}
}

bool EngineCore::GetIsRunning()
{
	return isRunnig;
}

void EngineCore::Update(const float deltaTime_)
{
}

void EngineCore::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window->GetWindow());
}

void EngineCore::OnDestroy()
{
	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}