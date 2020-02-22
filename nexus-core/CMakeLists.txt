set(target_name "nexus-core")

set(src_precompiled
    "src/precompiled.h")

set(src_include
	"include/nexus/nexus-core.h")

set(src_root
	"src/dummy.cpp")

set(src_core
	"src/core/event_binding.h"
	"src/core/event_broker.h"
	"src/core/state_machine.h"
	"src/core/module_manager.h"
	"src/core/number_pool.h")

set(src_math
	"src/math/rect.h"
	"src/math/vector.h")

set(src_files
    ${src_precompiled}
	${src_root}
	${src_core}
	${src_math}
	${src_include})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\include" FILES ${src_include})
source_group("src\\math" FILES ${src_math})
source_group("src\\core" FILES ${src_core})

target_link_libraries(${target_name} PUBLIC "compiler-warnings")
target_link_libraries(${target_name} PUBLIC "code-coverage")

target_compile_features(${target_name} INTERFACE cxx_std_17)

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${target_name})