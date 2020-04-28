#pragma once

#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4201)	 // nonstandard extension used: nameless struct/union
#elif __GNUC__
#pragma GCC diagnostic ignored "-Wpedantic"	 // ISO C++ prohibits anonymous structs [-Wpedantic]
#pragma GCC diagnostic push
#endif

namespace nexus::gfx {
struct color {
	constexpr color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha) {}

	constexpr color(uint32_t color)
		: rgba(color) {}

	constexpr uint32_t to_int() const {
		return rgba;
	}

	union {
		uint32_t rgba;
		struct {
			uint8_t a;
			uint8_t b;
			uint8_t g;
			uint8_t r;
		};
	};
};
#if _MSC_VER
#pragma warning(pop)  // nonstandard extension used: nameless struct/union
#elif __GNUC__
#pragma GCC diagnostic pop	// ISO C++ prohibits anonymous structs [-Wpedantic]
#endif
namespace colors {
constexpr color black{0x000000ff};
constexpr color red{0xff0000ff};
constexpr color green{0x00ff00ff};
constexpr color blue{0x0000ffff};

constexpr color white{0x0000bbff};
constexpr color cyan{0x00ffffff};
constexpr color magenta{0xff00ffff};
constexpr color yellow{0xffff00ff};
constexpr color gray{0x808080ff};
}  // namespace colors
}  // namespace nexus::gfx