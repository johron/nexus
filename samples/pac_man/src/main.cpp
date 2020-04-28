#include <nexus/nexus-gfx.h>

#include "game/game.h"
#include "game/sprite_sheet.h"

using namespace nexus;
using namespace std::chrono_literals;

int main(int /*argc*/, char** /*argv*/) {
	pac_man::entity_factory entity_factory(pac_man::sprite_sheet("res/textures/pac_man.png"));
	pac_man::maze_factory maze_factory(entity_factory);
	pac_man::game game(maze_factory);

	gfx::window main_window(800, 600, "pac man");
	gfx::view view({-20, -20}, {800, 600});
	main_window.set_view(view);

	nexus::timer timer;
	while (game.is_running() && main_window.is_open()) {
		if (keyboard::is_key_down(keyboard::key::escape)) {
			main_window.close();
		}
		const auto delta_time = timer.reset();
		main_window.update(delta_time);
		game.update(delta_time);

		main_window.clear();
		game.draw(main_window);

		main_window.present();
	}

	return 0;
}