#pragma once
#include "util.h"

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

	[[nodiscard]] vector2u size() const {
		return util::make_vector(m_window.getSize());
	}

	void set_size(const vector2u& size) {
		m_window.setSize(util::make_vector(size));
	}

	[[nodiscard]] vector2i position() const {
		return util::make_vector(m_window.getPosition());
	}

	void set_position(const vector2i& pos) {
		m_window.setPosition(util::make_vector(pos));
	}

private:
	sf::Window m_window;
};
}  // namespace nexus::sfml