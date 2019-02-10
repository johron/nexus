#pragma once

#include <SFML/Graphics.hpp>

namespace nexus {
	struct engine {
		[[nodiscard]] bool is_running() const {
			return true;
		}

		void update() {

		}

		void render() {

		}

		[[nodiscard]] int shutdown() {
			return EXIT_SUCCESS;
		}
	};

	auto make_engine() {
		return engine{};
	}
}