#ifndef ENGINECORE_H
#define ENGINECORE_H

#include "Window.h"
#include <memory>

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
	bool GetIsRunning();

private:
	EngineCore();
	~EngineCore();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<EngineCore> engineInstance;
	friend std::default_delete<EngineCore>;

	Window* window;
	bool isRunnig;
};

#endif // !ENGINECORE_H