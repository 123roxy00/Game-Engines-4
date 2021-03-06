#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "Window.h"
#include <memory>
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/SceneGraph.h"
#include "../Rendering/3D/GameObject.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Graphics//MaterialHandler.h"

#include "../Camera/Camera.h"

#include "../Events/EventListener.h"

class EngineCore
{
public:
	EngineCore(const EngineCore&) = delete;
	EngineCore(EngineCore&&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;
	EngineCore& operator=(EngineCore&&) = delete;

	static EngineCore* GetInstance();

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning();
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

	void NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_);
	void NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::ivec2 mouse_);
	void NotifyOfMouseScroll(int y_);

private:
	EngineCore();
	~EngineCore();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<EngineCore> engineInstance;
	friend std::default_delete<EngineCore>;

	Window* window;
	bool isRunning;

	Timer* timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};

#endif // !ENGINECORE_H