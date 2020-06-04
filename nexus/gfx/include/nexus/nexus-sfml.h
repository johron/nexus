#pragma once
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic push
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#pragma warning(push)
#endif

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif

#include "../../src/sfml/blend_mode.h"
#include "../../src/sfml/window.h"
#include "../../src/sfml/sprite.h"
#include "../../src/sfml/shapes.h"
#include "../../src/sfml/texture.h"
#include "../../src/sfml/image.h"
#include "../../src/sfml/line.h"

#include "../../src/sfml/keyboard.h"
#include "../../src/sfml/mouse.h"
