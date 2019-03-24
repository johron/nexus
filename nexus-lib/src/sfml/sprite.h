#pragma once
#include "drawable.h"
#include "texture.h"

namespace nexus::sfml {

struct sprite : public drawable<sf::Sprite> {
	sprite(const std::string& filename)
		: m_texture(std::make_shared<texture>(filename)) {
		get_drawable().setTexture(*m_texture);
	}

private:
	std::shared_ptr<texture> m_texture;
};
}  // namespace nexus::sfml