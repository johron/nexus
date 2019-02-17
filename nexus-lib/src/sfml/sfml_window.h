#pragma once
#include "SFML/Graphics.hpp"
#include "sfml_keyboard.h"
#include "../input_handler.h"

namespace nexus {
struct window {
	window(uint32_t width, uint32_t height, std::string&& title)
		: m_window(sf::VideoMode(width, height, 32), title) { }

	bool is_open() const { return m_window.isOpen(); }

	void poll_events() {
		sf::Event current_event;
		while (m_window.pollEvent(current_event)) {
			switch (current_event.type) {
				case sf::Event::Closed:
					close();
					break;

				case sf::Event::KeyPressed:
					m_input.trigger(keyboard::key(current_event.key.code));
					break;
			}
		}
	}

	template <class drawable_t>
	void draw(const drawable_t& drawable) {
		m_window.draw(drawable);
	}

	void clear() {
		m_window.clear(sf::Color::Black);
	}

	void present() {
		m_window.display();
	}

	auto& input() {
		return m_input;
	}

	void close() {
		m_window.close();
	}

private:
	sf::RenderWindow m_window;
	input_handler<nexus::keyboard::key> m_input;
};
}  // namespace nexus::sfml
