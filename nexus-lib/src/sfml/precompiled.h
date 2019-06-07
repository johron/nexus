#pragma once

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic push
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4457)  // imgui-SFML.cpp(384): warning C4457: declaration of 'mousePos' hides
								 // function parameter
#pragma warning(push)
#endif

#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include "util.h"