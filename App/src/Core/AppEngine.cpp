#include "AppEngine.h"

#include "Engine/ECS/System/SystemBuilder.h"

// Custom app systems
#include "Gameplay/ChangeStateSystem.h"
#include "Gameplay/ChangeSceneSystem.h"

// Here we use to include all we need for this specific app details to work
namespace MyEngine
{
	void Application::Init()
	{
		Engine::Init();

		// TODO: Come from scene config
		// TODO: Could this be categorized to avoid having to put all in the config?

		// Custom app systems
		SystemBuilder::RegisterSystem("ChangeStateSystem", []() { return new ChangeStateSystem; });
		SystemBuilder::RegisterSystem("ChangeSceneSystem", []() { return new ChangeSceneSystem; });
	}
}
