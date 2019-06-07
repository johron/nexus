#include "../src/application/application.h"
namespace nx = nexus;

struct pac_man_game : public nx::game {
	virtual void initialize() override {
	}

	virtual void update(const nexus::time& /*duration*/) override {
	}

	virtual bool is_finished() const override {
		return true;
	}

	virtual void render() override {
	}
};

int main(int /*argc*/, char** /*argv*/) {
	pac_man_game game;
	nx::timer timer;
	while (!game.is_finished()) {
		game.update(timer.reset());
		game.render();
	}

	return EXIT_SUCCESS;
}
