#pragma once
#include "drawable.h"

namespace nexus::gfx {
struct color {
	color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha) {
	}

	uint32_t to_int() const {
		return uint32_t(r) << 24 | uint32_t(g) << 16 | uint32_t(b) << 8 | uint32_t(a);
	}

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

template <class shape_t>
struct shape : public drawable<shape_t> {
protected:
	template <class... arg_t>
	shape(arg_t... args)
		: drawable<shape_t>(std::forward<arg_t>(args)...) {
	}

public:
	void set_fill_color(const color& fill) {
		this->get_drawable().setFillColor(sf::Color(fill.to_int()));
	}

	void set_outline_color(const color& outline) {
		this->get_drawable().setOutlineColor(sf::Color(outline.to_int()));
	}

	void set_outline_thickness(float thickness) {
		this->get_drawable().setOutlineThickness(thickness);
	}
};

struct circle : public shape<sf::CircleShape> {
	circle(float radius)
		: shape(radius) {
	}
};

struct rect : public shape<sf::RectangleShape> {
	rect(float width, float height)
		: shape(sf::Vector2f(width, height)) {
	}
};

struct triangle : public shape<sf::CircleShape> {
	triangle(float radius)
		: shape(radius, 3) {
	}
};

struct hexagon : public shape<sf::CircleShape> {
	hexagon(float radius) 
		: shape(radius, 6) {
	}
};

}  // namespace nexus::sfml