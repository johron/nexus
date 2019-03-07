#pragma once
#include "sfml/window.h"
#include "sfml/keyboard.h"

#include "keyboard.h"
#include "event_binding.h"

namespace nexus {
using window = sfml::window;
using keyboard = concrete_keyboard<sfml::key_code, sfml::keyboard>;
using input_binding = event_binding<sfml::key_code, std::function<void()>>;
}