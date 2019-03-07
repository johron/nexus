#pragma once
#include "sfml/window.h"
#include "sfml/input.h"

#include "keyboard.h"

namespace nexus {
using window = sfml::window;
using keyboard = concrete_keyboard<sfml::key_code, sfml::keyboard>;
}