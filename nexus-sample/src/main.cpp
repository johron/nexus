#include "nexus/nexus-lib.h"

#include <filesystem>

struct sample_app {
	sample_app(size_t count = 1) {
		for (auto i = 0; i < count; ++i) {
			m_sprites.emplace_back("resources/sprite_sheet.png");
		}
	}

	void update() {
	}

	void render(nexus::window& window) {
		for (const auto& sprite : m_sprites) {
			window.draw(sprite);
		}
	}

private:
	std::vector<nexus::sprite> m_sprites;
};

int main(int /*argc*/, char** argv) {
	std::filesystem::path current = argv[0];

	auto window = std::make_unique<nexus::window>(800, 600, "sample window");
	window->input().bind(nexus::keyboard::key::escape, [&window]() { window->close(); });

	sample_app application(1);

	while (window->is_open()) {
		window->clear();
		window->poll_events();
		application.update();
		application.render(*window);
		window->present();
	}

	window.reset();

	return EXIT_SUCCESS;
}
