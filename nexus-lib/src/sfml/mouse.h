#pragma once
#include "SFML/Window/Mouse.hpp"

namespace nexus::sfml {
struct mouse {
	enum button {
		left,
		right,
		middle,
		extra_1,
		extra_2,
	};

	static bool is_button_down(const button& button) {
		return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
	}

	static vector2i get_position() {
		return util::make_vector(sf::Mouse::getPosition());
	}

	static void set_position(const vector2i& position) {
		sf::Mouse::setPosition(util::make_vector(position));
	}
};

}