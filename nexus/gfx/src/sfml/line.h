#pragma once
#include "util.h"

namespace nexus::gfx {
struct line {
	template <class... vertex>
	line(vertex... vertices)
		: m_vertices({util::make_vertex(vertices)...}) {}

	auto size() const {
		return m_vertices.size();
	}

	auto data() const {
		return m_vertices.data();
	}

private:
	std::vector<sf::Vertex> m_vertices;
};

template <>
struct drawer<line> {
	template <class render_target, class... arg_t>
	static void draw(render_target& target, line drawable, arg_t... args) {
		target.draw(drawable.data(), drawable.size(), sf::LinesStrip);
	}
};
}  // namespace nexus::gfx