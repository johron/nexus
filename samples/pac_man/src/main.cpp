#include <nexus/nexus-gfx.h>

#include "game/game.h"
#include "util/sprite_sheet.h"

using namespace nexus;
using namespace std::chrono_literals;

int main(int /*argc*/, char** /*argv*/) {
	pac_man::game game;

	gfx::window main_window(800, 600, "pac man");
	gfx::view view({-20, -20}, {800, 600});
	main_window.set_view(view);

	pac_man::util::sprite_sheet sprites("res/textures/pac_man.png");

	std::vector<std::shared_ptr<nexus::gfx::sprite_animation>> anims{
		sprites.make_animation(pac_man::data::entity::clyde, pac_man::direction::right),
		sprites.make_animation(pac_man::data::entity::clyde, pac_man::direction::left),
		sprites.make_animation(pac_man::data::entity::clyde, pac_man::direction::up),
		sprites.make_animation(pac_man::data::entity::clyde, pac_man::direction::down), 
		sprites.make_animation(pac_man::data::entity::pinky, pac_man::direction::right),
		sprites.make_animation(pac_man::data::entity::pinky, pac_man::direction::left),
		sprites.make_animation(pac_man::data::entity::pinky, pac_man::direction::up),
		sprites.make_animation(pac_man::data::entity::pinky, pac_man::direction::down), 
		sprites.make_animation(pac_man::data::entity::player, pac_man::direction::right),
		sprites.make_animation(pac_man::data::entity::player, pac_man::direction::left),
		sprites.make_animation(pac_man::data::entity::player, pac_man::direction::up),
		sprites.make_animation(pac_man::data::entity::player, pac_man::direction::down)};

	nexus::vector2f pos(0, 0);
	for (auto& anim : anims) {
		anim->set_position(pos);
		pos.x += 23.f;
	}

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