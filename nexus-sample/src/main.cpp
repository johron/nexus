#include "nexus/nexus-lib.h"

struct sample_app {
	sample_app() {
	
	}

	void update() {
	
	}

	void render(nexus::window& /*window*/) {
		//window.draw()
	}

private:
	std::unique_ptr<nexus::sprite> m_sprite;

};

int main(int /*argc*/, char const* /*argv[]*/) {
	auto window = std::make_unique<nexus::window>(800, 600, "sample window");
	window->input().bind(nexus::keyboard::key::escape, [&window]() { window->close(); });

	while (window->is_open()) {
		window->clear();
		window->poll_events();
		// game update + rendering
		window->present();
	}

	window.reset();

	return EXIT_SUCCESS;
}
