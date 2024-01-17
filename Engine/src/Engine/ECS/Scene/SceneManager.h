#pragma once

#include "Engine/ECS/Scene/iSceneManager.h"

#include <map>

namespace MyEngine
{
	class SceneManager : public iSceneManager
	{
	public:
		SceneManager();
		virtual ~SceneManager();

		virtual void SetBasePath(std::string basePath);

		virtual Scene* LoadScene(std::string newSceneName);

		virtual void ChangeScene(std::string newSceneName, bool reload = false);

		virtual Scene* GetCurrentScene();
		virtual std::string GetCurrentSceneName();

		virtual Scene* GetScene(std::string sceneName);

	private:
		std::string m_basePath;

		std::string m_nameCurrScene;
		Scene* m_pCurrScene;

		std::map<std::string /*Scene name*/, Scene*> m_mapScenes;

		void m_TriggerSceneChange(std::string newSceneName, Scene* pNewScene);
	};
}
