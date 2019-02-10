#pragma once

namespace nexus {
	struct window {
		window(std::size_t width, std::size_t height, std::string&& title = "unnamed window")
			: m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), std::move(title))) { }

	private:
		std::unique_ptr<sf::RenderWindow> m_window;
	};
}