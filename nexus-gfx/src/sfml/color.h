#pragma once

namespace nexus::gfx {
struct color {
	color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha) {}

	uint32_t to_int() const {
		return uint32_t(r) << 24 | uint32_t(g) << 16 | uint32_t(b) << 8 | uint32_t(a);
	}

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};
}  // namespace nexus::gfx