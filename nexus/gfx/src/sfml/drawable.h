#pragma once
#include "util.h"

namespace nexus {
template <class drawable_t>
struct drawable {
	void set_position(float x, float y) {
		m_drawable->setPosition(x, y);
	}

	void set_position(const vector2f& pos) {
		m_drawable->setPosition(pos.x, pos.y);
	}

	vector2f get_position() const {
		return util::make_vector(m_drawable->getPosition());
	}

	void set_rotation(float angle) {
		m_drawable->setRotation(angle);
	}

	float get_rotation() const {
		return m_drawable->getRotation();
	}

	void set_origin(const vector2f& offset) {
		m_drawable->setOrigin(util::make_vector(offset));
	}

	void move(const vector2f& offset) {
		return m_drawable->move(util::make_vector(offset));
	}

	operator const drawable_t&() const {
		return *m_drawable;
	}

	drawable& operator=(const drawable& other) {
		get_drawable() = other.get_drawable();
		return *this;
	}

protected:
	drawable_t& get_drawable() {
		return *m_drawable;
	}

	template <class... arg_t>
	drawable(arg_t... args)
		: m_drawable(std::make_unique<drawable_t>(std::forward<arg_t>(args)...)) {}

	drawable(const drawable& other)
		: m_drawable(std::make_unique<drawable_t>(*other.m_drawable)) {}

private:
	std::unique_ptr<drawable_t> m_drawable;
};
}  // namespace nexus