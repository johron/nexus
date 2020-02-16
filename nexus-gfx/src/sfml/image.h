#pragma once
#include "color.h"

namespace nexus::gfx {
struct image : public sf::Image {
	image(uint32_t width, uint32_t height, const color& color) {
		create(width, height, util::make_color(color));
	}

	image(const std::string& filename) {
		if (!loadFromFile(filename)) {
			throw std::runtime_error("unable to load image from file: " + filename);
		}
	}

	image(const void* data, std::size_t size) {
		if (!loadFromMemory(data, size)) {
			throw std::runtime_error("unable to load image from memory");
		}
	}

	[[nodiscard]] bool save(const std::string& filename) const {
		saveToFile(filename);
	}

	vector2u size() const {
		return util::make_vector(getSize());
	}

	void set_pixel(uint32_t x, uint32_t y, const color& color) {
		setPixel(x, y, util::make_color(color));
	}

	color get_pixel(uint32_t x, uint32_t y) const {
		return util::make_color(getPixel(x, y));
	}
};
}  // namespace nexus::gfx