#include <nexus/nexus-gfx.h>

using namespace nexus;

int main(int /*argc*/, char** /*argv*/) {
	gfx::window main_window(800, 600);

	auto t1 = std::make_unique<gfx::sprite>("res/textures/ghost_red.png");
	auto t2 = std::make_unique<gfx::triangle>(16.f);
	t2->set_fill_color(gfx::color{150, 0, 0});

	gfx::view view({0, 0}, {80, 60});
	main_window.set_view(view);


	while (main_window.is_open()) {
		if (keyboard::is_key_down(keyboard::key::escape)) {
			main_window.close();
		}
		main_window.poll_events();

		if (mouse::is_button_down(mouse::button::left)) {
			t1->set_position(t1->get_position() + vector2f{0.02f, 0.f});
		}

		main_window.clear();
		main_window.draw(*t1);
		main_window.draw(*t2);
		main_window.present();
	}

	return 0;
}