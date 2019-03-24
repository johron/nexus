#pragma once

namespace nexus {
struct type_id {
	template <class type>
	static uint32_t get() {
		static uint32_t id = the_global_counter++;
		return id;
	}

	template <class type>
	static uint32_t get(const type&) {
		return get<type>();
	}

private:
	static uint32_t the_global_counter;
};
}