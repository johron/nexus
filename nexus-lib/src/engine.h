#pragma once
#include "sfml/mouse.h"
#include "sfml/keyboard.h"
#include "sfml/window.h"
#include "sfml/sprite.h"
#include "sfml/shapes.h"

#include "event_binding.h"
#include "input_device.h"

namespace nexus {
using keyboard = concrete_keyboard<sfml::keyboard::key, sfml::keyboard>;
using mouse = concrete_mouse<sfml::mouse::button, sfml::mouse>;

using window = sfml::window<keyboard, mouse>;

using sprite = sfml::sprite;
using circle = sfml::circle;
using triangle = sfml::triangle;
using hexagon = sfml::hexagon;
using rect = sfml::rect;

}  // namespace nexus