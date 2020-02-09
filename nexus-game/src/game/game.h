#pragma once
#include "../shared/game.h"
#include "view/board.h"
#include "model/board.h"

namespace match_game {
struct game : public sample::game {
	game()
		: m_window(800, 600, "sample game") {
		//m_window.keyboard().bind(nx::keyboard::key::escape, [this]() { m_window.close(); });
	}

	~game() = default;

	virtual void update(const nexus::time& delta_time) override {
		m_window.poll_events();
	}

	virtual void render() override {
		m_window.clear();
		m_window.present();
	}

	virtual bool is_running() const override {
		return m_window.is_open();
	}

	nx::window m_window;
	nx::keyboard m_keyboard;
};
}  // namespace pac_man
