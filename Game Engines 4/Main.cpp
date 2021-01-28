#include "Engine/Core/EngineCore.h"

int main(int argc, char* argv[])
{
	if (EngineCore::GetInstance()->OnCreate("Game 258 Engine", 800, 600) == false)
	{
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}
	EngineCore::GetInstance()->Run();
	return 0;
}