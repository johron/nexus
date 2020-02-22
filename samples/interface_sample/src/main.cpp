#include <nexus/nexus-gfx.h>

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


	while (main_window.is_open()) {
		if (keyboard::is_key_down(keyboard::key::escape)) {
			main_window.close();
		}
		main_window.poll_events();

		if (mouse::is_button_down(mouse::button::left)) {
			t3->set_position(t3->get_position() + vector2f{0.02f, 0.f});
		}

		main_window.clear();
		main_window.draw(*t3);
		main_window.draw(*t4);
		main_window.present();
	}

	return 0;
}