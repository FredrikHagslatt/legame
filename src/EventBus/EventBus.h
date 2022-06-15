#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "Logger/Logger.h"
#include <typeindex>
#include <map>
#include <list>
#include "Event.h"

class IEventCallback
{
private:
    virtual void Call(Event &event) = 0;
public:
    virtual ~IEventCallback() = default;
    void Execute(Event &event)
    {
        Call(event);
    }
}

template<typename TOwner, typename TEvent>
class EventCallback : public IEventCallback
{
private:
    typedef void (TOwner::*CallbackFunction)(TEvent&);
    TOwner *ownerInstance;
    CallbackFunction callbackFunction;

    virtual void Call(Event& event) override
    {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(event));
    }

public:
    EventCallback(TOwner *ownerInstance, CallbackFunction callbackFunction)
    : ownerInstance(ownerInstance),
      callbackFunction(callbackFunction)
    {
    }

    virtual ~EventCallback() override = default;

}

typedef std::list<std::unique_ptr<IEventCallback>> HanderList;

class EventBus
{
private:
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

public:
    EventBus()
    {
        Logger::Log("EventBus created!");
    }
    ~EventBus()
    {
        Logger::Log("EventBus destroyed!");
    }

    template<typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner *ownerInstance, void (TOwner::*callbackFunction)(TEvent &event))
    {
        if (!subscribers[typeid(TEvent)].get())
        {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

    template<typename TEvent, typename TOwner>
    void EmitEvent(TArgs&& ...args)
    {
        auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers)
        {
            for (auto it = handlers->begin(), it != handler->end(), it++)
            {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->Execute(event);
            }
        }
    }

}

#endif