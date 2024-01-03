#pragma once

#include "NullEventBus.hpp"
#include "iEventBus.h"

namespace MyEngine
{
	template <typename T>
	class EventBusLocator
	{
	public:
		static iEventBus<T>* Get() { return m_eventBus; }

		static void Set(iEventBus<T>* eventBus)
		{
			if (eventBus == nullptr)
			{
				m_eventBus = &m_nullService;
			}
			else
			{
				m_eventBus = eventBus;
			}
		}

	private:
		static iEventBus<T>* m_eventBus;
		static NullEventBus<T> m_nullService;
	};
}
