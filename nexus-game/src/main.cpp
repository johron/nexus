#include "pac_man/game.h"

auto make_game() {
	return std::make_unique<pac_man::game>();
}

int main(int /*argc*/, char** /*argv*/) {
	auto game = make_game();

	while (game->is_running()) {
		game->update();
		game->render();
	}

	return EXIT_SUCCESS;
}
