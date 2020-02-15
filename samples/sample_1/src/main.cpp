#include <nexus/nexus-core.h>
#include <nexus/nexus-gfx.h>

using namespace nexus;

int main(int /*argc*/, char** /*argv*/) {
	window main_window(800, 600);

	auto t = std::make_unique<sprite>("res/textures/ghost_red.png");

	while (main_window.is_open()) {
		main_window.poll_events();
		t->set_position(t->get_position() + vector2f{0.02f, 0.f});
		main_window.clear();
		main_window.draw(*t);
		main_window.present();
	}

	return 0;
}