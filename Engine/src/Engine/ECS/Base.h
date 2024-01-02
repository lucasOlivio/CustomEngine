#pragma once

#include <bitset>

namespace MyEngine
{
	// Numeric types alias
	typedef __int32 int32_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int8 uint8_t;

	// Alias for the component type id
	using ComponentType = uint8_t;
	using ComponentId = uint32_t;

	// Type alias for the entities ids
	using Entity = int32_t;

	// Used to define the size of arrays
	const ComponentType MAX_COMPONENTS = 16;
	const Entity MAX_ENTITIES = 1000;

	// Defines an entity's component composition
	using EntityMask = std::bitset<MAX_COMPONENTS>;

	// For any kind of orientation needed
	enum eDirections
	{
		BACKWARD,
		LEFT,
		RIGHT,
		FORWARD
	};
}
