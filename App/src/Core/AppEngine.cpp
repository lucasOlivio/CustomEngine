#include "AppEngine.h"

#include "Engine/ECS/System/SystemBuilder.h"

// Custom app systems
#include "Gameplay/ChangeStateSystem.h"
#include "Gameplay/ChangeSceneSystem.h"

// Here we use to include all we need for this specific app details to work
namespace MyEngine
{
	void Application::Init(std::string initialSceneName)
	{
		// TODO: Come from scene config
		// TODO: Could this be categorized to avoid having to put all in the config?
		Engine::AddSystem(SystemBuilder::CreateSystem("WindowFrameSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("TransformParentSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("WindowSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("InputSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("ShaderSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("CameraSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("RenderSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("LightSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("MovementSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("RotationSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("GravitySystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("RegisterCollisionSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("GridBroadPhaseSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("CollisionSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("DebugSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("DrawGridSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("DrawCollisionSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("StateSystem"));

		// Custom app systems
		SystemBuilder::RegisterSystem("ChangeStateSystem", []() { return new ChangeStateSystem; });
		Engine::AddSystem(SystemBuilder::CreateSystem("ChangeStateSystem"));
		SystemBuilder::RegisterSystem("ChangeSceneSystem", []() { return new ChangeSceneSystem; });
		Engine::AddSystem(SystemBuilder::CreateSystem("ChangeSceneSystem"));

		Engine::Init(initialSceneName);
	}
}
