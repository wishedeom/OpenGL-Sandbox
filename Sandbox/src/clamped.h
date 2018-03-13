#pragma once

#include <utility>

template <typename T, typename MinProvider, typename MaxProvider>
struct Clamped final
{
	static constexpr T min = MinProvider::value;
	static constexpr T max = MaxProvider::value;

public:
	static constexpr T Clamp(T x);

	Clamped(T x);
	Clamped& operator=(T x);
	
	Clamped(const Clamped<T, MinProvider, MaxProvider>&) = default;
	Clamped(Clamped<T, MinProvider, MaxProvider>&&) = default;
	Clamped& operator=(const Clamped<T, MinProvider, MaxProvider>&) = default;
	Clamped& operator=(Clamped<T, MinProvider, MaxProvider>&&) = default;

	const T& Value() const;
	T Value();

private:
	T m_value;
};

template <typename T>
struct ZeroProvider final
{
	static constexpr T value = T(0);
};

template <typename T>
struct OneProvider final
{
	static constexpr T value = T(1);
};

template <typename T>
using ClampUnit = Clamped<T, ZeroProvider<T>, OneProvider<T>>;

template <typename T, typename MinProvider, typename MaxProvider>
inline constexpr T Clamped<T, MinProvider, MaxProvider>::Clamp(T x)
{
	return x < min ? min
		:  x > max ? max
		:  std::move(x);
}

template <typename T, typename MinProvider, typename MaxProvider>
inline Clamped<T, MinProvider, MaxProvider>::Clamped(T x)
	: m_value(Clamp(std::move(x)))
{}

template <typename T, typename MinProvider, typename MaxProvider>
inline Clamped<T, MinProvider, MaxProvider>& Clamped<T, MinProvider, MaxProvider>::operator=(T x)
{
	m_value = std::move(x);
}

template <typename T, typename MinProvider, typename MaxProvider>
inline const T& Clamped<T, MinProvider, MaxProvider>::Value() const
{
	return m_value;
}

template <typename T, typename MinProvider, typename MaxProvider>
inline T Clamped<T, MinProvider, MaxProvider>::Value()
{
	return m_value;
}
