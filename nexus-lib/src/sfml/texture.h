#pragma once
#include "SFML/Graphics/Texture.hpp"

namespace nexus::sfml {
struct texture {
	texture(std::string&& filename)
		: m_texture(filename)

private:
	sf::Texture m_texture;
};
}  // namespace nexus::sfml