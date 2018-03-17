#pragma once

#include <functional>
#include <vector>

template <typename... Args>
class Event final
{
public:
	using Delegate = std::function<void(Args...)>;

	void operator+=(Delegate delegate);
	void operator()(Args... args) const;

private:
	using Delegates = std::vector<Delegate>;

	Delegates m_delegates;
};

template <typename... Args>
inline void Event<Args...>::operator+=(Delegate delegate)
{
	m_delegates.push_back(std::move(delegate));
}

template <typename... Args>
inline void Event<Args...>::operator()(Args... args) const
{
	for (const auto& delegate : m_delegates)
	{
		delegate(std::forward<Args>(args)...);
	}
}
