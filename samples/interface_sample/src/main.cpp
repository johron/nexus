#include <nexus/nexus-gfx.h>
#include "view/node_editor.h"

using namespace nexus;

int main(int /*argc*/, char** /*argv*/) {
	gfx::window main_window(800, 600);

	auto t1 = std::make_unique<gfx::image>("res/textures/sprite_sheet.png");
	auto t2 = std::make_unique<gfx::texture>(*t1, recti{6, 125, 22, 22});
	auto t3 = std::make_unique<gfx::sprite>(std::move(t2));
	auto t4 = std::make_unique<gfx::triangle>(16.f);
	t4->set_fill_color(gfx::color{150, 0, 0});

	gfx::view view({0, 0}, {160, 120});
	main_window.set_view(view);

	node_editor editor;
	gfx::performance_monitor perf_view;

	timer main_timer;
	while (main_window.is_open()) {
		if (keyboard::is_key_down(keyboard::key::escape)) {
			main_window.close();
		}

		std::this_thread::sleep_for(6ms);

		const auto delta_time = main_timer.reset();
		main_window.update(delta_time);
		main_window.clear();

		perf_view.update(delta_time);
		perf_view.draw();

		editor.draw();

		main_window.present();
	}

	return 0;
}