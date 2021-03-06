#include "game/game.h"

auto make_game() {
	return std::make_unique<match_game::game>();
}

int main(int /*argc*/, char** /*argv*/) {
	auto game = make_game();

	nexus::timer timer;
	while (game->is_running()) {
		game->update(timer.reset());
		game->render();
	}

	return EXIT_SUCCESS;
}

// dummy change
