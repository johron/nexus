#pragma once

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

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic push
#endif

#include "SFML/Graphics.hpp"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#include "sfml/util.h"
#include "util/type_id.h"