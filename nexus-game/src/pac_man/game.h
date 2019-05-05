#pragma once
#include "../shared/game.h"
#include "world_definition.h"
#include "world_model.h"
#include "world_view.h"

namespace pac_man {
struct game : public sample::game {
	game()
		: m_window(1024, 1024, "sample game")
		, m_model(model::get_default_world())
		, m_view(std::make_unique<view::world>(*m_model)) {
		m_window.keyboard().bind(nx::keyboard::key::escape, [this]() { m_window.close(); });
	}

	virtual void update(nx::time&& delta_time) override {
		m_model->update(delta_time);
		m_window.update(delta_time);
		m_window.poll_events();
	}

	virtual void render() override {
		m_window.clear();
		m_view->render(m_window);
		m_window.present();
	}

	virtual bool is_running() const override {
		return m_window.is_open();
	}

	nx::window m_window;
	std::unique_ptr<model::world> m_model;
	std::unique_ptr<view::world> m_view;
};
}  // namespace pac_man
