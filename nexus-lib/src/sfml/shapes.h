#pragma once
#include "../color.h"
#include "drawable.h"

namespace nexus::sfml {
template <class shape_t>
struct shape : public drawable<shape_t> {
protected:
	template <class... arg_t>
	shape(arg_t... args)
		: drawable<shape_t>(std::forward<arg_t>(args)...) {
	}

public:
	void set_fill_color(const color& fill) {
		drawable<shape_t>::get_drawable().setFillColor(sf::Color(fill.to_int()));
	}

	void set_outline_color(const color& outline) {
		drawable<shape_t>::get_drawable().setOutlineColor(sf::Color(outline.to_int()));
	}

	void set_outline_thickness(float thickness) {
		drawable<shape_t>::get_drawable().setOutlineThickness(thickness);
	}
};

struct circle : public shape<sf::CircleShape> {
	circle(float radius)
		: shape(radius) {
	}

	float get_radius() const {
		return get_drawable().getRadius();
	}

	void set_radius(float radius) {
		get_drawable().setRadius(radius);
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