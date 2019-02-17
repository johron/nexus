#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace nexus {
struct color_t : public sf::Color {
	color_t(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
		: sf::Color(red, green, blue, alpha) {
	}
};

struct texture : public sf::Texture {
	texture(const std::string& filename) {
		if (!loadFromFile(filename)) {
			throw std::runtime_error("failed to load texture");
		}
	}

	texture(size_t width, size_t height) {
		create(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
	}
};

struct sprite : public sf::Sprite {
	sprite(texture&& texture)
		: sf::Sprite(std::move(texture)) {
	}

	sprite(const std::string& filename)
		: sf::Sprite(texture(filename)) {
	}

	sprite(size_t width, size_t height, color_t color = {255, 0, 255, 255})
		: sf::Sprite(texture(width, height)) {
		setColor(color);
	}
};
}  // namespace nexus