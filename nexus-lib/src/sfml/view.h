#pragma once
#include "util.h"

namespace nexus::sfml {
struct view {
	view()
		: m_view() {
	}

	view(nexus::vector2f&& pos, nexus::vector2f&& size)
		: m_view(sf::FloatRect(pos.x, pos.y, size.x, size.y)) {
	}
	
	nexus::vector2f get_center() const {
		return util::make_vector(m_view.getCenter());
	}

	void set_center(float x, float y) {
		m_view.setCenter(x, y);
	}

	void set_center(const nexus::vector2f& pos) {
		set_center(pos.x, pos.y);
	}

	nexus::vector2f get_size() const {
		return util::make_vector(m_view.getSize());
	}

	void set_size(float width, float height) {
		m_view.setSize(width, height);
	}

	void set_size(const nexus::vector2f& size) {
		set_size(size.x, size.y);
	}

	void set_rotation(float angle) {
		m_view.setRotation(angle);
	}

	float get_rotation() const {
		return m_view.getRotation();
	}

	void rotate(float angle) {
		m_view.rotate(angle);
	}

	void move(float x, float y) {
		m_view.move(x, y);
	}

	void move(const nexus::vector2f& offset) {
		move(offset.x, offset.y);
	}

	void reset(nexus::vector2f&& pos, nexus::vector2f&& size) {
		m_view.reset(sf::FloatRect(pos.x, pos.y, size.x, size.y));
	}

	void zoom(float factor) {
		m_view.zoom(factor);
	}

	operator const sf::View&() const {
		return m_view;
	}

private:
	sf::View m_view;
};
}  // namespace nexus::sfml