#include "nexus/nexus.h"

void test2() {
	nexus::window win1(800, 600, "test 1");
	win1.set_position(100, 100);
	nexus::window win2(800, 600, "test 2");
	win2.set_position(950, 100);

	nexus::shape::triangle shape(50);
	shape.set_fill_color({0, 0, 255});
	shape.set_outline_color({120, 120, 0});
	shape.set_outline_thickness(1);

	nexus::view view(nexus::vector2f{200, 200}, nexus::vector2f{300, 200});
	win1.set_view(view);

	auto lastFramTime = std::chrono::steady_clock::now();
	while (true) {
		view.rotate(0.5f);
		win1.set_view(view);
		win1.clear();
		win2.clear();
		nexus::vector2f origin(50, 80);
		for (int y = 0; y < 5; ++y) {
			for (int x = 0; x < 7; ++x) {
				shape.set_position(origin + nexus::vector2f(x * 100, y * 100));
				win1.draw(shape);
				win2.draw(shape);
			}
		}
		win1.present();
		win2.present();

		win1.poll_events();
		win2.poll_events();
	}
}

int main(int /*argc*/, char** /*argv*/) {
	test2();

	return EXIT_SUCCESS;
}
