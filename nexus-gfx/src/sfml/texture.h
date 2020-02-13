#pragma once

namespace nexus {
struct texture : public sf::Texture {
	texture(const std::string& filename) {
		if (!loadFromFile(filename)) {
			throw std::runtime_error("failed to load texture: " + filename);
		}
	}
};
}  // namespace nexus::sfml