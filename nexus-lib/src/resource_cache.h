#pragma once
#include <optional>

namespace nexus {
template <class resource_t>
struct loader {
	template <class... arg_t>
	std::optional<resource_t> get(arg_t... args) {
		return resource_t(args...);
	}
};

template <class key_t, class resource_t>
struct resource_cache {
	std::shared_ptr<resource_t> get(const key_t& key) {
		if (!is_loaded(key)) {

		}

		return m_resources[key];
	}

	[[nodiscard]] bool is_loaded(const key_t& key) const {
		return m_resources.find(key) != m_resources.end();
	}

	template <class... arg_t>
	resource_t& load(arg_t... args) {
		
	}

	void release_unused() {
		for (auto& entry : m_resources) {
			if (entry.second->use_count() == 1) {
				m_resources.erase(entry.first);
			}
		}
	}

private:

	std::unordered_map<key_t, std::shared_ptr<resource_t>> m_resources;
};
}  // namespace nexus
