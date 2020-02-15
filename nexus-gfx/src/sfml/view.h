#pragma once
#include "util.h"

namespace nexus::gfx {
struct view {
	view()
		: m_view() {}

	view(vector2f&& pos, vector2f&& size)
		: m_view(sf::FloatRect(pos.x, pos.y, size.x, size.y)) {}

	vector2f get_center() const {
		return util::make_vector(m_view.getCenter());
	}

	void set_center(float x, float y) {
		m_view.setCenter(x, y);
	}

	void set_center(const vector2f& pos) {
		set_center(pos.x, pos.y);
	}

	vector2f get_size() const {
		return util::make_vector(m_view.getSize());
	}

	void set_size(float width, float height) {
		m_view.setSize(width, height);
	}

	void set_size(const vector2f& size) {
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

	void move(const vector2f& offset) {
		move(offset.x, offset.y);
	}

	void reset(vector2f&& pos, vector2f&& size) {
		m_view.reset(sf::FloatRect(pos.x, pos.y, size.x, size.y));
	}

	void zoom(float factor) {
		m_view.zoom(factor);
	}

	void set_viewport(const rectf& rect) {
		m_view.setViewport(util::make_rect(rect));
	}

	rectf get_viewport() const {
		return util::make_rect(m_view.getViewport());
	}

	operator const sf::View&() const {
		return m_view;
	}

private:
	sf::View m_view;
};
}  // namespace nexus::gfx