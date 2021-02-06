#include "Engine/Core/EngineCore.h"
#include "Game/Game1.h"
#include "Engine/Core/Debug.h"

int main(int argc, char* argv[])
{
	EngineCore::GetInstance()->SetGameInterface(new Game1);

	if (EngineCore::GetInstance()->OnCreate("Game 258 Engine", 800, 600) == false)
	{
		Debug::FatalError("Engine failed to initialize", __FILE__, __LINE__);
		return 0;
	}
	EngineCore::GetInstance()->Run();
	return 0;
}