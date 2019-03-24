#pragma once
#include <optional>

namespace nexus {
template <class resource_t>
struct loader {
	template <class key_t>
	static std::shared_ptr<resource_t> get(const key_t& key) {
		return std::make_shared<resource_t>(key);
	}
};

template <class key_t, class resource_t>
struct resource_cache {
	[[nodiscard]] std::shared_ptr<resource_t> get(const key_t& key) {
		auto iterator = m_resources.find(key);
		if (iterator == m_resources.end()) {
			iterator = load(key);
		}

		return iterator->second;	
	}

	[[nodiscard]] bool is_loaded(const key_t& key) const {
		return m_resources.find(key) != m_resources.end();
	}

	void release_unused() {
		static const auto is_unused = [](const auto& entry) { return entry.second.use_count() == 1; };
		for (auto it = m_resources.begin(); it != m_resources.end();) {
			it = is_unused(*it) ? m_resources.erase(it) : ++it;
		}
	}

	auto load(const key_t& key) {
		if (auto resource = loader<resource_t>::get(key)) {
			return m_resources.insert({key, std::move(resource)}).first;
		} else {
			throw std::runtime_error("failed to load resource");
		}
	}

	[[nodiscard]] std::size_t size() const {
		return m_resources.size();
	}

private:
	std::unordered_map<key_t, std::shared_ptr<resource_t>> m_resources;
};
}  // namespace nexus
