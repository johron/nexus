#pragma once
#include "../time.h"

namespace nexus {
struct simulation {
	virtual void initialize() = 0;
	virtual void update(const nexus::time& duration) = 0;
	virtual bool is_finished() const = 0;
};

struct renderable {
	virtual void render() = 0;
};

struct game : public simulation, public renderable {

};

}  // namespace nexus