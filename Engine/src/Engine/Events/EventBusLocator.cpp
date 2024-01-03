#include "pch.h"

#include "EventBusLocator.hpp"

namespace MyEngine
{
	template <typename T>
	NullEventBus<T> EventBusLocator<T>::m_nullService = NullEventBus<T>();
	template <typename T>
	iEventBus<T>* EventBusLocator<T>::m_eventBus = &(EventBusLocator<T>::m_nullService);
}
