#include "EditorEngine.h"

#include "Engine/ECS/System/SystemBuilder.h"

// Custom editor systems
#include "UI/MenuSystem.h"

// Here we use to include all we need for this specific app details to work
namespace MyEngine
{
	// TODO: For now duplicated from App we just need editor to create the scenes,
	// but later this should all come separated from config and better system management
	void Editor::Init(std::string initialSceneName)
	{
		// TODO: Come from scene config
		// TODO: Could this be categorized to avoid having to put all in the config?
		// 
		// Core
		Engine::AddSystem(SystemBuilder::CreateSystem("WindowFrameSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("TransformParentSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("WindowSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("InputSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("BaseUISystem")); // Has to come after inputsystem, to init imgui after we register our input callbacks
		Engine::AddSystem(SystemBuilder::CreateSystem("StateSystem"));
		// Graphics
		Engine::AddSystem(SystemBuilder::CreateSystem("ShaderSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("CameraSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("RenderSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("LightSystem"));
		// Physics
		Engine::AddSystem(SystemBuilder::CreateSystem("MovementSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("RotationSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("GravitySystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("RegisterCollisionSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("GridBroadPhaseSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("CollisionSystem"));
		// DEBUG
#ifdef DEBUG
		Engine::AddSystem(SystemBuilder::CreateSystem("DebugSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("DrawGridSystem"));
		Engine::AddSystem(SystemBuilder::CreateSystem("DrawCollisionSystem"));
#endif

		// Custom app systems
		SystemBuilder::RegisterSystem("MenuSystem", []() { return new MenuSystem; });
		Engine::AddSystem(SystemBuilder::CreateSystem("MenuSystem"));

		Engine::Init(initialSceneName);
	}
}
