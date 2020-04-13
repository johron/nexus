#pragma once
#include <deque>
#include <thread>
using namespace std::chrono_literals;

struct performance_view {
	performance_view()
		: m_frames{100, frame_data{0}} 
		, m_enabled(true) {}

	struct frame_data {
		nexus::duration m_duration;
	};

	void update(const nexus::duration& duration) {
		if (m_enabled) {
			m_frames.push_front(frame_data{duration});
			while (m_frames.size() > 100) {
				m_frames.pop_back();
			}
		}
	}

	void draw() {

		ImGui::Begin("performance view");
		ImGui::PlotHistogram("",
							 [](void* data, int index) {
								 const auto& frames = *static_cast<std::deque<frame_data>*>(data);
								 return frames[index].m_duration.to_seconds();
								 ;
							 },
							 &m_frames,
							 static_cast<int>(m_frames.size()),
							 0,
							 "frame time",
							 0,
							 0.150f,
							 {500, 200});
		if (ImGui::Button("toggle recording")) {
			m_enabled = !m_enabled;
		}
		const auto fps = 1.0f / m_frames.front().m_duration.to_seconds();
		ImGui::Text(("fps:" + std::to_string(static_cast<int>(fps))).c_str());
		ImGui::End();
	}

	bool m_enabled;
	std::deque<frame_data> m_frames;
};