#pragma once

namespace nexus {
struct module {
	virtual ~module() = default;
	virtual void update() {
	}
};
}  // namespace nexus