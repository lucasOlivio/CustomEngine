#pragma once

#include "Engine/Core/StateProperties.h"

#include "Engine/Events/Event.hpp"

#include "Engine/ECS/Scene/Scene.h"

namespace MyEngine
{
	enum eGameStateEvents
	{
		GAME_STARTED,
		GAME_RUNNING,
		GAME_STOPPED,
		GAME_LEVELUP,
		GAME_OVER
	};

	class GameStartedEvent : public Event<eGameStateEvents>
	{
	public:
		GameStartedEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_STARTED, "GameStarted") {};
		virtual ~GameStartedEvent() {};

		eGameStates prevState;
		Scene* pScene;
	};

	class GameRunningEvent : public Event<eGameStateEvents>
	{
	public:
		GameRunningEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_RUNNING, "GameRunning") {};
		virtual ~GameRunningEvent() {};

		eGameStates prevState;
		Scene* pScene;
	};

	class GameStoppedEvent : public Event<eGameStateEvents>
	{
	public:
		GameStoppedEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_STOPPED, "GameStopped") {};
		virtual ~GameStoppedEvent() {};

		eGameStates prevState;
		Scene* pScene;
	};

	class GameLevelUpEvent : public Event<eGameStateEvents>
	{
	public:
		GameLevelUpEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_LEVELUP, "GameLevelUp") {};
		virtual ~GameLevelUpEvent() {};

		eGameStates prevState;
		Scene* pScene;
	};

	class GameOverEvent : public Event<eGameStateEvents>
	{
	public:
		GameOverEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_OVER, "GameOver") {};
		virtual ~GameOverEvent() {};

		eGameStates prevState;
		Scene* pScene;
	};
}
