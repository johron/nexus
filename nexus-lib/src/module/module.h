#pragma once

namespace nexus {
struct module {
	virtual ~module() = default;
	virtual void update() {
	}
	virtual void render() {
	}
};

namespace module_visitor {
static const auto update = [](auto& module) { module.update(); };
static const auto render = [](auto& module) { module.render(); };
}  // namespace module_visitor
}  // namespace nexus