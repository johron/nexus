#include "nexus/nexus-lib.h"

int main(int /*argc*/, char const* /*argv[]*/) {
	auto window = nexus::make_window(800, 600, "sample window");
	window->input().bind(nexus::key::Escape, [&window]() { window->close(); });

	while (window->is_open()) {
		window->update();
		window->render();
	}

	window.reset();

	return EXIT_SUCCESS;
}
