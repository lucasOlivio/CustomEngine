#pragma once

#include "Event.hpp"
#include "Engine/Core/InputProperties.h"

namespace MyEngine
{
	enum eInputEvents
	{
		KEYBOARD
	};

	class KeyboardEvent : public Event<eInputEvents>
	{
	public:
		KeyboardEvent() :
			Event<eInputEvents>(eInputEvents::KEYBOARD, "Keyboard") {};
		virtual ~KeyboardEvent() {};

		sKeyData keyData;
	};
}
