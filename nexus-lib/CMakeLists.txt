set(target_name "nexus-lib")

set(src_precompiled
    "src/precompiled.h")

set(src_include
	"include/nexus/nexus.h")

set(src_math
	"src/math/vector.h")

set(src_mock
	"src/mock/window.h")

set(src_module
	"src/module/module.h"
	"src/module/module_dependency.h"
	"src/module/module_manager.h")

set(src_sfml
	"src/sfml/util.h"
	"src/sfml/drawable.h"
	"src/sfml/events.h"
	"src/sfml/mouse.h"
	"src/sfml/keyboard.h"
	"src/sfml/shapes.h"
	"src/sfml/sprite.h"
	"src/sfml/texture.h"
	"src/sfml/window.h")

set(src_engine
	"src/engine.h"
	"src/event_binding.h"
	"src/input_device.h"
	"src/resource_cache.h"
	"src/dummy.cpp")

set(src_events
	"src/events/event_dispatcher.h"
	"src/events/event_listener.h")

set(src_utils
	"src/utils/type_id.cpp"
	"src/utils/type_id.h")

set(src_files
    ${src_precompiled}
	${src_include}
    ${src_engine}
	${src_events}
	${src_mock}
	${src_module}
	${src_sfml}
	${src_math}
	${src_utils})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\include" FILES ${src_include})
source_group("src\\engine" FILES ${src_engine})
source_group("src\\engine\\sfml" FILES ${src_sfml})
source_group("src\\engine\\mock" FILES ${src_mock})
source_group("src\\events" FILES ${src_events})
source_group("src\\math" FILES ${src_math})
source_group("src\\module" FILES ${src_module})
source_group("src\\utils" FILES ${src_utils})

target_link_libraries(${target_name} PUBLIC "compiler-warnings")
target_link_libraries(${target_name} PUBLIC "code-coverage")
target_link_libraries(${target_name} PUBLIC ${sfml_libraries})

target_compile_features(${target_name} INTERFACE cxx_std_17)

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${target_name})