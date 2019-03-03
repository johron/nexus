#pragma once

#include "SFML/Graphics.hpp"

namespace nexus::sfml {
struct window {
	window() 
		: m_window{} {
	}

	window(uint16_t width, uint16_t height, const std::string& title = "unnamed")
		: m_window(sf::VideoMode(width, height), title) {
	}

	[[nodiscard]] bool is_open() const {
		return m_window.isOpen();
	}

	void close() {
		m_window.close();
	}

	void set_size(uint16_t width, uint16_t height) {
		m_window.setSize({width, height});
	}

	void set_position(uint16_t x, uint16_t y) {
		m_window.setPosition({x, y});
	}



private:
	sf::Window m_window;
};
}  // namespace nexus::sfml