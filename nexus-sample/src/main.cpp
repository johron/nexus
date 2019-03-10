#include "nexus/nexus.h"

int main(int /*argc*/, char** /*argv*/) {
	nexus::window window(800, 600, "sample window");
	window.keyboard().bind(nexus::keyboard::key::escape, [&window]() { window.close(); });
	window.mouse().bind(nexus::mouse::button::middle, [&window](const nexus::vector2i&) { window.close(); });

	while (window.is_open()) {
		window.poll_events();
	}

	return EXIT_SUCCESS;
}
