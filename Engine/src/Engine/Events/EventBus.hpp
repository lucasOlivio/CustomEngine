#pragma once

#include "iEventBus.h"
#include "Event.hpp"

#include <functional>
#include <unordered_map>

namespace MyEngine
{
    template <typename T>
    class EventBus : public iEventBus<T>
    {
    private:
        using EventHandler = iEventBus<T>::EventHandler;

    public:
        EventBus() {}
        virtual ~EventBus() {};

        // Subscribe to an event
        virtual void Subscribe(T eventType, const EventHandler& handler)
        {
            m_subscribers[eventType].push_back(handler);
        }

        // Publish an event to all the listeners
        virtual void Publish(const Event<T>& event)
        {
            if (m_subscribers.find(event.GetType()) == m_subscribers.end())
            {
                // No subs
                return;
            }

            for (const auto& handler : m_subscribers[event.GetType()])
            {
                // Process until hadled or reach end of listeners
                if (event.IsHandled())
                {
                    break;
                }
                handler(event);
            }
        }

    private:
        std::unordered_map<T, std::vector<EventHandler>> m_subscribers;
    };
}
