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

#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic push
#include "SFML/Graphics.hpp"
#pragma GCC diagnostic pop

#include "sfml/util.h"
#include "util/type_id.h"