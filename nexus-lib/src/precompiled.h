#pragma once

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic push
#endif
#include "imgui.h"
#include "sfml/imgui/imgui-SFML.h"
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include <cassert>
#include <cstdint>

#include <limits>
#include <atomic>
#include <memory>
#include <functional>
#include <type_traits>

#include <map>
#include <set>
#include <any>

#include <string>

#include "sfml/precompiled.h"
#include "engine/precompiled.h"