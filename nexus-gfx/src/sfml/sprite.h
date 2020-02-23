#pragma once
#include "drawable.h"
#include "texture.h"

namespace nexus::gfx {
struct sprite : public drawable<sf::Sprite> {
	sprite(const std::string& filename)
		: m_texture(std::make_unique<texture>(filename, recti{})) {
		get_drawable().setTexture(*m_texture);
	}

	sprite(std::unique_ptr<texture> texture)
		: m_texture(std::move(texture)) {
		get_drawable().setTexture(*m_texture);
	}

	sprite(std::shared_ptr<texture> texture) 
		: m_texture(texture) {
		get_drawable().setTexture(*m_texture);
	}

	void set_texture(std::shared_ptr<texture> texture) {
		m_texture = texture;
		get_drawable().setTexture(*m_texture);
	}

private:
	std::shared_ptr<texture> m_texture;
};
}  // namespace nexus::gfx