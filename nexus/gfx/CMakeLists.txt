set(target_name "nexus-gfx")

set(src_precompiled
    "src/precompiled.h")

set(src_include
	"include/nexus/nexus-gfx.h"
	"include/nexus/nexus-sfml.h")

set(src_dummy
	"src/dummy.cpp")

set(src_gfx
	"src/gfx/color.h"
	"src/gfx/sprite_animation.h")

set(src_sfml
	"src/sfml/blend_mode.h"
	"src/sfml/drawable.h"
	"src/sfml/keyboard.h"
	"src/sfml/image.h"
	"src/sfml/mouse.h"
	"src/sfml/shapes.h"
	"src/sfml/sprite.h"
	"src/sfml/texture.h"
	"src/sfml/util.h"
	"src/sfml/view.h"
	"src/sfml/window.h")

set(src_util
	"src/util/performance_monitor.h")

set(src_files
    ${src_precompiled}
	${src_sfml}
	${src_gfx}
	${src_util}
	${src_dummy}
	${src_include})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\include" FILES ${src_include})
source_group("src\\gfx" FILES ${src_gfx})
source_group("src\\sfml" FILES ${src_sfml})
source_group("src\\util" FILES ${src_util})

target_link_libraries(${target_name} PUBLIC "compiler_warnings")
target_link_libraries(${target_name} PUBLIC "compiler_features")
target_link_libraries(${target_name} PUBLIC "sanitizers")
target_link_libraries(${target_name} PUBLIC CONAN_PKG::imgui-sfml)

target_include_directories(${target_name} PUBLIC "../core/include/")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)

target_precompile_headers(${target_name} PUBLIC ${src_precompiled} PRIVATE ${common_precompiled})