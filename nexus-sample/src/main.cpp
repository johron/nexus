#include "nexus/nexus.h"

void test() {
	sf::RenderWindow win1(sf::VideoMode(800, 600), "test 1");
	sf::RenderWindow win2(sf::VideoMode(800, 600), "test 1");

	sf::CircleShape shape(50, 3);
	shape.setFillColor(sf::Color::Blue);

	while (true) {
		shape.setPosition(100, 100);
		win1.clear();
		win1.draw(shape);
		win1.display();

		shape.setPosition(100, 200);
		win2.clear();
		win2.draw(shape);
		win2.display();

		sf::Event event;
		while (win1.pollEvent(event)) {
			// ignore
		}

		while (win2.pollEvent(event)) {
			// ignore
		}
	}
}

void test2() {
	nexus::window win1(800, 600, "test 1");
	nexus::window win2(800, 600, "test 2");

	nexus::shape::triangle shape(50);
	shape.set_fill_color({0, 0, 255});

	while (true) {
		shape.set_position(100, 100);
		win1.clear();
		win1.draw(shape);
		win1.present();

		shape.set_position(100, 200);
		win2.clear();
		win2.draw(shape);
		win2.present();

		win1.poll_events();
		win2.poll_events();
	}

}

int main(int /*argc*/, char** /*argv*/) {
	test2();

	return EXIT_SUCCESS;
}
