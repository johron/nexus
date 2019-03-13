#include "nexus/nexus.h"

int main(int /*argc*/, char** /*argv*/) {
	nexus::window window(800, 600, "sample window");
	window.keyboard().bind(nexus::keyboard::key::escape, [&window]() { window.close(); });

	while (window.is_open()) {
		window.poll_events();
		window.clear();
		window.present();
	}

	return EXIT_SUCCESS;
}
