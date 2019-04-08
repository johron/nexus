#include "nexus/nexus.h"

int main(int /*argc*/, char** /*argv*/) {
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
