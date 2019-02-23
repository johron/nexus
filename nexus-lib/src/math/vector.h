#pragma once
#include <type_traits>

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)  // nonstandard extension used: nameless struct/union
#elif __GNUC__
#pragma GCC diagnostic ignored "-Wpedantic"  // ISO C++ prohibits anonymous structs [-Wpedantic]
#pragma GCC diagnostic push
#endif

namespace nexus::math {
namespace detail {
template <class value_t, std::size_t N>
struct vector_storage {
	constexpr vector_storage()
		: m_storage{} {
	}

	template <class... arg_t>
	constexpr vector_storage(arg_t&&... data)
		: m_storage{static_cast<value_t>(std::forward<arg_t>(data))...} {
	}

	value_t m_storage[N];
};

template <class value_t>
struct vector_storage<value_t, 2> {
	constexpr vector_storage()
		: m_storage{} {
	}

	template <class... arg_t>
	constexpr vector_storage(arg_t&&... data)
		: m_storage{static_cast<value_t>(std::forward<arg_t>(data))...} {
	}

	union {
		struct {
			value_t x;
			value_t y;
		};
		value_t m_storage[2];
	};
};

template <class value_t>
struct vector_storage<value_t, 3> {
	constexpr vector_storage()
		: m_storage{} {
	}

	template <class... arg_t>
	constexpr vector_storage(arg_t&&... data)
		: m_storage{static_cast<value_t>(std::forward<arg_t>(data))...} {
	}

	union {
		struct {
			value_t x;
			value_t y;
			value_t z;
		};
		value_t m_storage[3];
	};
};

template <class value_t, std::size_t N, std::enable_if_t<std::is_arithmetic_v<value_t>, int> = 0>
struct vector_base : public vector_storage<value_t, N> {
	static constexpr std::size_t size() {
		return N;
	}

	[[nodiscard]] constexpr auto begin() const {
		return vector_storage<value_t, N>::m_storage;
	}

	[[nodiscard]] constexpr auto begin() {
		return vector_storage<value_t, N>::m_storage;
	}

	[[nodiscard]] constexpr auto end() const {
		return vector_storage<value_t, N>::m_storage + N;
	}

	[[nodiscard]] constexpr auto end() {
		return vector_storage<value_t, N>::m_storage + N;
	}

	[[nodiscard]] constexpr auto operator[](std::size_t index) const {
		return vector_storage<value_t, N>::m_storage[index];
	}

	[[nodiscard]] constexpr auto operator[](std::size_t index) {
		return vector_storage<value_t, N>::m_storage[index];
	}

protected:
	template <class... arg_t>
	constexpr vector_base(arg_t&&... args)
		: vector_storage<value_t, N>{std::forward<arg_t>(args)...} {
	}

	template <class other_t>
	constexpr vector_base(const vector_base<other_t, N>& other)
		: vector_base{other, std::make_index_sequence<N>{}} {
	}

private:
	template <class other_t, std::size_t... index>
	constexpr vector_base(const vector_base<other_t, N, 0>& other, std::index_sequence<index...>)
		: vector_base{other[index]...} {
	}
};
}  // namespace detail

template <class value_t, std::size_t N, std::enable_if_t<N != 0, int> = 0>
struct vector : public detail::vector_base<value_t, N> {
	constexpr vector() {
	}

	template <class... arg_t>
	constexpr vector(arg_t&&... args)
		: detail::vector_base<value_t, N>{std::forward<arg_t>(args)...} {
	}
};

template <class value_t>
struct vector<value_t, 2> : public detail::vector_base<value_t, 2> {
	using detail::vector_storage<value_t, 2>::x;
	using detail::vector_storage<value_t, 2>::y;

	constexpr vector() {
	}

	template <class... arg_t, std::enable_if_t<sizeof...(arg_t) == 2, int> = 0>
	constexpr vector(arg_t&&... args)
		: detail::vector_base<value_t, 2>{std::forward<arg_t>(args)...} {
	}

	template <class other_value_t>
	constexpr vector(const vector<other_value_t, 2>& other)
		: detail::vector_base<value_t, 2>{other} {
	}
};

using vector2f = vector<float, 2>;
using vector2i = vector<int, 2>;

template <class value_t>
struct vector<value_t, 3> : public detail::vector_base<value_t, 3> {
	using detail::vector_storage<value_t, 3>::x;
	using detail::vector_storage<value_t, 3>::y;
	using detail::vector_storage<value_t, 3>::z;

	constexpr vector() {
	}

	template <class... arg_t, std::enable_if_t<sizeof...(arg_t) == 3, int> = 0>
	constexpr vector(arg_t&&... args)
		: detail::vector_base<value_t, 3>{std::forward<arg_t>(args)...} {
	}
};

using vector3f = vector<float, 3>;
using vector3i = vector<int, 3>;
}  // namespace nexus::math

#if _MSC_VER
#pragma warning(pop)
#elif __GNUC__
#pragma GCC diagnostic pop  // "-Wpedantic"
#endif