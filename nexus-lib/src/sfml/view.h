#pragma once
#include "SFML/Graphics/View.hpp"

namespace nexus::sfml {
struct view {

	operator const sf::View&() const {
		return m_view;
	}


private:
	sf::View m_view;
};
}  // namespace nexus::sfml