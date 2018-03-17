#pragma once

#include "event.h"

#include <functional>

template <typename... Args>
class EventRegistrar final
{
	using Event = Event<Args...>;
	using Delegate = typename Event::Delegate;

public:
	EventRegistrar(Event& event);
	void operator+=(Delegate delegate);

private:
	Event& m_event;
};

template <typename... Args>
inline EventRegistrar<Args...>::EventRegistrar(Event& event)
	: m_event(event)
{}

template <typename... Args>
inline void EventRegistrar<Args...>::operator+=(Delegate delegate)
{
	m_event += std::move(delegate);
}
