#include "nexus/nexus-lib.h"

int main(int /*argc*/, char const* /*argv[]*/) {
	auto window = nexus::make_window(800, 600, "sample window");
	window->input().bind(nexus::keyboard::key::escape, [&window]() { window->close(); });

	while (window->is_open()) {
		window->clear();
		window->update();
		// game update + rendering
		window->present();
	}

	window.reset();

	return EXIT_SUCCESS;
}
