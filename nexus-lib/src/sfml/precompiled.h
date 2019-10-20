#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic push
#elif defined(_MSC_VER)
#pragma warning (disable: 4996)
#pragma warning (push)
#endif

#include "SFML/Graphics.hpp"

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#pragma warning (pop)
#endif

#include "util.h"