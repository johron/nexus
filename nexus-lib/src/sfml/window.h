#pragma once
#include "util.h"
#include "view.h"
#include "../time.h"

namespace nexus::sfml {
template <class keyboard_t, class mouse_t>
struct window {
	window()
		: m_window{} {
	}

	window(uint32_t width, uint32_t height, const std::string& title = "unnamed")
		: m_window(sf::VideoMode(width, height), title, 7u, sf::ContextSettings{0, 0, 8}) {
		ImGui::SFML::Init(m_window);
	}

	~window() {
		ImGui::SFML::Shutdown();
	}

	[[nodiscard]] bool is_open() const {
		return m_window.isOpen();
	}

	void close() {
		m_window.close();
	}

	[[nodiscard]] vector2u size() const {
		return util::make_vector(m_window.getSize());
	}

	void set_size(const vector2u& size) {
		m_window.setSize(util::make_vector(size));
	}

	[[nodiscard]] vector2i get_position() const {
		return util::make_vector(m_window.getPosition());
	}

	void set_position(const vector2i& pos) {
		m_window.setPosition(util::make_vector(pos));
	}

	void set_position(int x, int y) {
		set_position({x, y});
	}

	void set_view(const view& current_view) {
		m_window.setView(current_view);
	}

	void reset_view() {
		m_window.setView(m_window.getDefaultView());
	}

	keyboard_t& keyboard() {
		return m_keyboard;
	}

	mouse_t& mouse() {
		return m_mouse;
	}

	operator sf::RenderWindow&() {
		return m_window;
	}

	template <class drawable_t>
	inline void draw(const drawable_t& drawable) {
		m_window.draw(drawable);
	}

	void update(const time& delta_time) {
		ImGui::SFML::Update(m_window, sf::microseconds(delta_time.as_microseconds()));
	}

	void poll_events() {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			switch (event.type) {
				case sf::Event::Closed:
					close();
					break;
				case sf::Event::KeyPressed:
					m_keyboard.trigger(static_cast<typename keyboard_t::key>(event.key.code));
					break;
				case sf::Event::MouseButtonPressed:
					m_mouse.trigger(static_cast<typename mouse_t::button>(event.mouseButton.button),
									nexus::vector2i(event.mouseButton.x, event.mouseButton.y));
				default:
					break;
			}
		}
	}

	void clear() {
		m_window.clear(sf::Color::Black);
	}

	void present() {
		ImGui::SFML::Render(m_window);
		m_window.display();
	}

private:
	sf::RenderWindow m_window;
	keyboard_t m_keyboard;
	mouse_t m_mouse;
};
}  // namespace nexus::sfml