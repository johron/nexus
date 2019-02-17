#include "nexus/nexus-lib.h"
#include "pac_man/maze.h"

int main(int /*argc*/, char ** /*argv*/) {
	auto window = std::make_unique<nexus::window>(800, 800, "sample: pac man");
	window->input().bind(nexus::keyboard::key::escape, [&window]() { window->close(); });

	game::maze game;

	while (window->is_open()) {
		window->clear();
		window->poll_events();
		game.update();
		game.render(*window);
		window->present();
	}

	return EXIT_SUCCESS;
}
