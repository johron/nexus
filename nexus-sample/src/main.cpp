#include "nexus/nexus.h"

int main(int /*argc*/, char** /*argv*/) {
	nexus::window window(800, 600, "sample window");

	while (window.is_open()) {
		window.poll_events();
	}

	window.close();

	return EXIT_SUCCESS;
}
