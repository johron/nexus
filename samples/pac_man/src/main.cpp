#include <nexus/nexus-gfx.h>
#include "game/game.h"

using namespace nexus;

int main(int /*argc*/, char** /*argv*/) {
	pac_man::game game;

	gfx::window main_window(800, 600);
	gfx::view view({0, 0}, {80, 60});
	main_window.set_view(view);

	while (game.is_running() && main_window.is_open()) {
		if (keyboard::is_key_down(keyboard::key::escape)) {
			main_window.close();
		}
		main_window.poll_events();
		game.update();

		main_window.clear();
		game.draw(main_window);
		main_window.present();
	}

	return 0;
}