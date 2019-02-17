#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace nexus {
struct color_t : public sf::Color {
	color_t(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
		: sf::Color(red, green, blue, alpha) {
	}
};


// should add a mechanism to share texture memory;
struct sprite {
	sprite(const std::string& filename) {
		if (!m_texture.loadFromFile(filename)) {
			throw std::runtime_error("failed to load texture");
			// set to fallback texture;
		} else {
			m_sprite.setTexture(m_texture);
		}
	}

	sprite(size_t width, size_t height, color_t color = { 255, 0, 255, 255 }) {
		m_texture.create(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
		m_sprite.setTexture(m_texture);
		m_sprite.setColor(color);
	}

	const sf::Sprite& operator()() const {
		return m_sprite;
	}

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

/*
struct rect {
	rect(int32_t x, int32_t y, uint32_t width, uint32_t height)
		: m_rect(x, y, width, height) {
	}

	const auto& operator()() const {
		return m_rect;
	}

private:
	sf::RectangleShape m_rect;
};*/

}  // namespace nexus