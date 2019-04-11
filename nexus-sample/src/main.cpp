#include "nexus/nexus.h"

struct sample_module : public nexus::module {
	sample_module() 
		: m_window(std::make_unique<nexus::window>(800, 600)) {
		m_window->keyboard().bind(nexus::keyboard::key::escape, [this]() { m_window->close(); });
	}

private:
	std::unique_ptr<nexus::window> m_window;
};

struct sample_1 : public sample_module {};
struct sample_2 : public sample_module {};

int main(int /*argc*/, char** /*argv*/) {
	nexus::module_manager manager;
	manager.register_module<sample_1>();
	manager.register_module<sample_2>();

	manager.load<sample_1>();
	manager.load<sample_2>();



	nexus::window window(800, 600, "sample window");
	window.keyboard().bind(nexus::keyboard::key::escape, [&window]() { window.close(); });

	nexus::sprite sprite("resources/ghost_red.png");
	sprite.set_position(100, 200);
	nexus::sprite copy(sprite);
	copy.set_position(200, 200);

	nexus::hexagon shape(50);
	shape.set_fill_color({200, 0, 0, 200});
	shape.set_outline_thickness(2);
	shape.set_outline_color({255, 255, 0, 255});
	shape.set_position(300, 200);

	while (window.is_open()) {
		window.poll_events();
		window.clear();

		window.draw(sprite);
		window.draw(copy);
		window.draw(shape);

		window.present();
	}

	return EXIT_SUCCESS;
}
