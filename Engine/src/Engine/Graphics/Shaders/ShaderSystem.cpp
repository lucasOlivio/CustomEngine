#include "pch.h"

#include "ShaderSystem.h"
#include "Engine/ECS/SingletonComponents/ConfigPathLocator.h"
#include "Engine/Graphics/Shaders/ShaderManagerLocator.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
	void ShaderSystem::Start(Scene* pScene)
	{
		ConfigPathComponent* pConfigPath = ConfigPathLocator::Get();
		iShaderManager* pShaderManager = ShaderManagerLocator::Get();

		// Setup shaders
		pShaderManager->SetBasePath(pConfigPath->pathShaders);
		std::string shaderName = "Shader01"; // TODO: This should come from config?
		pShaderManager->AddShaderProgram(shaderName);
		pShaderManager->UseShaderProgram(shaderName);
	}

	void ShaderSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void ShaderSystem::Render(Scene* pScene)
	{
	}

	void ShaderSystem::End(Scene* pScene)
	{
	}
}
