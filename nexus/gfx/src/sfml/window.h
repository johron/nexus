#pragma once
#include "util.h"
#include "view.h"

namespace nexus::gfx {
template <class drawable_t>
struct drawer {
	template <class render_target, class... arg_t>
	static void draw(render_target& target, drawable_t drawable, arg_t... args) {
		target.draw(drawable, std::forward<arg_t>(args)...);
	}
};

struct window {
	window()
		: m_window{} {}

	window(uint32_t width, uint32_t height, const std::string& title = "unnamed")
		: m_window(sf::VideoMode(width, height), title, 7u, sf::ContextSettings(0, 0, 8)) {
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

	operator sf::RenderWindow&() {
		return m_window;
	}

	template <class drawable_t, class... arg_t>
	inline void draw(const drawable_t& drawable, arg_t... args) {
		drawer<drawable_t>::draw(m_window, drawable, std::forward<arg_t>(args)...);
	}

	void update(duration delta) {
		ImGui::SFML::Update(m_window, sf::microseconds(delta.to_microseconds().count()));
		poll_events();
	}

	void clear(const color& color = colors::black) {
		m_window.clear(util::make_color(color));
	}

	void present() {
		ImGui::SFML::Render(m_window);
		m_window.display();
	}

private:
	void poll_events() {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			switch (event.type) {
				case sf::Event::Closed:
					close();
					break;
				default:
					break;
			}
		}
	}

	sf::RenderWindow m_window;
};
}  // namespace nexus::gfx