#include "nexus/nexus-lib.h"

int main(int /*argc*/, char const* /*argv[]*/) {
	auto engine = nexus::make_engine(800, 600, "sample");

	while (engine->is_running()) {
		engine->update();
		engine->render();
	}

	engine.reset();

	return EXIT_SUCCESS;
}
