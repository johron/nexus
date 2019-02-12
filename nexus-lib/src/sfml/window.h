#pragma once
#include "SFML/Graphics.hpp"

namespace nexus::sfml {
struct window {
	window(uint32_t width, uint32_t height, std::string&& title)
		: m_window(sf::VideoMode(width, height, 32), title) {}

	bool is_open() const { return m_window.isOpen(); }

	void update() {
		sf::Event current_event;
		while (m_window.pollEvent(current_event)) {
			switch (current_event.type) {
				case sf::Event::Closed:
					m_window.close();
					break;

				case sf::Event::KeyPressed:
					if (current_event.key.code == sf::Keyboard::Escape) {
						m_window.close();
					}
			}
		}
	}

	void render() { 
		sf::CircleShape circle(20);
		circle.setFillColor(sf::Color(255, 0, 0, 100));

		m_window.draw(circle);

		m_window.display();
		m_window.clear(sf::Color::Black);
	}

private:
	sf::RenderWindow m_window;
};
}  // namespace nexus::sfml