#pragma once
#include "../shared/game.h"
#include "world_model.h"
#include "world_view.h"

namespace pac_man {
struct game : public sample::game {
	game()
		: m_window(800, 600, "sample game") {
		m_window.keyboard().bind(nx::keyboard::key::escape, [this]() { m_window.close(); });
	}

	~game() {
	}

	virtual void update(nexus::time&& delta_time) override {
		m_window.update(delta_time);
		m_window.poll_events();
	}

	virtual void render() override {
		m_window.clear();
		m_view->render(m_window);

		ImGui::Begin("test");
		ImGui::Button("button");
		ImGui::End();

		m_window.present();
	}

	virtual bool is_running() const override {
		return m_window.is_open();
	}

	nx::window m_window;
	std::unique_ptr<world_view> m_view;
	std::unique_ptr<world_model> m_model;
};
}  // namespace pac_man
