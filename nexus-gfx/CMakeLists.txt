set(target_name "nexus-gfx")

set(src_precompiled
    "src/precompiled.h")

set(src_include
	"include/nexus/nexus-gfx.h"
	"include/nexus/nexus-sfml.h")

set(src_dummy
	"src/dummy.cpp")

set(src_sfml
	"src/sfml/drawable.h"
	"src/sfml/input_device.h"
	"src/sfml/keyboard.h"
	"src/sfml/mouse.h"
	"src/sfml/shapes.h"
	"src/sfml/sprite.h"
	"src/sfml/texture.h"
	"src/sfml/util.h"
	"src/sfml/view.h"
	"src/sfml/window.h"
	"src/sfml/gfx_sfml.h")

set(src_files
    ${src_precompiled}
	${src_sfml}
	${src_dummy}
	${src_include})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\include" FILES ${src_include})
source_group("src\\sfml" FILES ${src_sfml})

target_link_libraries(${target_name} PUBLIC "compiler-warnings")
target_link_libraries(${target_name} PUBLIC "code-coverage")
target_link_libraries(${target_name} PUBLIC ${sfml_libs})

target_compile_features(${target_name} INTERFACE cxx_std_17)

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${target_name})