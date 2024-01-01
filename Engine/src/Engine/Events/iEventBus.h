#pragma once

#include "Event.hpp"

#include <functional>

namespace MyEngine
{
    template <typename T>
    class iEventBus
    {
    protected:
        using EventHandler = std::function<void(const Event<T>&)>;

    public:
        iEventBus() {}
        virtual ~iEventBus() {};

        // Subscribe to an event
        virtual void Subscribe(T eventType, const iEventBus::EventHandler& handler) = 0;

        // Publish an event to all the listeners
        virtual void Publish(const Event<T>& event) = 0;
    };
}
