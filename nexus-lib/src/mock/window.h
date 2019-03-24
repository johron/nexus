#pragma once
#include "../math/vector.h"

namespace nexus::mock {
struct window {
	window()
		: m_size{}
		, m_position{}
		, m_is_open(false) {
	}

	window(uint16_t width, uint16_t height, const std::string& title = "unnamed")
		: m_size{width, height}
		, m_position{0, 0}
		, m_title(title)
		, m_is_open(true) {
	}

	[[nodiscard]] bool is_open() const {
		return m_is_open;
	}

	void close() {
		m_is_open = false;
	}

	[[nodiscard]] vector2u size() const {
		return m_size;
	}

	void set_size(const vector2u& size) {
		m_size = size;
	}

	[[nodiscard]] vector2i position() const {
		return m_position;
	}

	void set_position(const vector2i& pos) {
		m_position = pos;
	}

	void poll_events() {
	}

private:
	vector2u m_size;
	vector2i m_position;
	std::string m_title;
	bool m_is_open;
};
}  // namespace nexus::mock