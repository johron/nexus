#include "../src/application/application.h"
namespace nx = nexus;

struct lost_cities : public nx::game {
	virtual void initialize() override {
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void update(const nexus::time& duration) override {
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual bool is_finished() const override {
		throw std::logic_error("The method or operation is not implemented.");
	}

	virtual void render() override {
		throw std::logic_error("The method or operation is not implemented.");
	}
};

int main(int /*argc*/, char** /*argv*/) {
	lost_cities game;
	nx::timer timer;
	while (!game.is_finished()) {
		game.update(timer.reset());
		game.render();
	}

	return EXIT_SUCCESS;
}
