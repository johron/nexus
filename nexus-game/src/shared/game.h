#pragma once
#include "nexus/nexus.h"

namespace nx = nexus;
namespace sample {
struct game {
	virtual ~game() = default;
	virtual void update(const nexus::time& delta_time) = 0;
	virtual void render() = 0;
	virtual bool is_running() const = 0;
};

}  // namespace sample