#pragma once
#include "image.h"

namespace nexus::gfx {
struct texture : public sf::Texture {
	texture(const std::string& filename, const recti& area = recti{}) {
		if (!loadFromFile(filename, util::make_rect(area))) {
			throw std::runtime_error("failed to load texture from file: " + filename);
		}
	}

	texture(const image& image, const recti& area) {
		if (!loadFromImage(image, util::make_rect(area))) {
			throw std::runtime_error("failed to load texture from image");
		}
	}
};
}  // namespace nexus::gfx