#include "nexus/nexus-lib.h"

int main(int argc, char const* argv[]) {
	auto engine = nexus::make_engine();
	auto window = nexus::window(800, 600, "sample window");

	while (engine.is_running()) {
		engine.update();
		engine.render();
	}

    return engine.shutdown();
}
