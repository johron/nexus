set(target_name "nexus-lib")

set(src_precompiled
    "src/precompiled.h")

set(src_include
	"include/nexus/nexus-lib.h")

set(src_sfml_engine 
	"src/sfml/sfml_drawable.h"
	"src/sfml/sfml_keyboard.h"
	"src/sfml/sfml_mouse.h"
    "src/sfml/sfml_window.h")

set(src_engine
	"src/window.h"
	"src/engine_interface.h"
	"src/input_handler.h"
	"src/dummy.cpp")


set(src_files
    ${src_precompiled}
	${src_include}
    ${src_engine}
    ${src_sfml_engine})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\include" FILES ${src_include})
source_group("src\\engine" FILES ${src_engine})
source_group("src\\engine\\sfml" FILES ${src_sfml_engine})

target_link_libraries(${target_name} PUBLIC "compiler-warnings")
target_link_libraries(${target_name} PUBLIC "code-coverage")
target_link_libraries(${target_name} PUBLIC ${sfml_libraries})

target_compile_features(${target_name} INTERFACE cxx_std_17)

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${target_name})