#include "../include/nexus/nexus.h"
#include "gtest/gtest.h"

using namespace nexus;

TEST(keyboard, key_codes_are_defined) {
	[[maybe_unused]] keyboard::key key_code = keyboard::key::unknown;
	key_code = keyboard::key::a;
	key_code = keyboard::key::b;
	key_code = keyboard::key::c;
	key_code = keyboard::key::d;
	key_code = keyboard::key::e;
	key_code = keyboard::key::f;
	key_code = keyboard::key::g;
	key_code = keyboard::key::h;
	key_code = keyboard::key::i;
	key_code = keyboard::key::j;
	key_code = keyboard::key::k;
	key_code = keyboard::key::l;
	key_code = keyboard::key::m;
	key_code = keyboard::key::n;
	key_code = keyboard::key::o;
	key_code = keyboard::key::p;
	key_code = keyboard::key::q;
	key_code = keyboard::key::r;
	key_code = keyboard::key::s;
	key_code = keyboard::key::t;
	key_code = keyboard::key::u;
	key_code = keyboard::key::v;
	key_code = keyboard::key::w;
	key_code = keyboard::key::x;
	key_code = keyboard::key::y;
	key_code = keyboard::key::z;
	key_code = keyboard::key::num_0;
	key_code = keyboard::key::num_1;
	key_code = keyboard::key::num_2;
	key_code = keyboard::key::num_3;
	key_code = keyboard::key::num_4;
	key_code = keyboard::key::num_5;
	key_code = keyboard::key::num_6;
	key_code = keyboard::key::num_7;
	key_code = keyboard::key::num_8;
	key_code = keyboard::key::num_9;
	key_code = keyboard::key::escape;
	key_code = keyboard::key::l_control;
	key_code = keyboard::key::l_shift;
	key_code = keyboard::key::l_alt;
	key_code = keyboard::key::l_system;
	key_code = keyboard::key::r_control;
	key_code = keyboard::key::r_shift;
	key_code = keyboard::key::r_alt;
	key_code = keyboard::key::r_system;
	key_code = keyboard::key::menu;
	key_code = keyboard::key::l_bracket;
	key_code = keyboard::key::r_bracket;
	key_code = keyboard::key::semicolon;
	key_code = keyboard::key::comma;
	key_code = keyboard::key::period;
	key_code = keyboard::key::quote;
	key_code = keyboard::key::slash;
	key_code = keyboard::key::backslash;
	key_code = keyboard::key::tilde;
	key_code = keyboard::key::equal;
	key_code = keyboard::key::hyphen;
	key_code = keyboard::key::space;
	key_code = keyboard::key::enter;
	key_code = keyboard::key::backspace;
	key_code = keyboard::key::tab;
	key_code = keyboard::key::pageup;
	key_code = keyboard::key::pagedown;
	key_code = keyboard::key::end;
	key_code = keyboard::key::home;
	key_code = keyboard::key::insert;
	key_code = keyboard::key::del;
	key_code = keyboard::key::add;
	key_code = keyboard::key::subtract;
	key_code = keyboard::key::multiply;
	key_code = keyboard::key::divide;
	key_code = keyboard::key::arrow_left;
	key_code = keyboard::key::arrow_right;
	key_code = keyboard::key::arrow_up;
	key_code = keyboard::key::arrow_down;
	key_code = keyboard::key::numpad_0;
	key_code = keyboard::key::numpad_1;
	key_code = keyboard::key::numpad_2;
	key_code = keyboard::key::numpad_3;
	key_code = keyboard::key::numpad_4;
	key_code = keyboard::key::numpad_5;
	key_code = keyboard::key::numpad_6;
	key_code = keyboard::key::numpad_7;
	key_code = keyboard::key::numpad_8;
	key_code = keyboard::key::numpad_9;
	key_code = keyboard::key::f1;
	key_code = keyboard::key::f2;
	key_code = keyboard::key::f3;
	key_code = keyboard::key::f4;
	key_code = keyboard::key::f5;
	key_code = keyboard::key::f6;
	key_code = keyboard::key::f7;
	key_code = keyboard::key::f8;
	key_code = keyboard::key::f9;
	key_code = keyboard::key::f10;
	key_code = keyboard::key::f11;
	key_code = keyboard::key::f12;
	key_code = keyboard::key::f13;
	key_code = keyboard::key::f14;
	key_code = keyboard::key::f15;
	key_code = keyboard::key::pause;
	static_assert(static_cast<int>(keyboard::key::__key_count__) == 101);
}

TEST(keyboard, is_key_down) {
#ifndef __GNUC__ // for some reason causes an exception on Linux, should be debugged properly
	EXPECT_FALSE(keyboard::is_key_down(keyboard::key::a));
#endif
}