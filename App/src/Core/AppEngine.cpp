#include "AppEngine.h"
#include "Engine/Graphics/Shaders/ShaderSystem.h"
#include "Engine/Graphics/CameraSystem.h"
#include "Engine/Graphics/WindowSystem.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/Lights/LightSystem.h"
#include "Engine/Physics/MovementSystem.h"
#include "Engine/Physics/GravitySystem.h"
#include "Engine/Physics/BroadPhase/GridBroadPhaseSystem.h"
#include "Engine/Physics/NarrowPhase/CollisionSystem.h"
#include "Engine/Debug/DebugSystem.h"
#include "Engine/Debug/WindowFPSSystem.h"
#include "Engine/Debug/DrawGridSystem.h"
#include "Engine/Debug/DrawCollisionSystem.h"
#include "Engine/ECS/SceneSerializerFactory.h"
#include "Engine/ECS/SingletonComponents/ConfigPathLocator.h"

// Here we use to include all we need for this specific app details to work
namespace MyEngine
{
	// TODO: This should be in a separated config file maybe?
	const std::string SCENE_PATH = "assets/scenes/scene01.json";

	void Application::Init()
	{
		// Loading scene from file
		iSceneSerializer* pSceneSerializer = SceneSerializerFactory::CreateSceneSerializer(SCENE_PATH);
		pSceneSerializer->DeserializeScene(SCENE_PATH, *m_pScene);

		// Graphics systems
		ShaderSystem* pShaderSys = new ShaderSystem();
		WindowSystem* pWindowSys = new WindowSystem();
		CameraSystem* pCameraSys = new CameraSystem();
		RenderSystem* pRenderSys = new RenderSystem();
		LightSystem* pLightSys = new LightSystem();

		Engine::AddSystem(pWindowSys);
		Engine::AddSystem(pShaderSys);
		Engine::AddSystem(pCameraSys);
		Engine::AddSystem(pRenderSys);
		Engine::AddSystem(pLightSys);

		// Physics systems
		GravitySystem* pGravitySys = new GravitySystem();
		MovementSystem* pMovementSys = new MovementSystem();
		GridBroadPhaseSystem* pGridBroadPhaseSys = new GridBroadPhaseSystem();
		CollisionSystem* pCollisionSys = new CollisionSystem();

		Engine::AddSystem(pGravitySys);
		Engine::AddSystem(pMovementSys);
		Engine::AddSystem(pGridBroadPhaseSys);
		Engine::AddSystem(pCollisionSys);

		// Debug systems
		DebugSystem* pDebugSys = new DebugSystem();
		WindowFPSSystem* pWindowFPSSys = new WindowFPSSystem();
		DrawGridSystem* pDrawGridSys = new DrawGridSystem();
		DrawCollisionSystem* pDrawCollisionSys = new DrawCollisionSystem();

		Engine::AddSystem(pDebugSys);
		Engine::AddSystem(pWindowFPSSys);
		Engine::AddSystem(pDrawGridSys);
		Engine::AddSystem(pDrawCollisionSys);

		Engine::Init();
	}
}
