#pragma once

#ifdef _MSC_VER
#define USE_PARALLEL_EXECUTION
#endif

#ifdef USE_PARALLEL_EXECUTION
#include <execution>
namespace nexus::parallel {
constexpr bool supports_parallel_algorithms = true;
constexpr auto& execute_parallel = std::execution::par;
constexpr auto& execute_sequential = std::execution::seq;
}
#else
namespace nexus::parallel {
constexpr bool supports_parallel_algorithms = false;
constexpr auto execute_parallel = std::false_type{};
constexpr auto execute_sequential = std::false_type{};
}
#endif

namespace nexus::parallel {
template <class ex_policy_t, class iterator_t, class functor_t>
inline void for_each(ex_policy_t&& policy, iterator_t&& begin, iterator_t&& end, functor_t&& func) {
	if constexpr (supports_parallel_algorithms) {
		std::for_each(std::forward<ex_policy_t>(policy),
					  std::forward<iterator_t>(begin),
					  std::forward<iterator_t>(end),
					  std::forward<functor_t>(func));
	} else {
		(void)policy;
		std::for_each(
			std::forward<iterator_t>(begin), std::forward<iterator_t>(end), std::forward<functor_t>(func));
	}
}
}  // namespace nexus::parallel