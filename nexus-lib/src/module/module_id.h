#pragma once

namespace nexus {
using module_id = uint32_t;

struct type_id {
	template <class type>
	static module_id get() {
		static module_id id = the_global_counter++;
		return id;
	}

	template <class type>
	static module_id get(const type&) {
		return get<type>();
	}

private:
	static module_id the_global_counter;
};

__declspec(selectany) module_id nexus::type_id::the_global_counter = 0;
}