#pragma once

#include "../../src/engine_interface.h"
#include "../../src/input_handler.h"
#include "../../src/precompiled.h"

#define IMPLEMENTATION_SFML

#ifdef IMPLEMENTATION_SFML
#define IMPL sfml

#include "../../src/sfml/sfml_window.h"
#include "../../src/sfml/sfml_keyboard.h"

#endif

namespace nexus {
using window = IMPL::window;
using keyboard = IMPL::keyboard;
}