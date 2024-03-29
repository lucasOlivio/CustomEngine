#include "EditorEngine.h"

#include "Engine/ECS/System/SystemBuilder.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

// Custom gameplay systems
#include "Gameplay/PlayerControllerSystem.h"

#include "UI/MenuSystem.h"
#include "UI/EntityBarSystem.h"
#include "UI/GuizmoSystem.h"

// Here we use to include all we need for this specific app details to work
namespace MyEngine
{
	Editor::Editor()
	{
		Init();
	}

	Editor::~Editor()
	{
		Shutdown();
	}
	// TODO: For now duplicated from App we just need editor to create the scenes,
	// but later this should all come separated from config and better system management
	void Editor::Init()
	{
		Engine::Init();

		// Register custom app systems
		// SystemBuilder::RegisterSystem("ExampleCustomSystem", []() { return new ExampleCustomSystem; });
		SystemBuilder::RegisterSystem("MenuSystem", []() { return new MenuSystem; });
		SystemBuilder::RegisterSystem("EntityBarSystem", []() { return new EntityBarSystem; });
		SystemBuilder::RegisterSystem("GuizmoSystem", []() { return new GuizmoSystem; });
		
		// SystemBuilder::RegisterSystem("ExampleCustomSystem", []() { return new ExampleCustomSystem; });
		SystemBuilder::RegisterSystem("PlayerControllerSystem", []() { return new PlayerControllerSystem; });

		GameStateComponent* pStates = CoreLocator::GetGameState();

		pStates->mainSystems.push_back("WindowFrameSystem");
		pStates->mainSystems.push_back("FrameBufferSystem");
		pStates->mainSystems.push_back("TransformParentSystem");
		pStates->mainSystems.push_back("WindowSystem");
		pStates->mainSystems.push_back("InputSystem");
		pStates->mainSystems.push_back("BaseUISystem"); // Has to come after inputsystem, to init imgui after we register our input callback
		// Graphics
		pStates->mainSystems.push_back("ShaderSystem");
		pStates->mainSystems.push_back("ModelRenderSystem");
		pStates->mainSystems.push_back("RenderSystem");
		pStates->mainSystems.push_back("LightSystem");
		pStates->mainSystems.push_back("LightFlickerSystem");
		pStates->mainSystems.push_back("MaterialOffsetSystem");
		pStates->mainSystems.push_back("AnimationSystem");

		pStates->mainSystems.push_back("MenuSystem");
		pStates->mainSystems.push_back("EntityBarSystem");
		pStates->mainSystems.push_back("GuizmoSystem");
		pStates->mainSystems.push_back("FlyingCameraSystem");

		// TODO: This could come from a config file
		// TODO: Could this be categorized to avoid having to put all in the config?
		pStates->mapStateSystems[eGameStates::NOT_STARTED] = {};

		pStates->mapStateSystems[eGameStates::STARTED] = {};

		pStates->mapStateSystems[eGameStates::RUNNING] = {
			// Graphics
			"AnimationPlayerSystem",
			// Physics
			"MovementSystem",
			"RotationSystem",
			"GravitySystem",
			"GridBroadPhaseSystem",
			"CollisionSystem",
			"SoftBodyUpdateSystem",
			"SoftBodyResponseSystem",
			"SotBodyConstraintsSystem",
			// Gameplay
			"PlayerControllerSystem",
			"SteeringBehaviorSystem"

			// Debug
			,"DebugSystem",
			"DrawGridSystem",
			"DrawCollisionSystem",
			"DrawSoftBodyPartclesSystem"

		};

		pStates->mapStateSystems[eGameStates::STOPPED] = {};

		pStates->mapStateSystems[eGameStates::GAMEOVER] = {};
	}
}
