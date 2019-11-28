#pragma once
#include "../shared/game.h"
#include "view/board.h"
#include "model/board.h"

namespace match_game {
struct game : public sample::game {
	game()
		: m_window(800, 600, "sample game") 
		, m_model(std::make_unique<model::board>(8, 8)) 
		, m_view(std::make_unique<view::board>(*m_model)) {

		m_window.keyboard().bind(nx::keyboard::key::escape, [this]() { m_window.close(); });
	}

	~game() = default;

	virtual void update(nexus::time&& delta_time) override {
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
	std::unique_ptr<model::board> m_model;
	std::unique_ptr<view::board> m_view;
};
}  // namespace pac_man
