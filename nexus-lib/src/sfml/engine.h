#pragma once

#include "window.h"

namespace nexus::sfml {
struct engine {
	engine(uint32_t width, uint32_t height, std::string&& title)
		: m_window(std::make_unique<window>(width, height, std::move(title))) {
	}

	[[nodiscard]] bool is_running() const {
		return m_window && m_window->is_open();
	};

	void update() { 
		m_window->update();
	}

	void render() {
		m_window->render();
	}
	

private:
	std::unique_ptr<window> m_window;
};
}  // namespace nexus::sfml