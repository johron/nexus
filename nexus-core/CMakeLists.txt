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
	"src/core/module_manager.h"
	"src/core/number_pool.h"
	"src/core/time.h")

set(src_util
	"src/util/observer_ptr.h")

set(src_json
	"src/json/json.h")

set(src_math
	"src/math/rect.h"
	"src/math/vector.h")

set(src_files
    ${src_precompiled}
	${src_root}
	${src_core}
	${src_json}
	${src_math}
	${src_util}
	${src_include})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\include" FILES ${src_include})
source_group("src\\math" FILES ${src_math})
source_group("src\\core" FILES ${src_core})
source_group("src\\json" FILES ${src_json})
source_group("src\\util" FILES ${src_util})

target_link_libraries(${target_name} PUBLIC "compiler_warnings")
target_link_libraries(${target_name} PUBLIC "compiler_features")
target_link_libraries(${target_name} PUBLIC "sanitizers")

target_include_directories(${target_name} INTERFACE "${rapidjson_SOURCE_DIR}/include")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)

target_precompile_headers(${target_name} PUBLIC ${src_precompiled} PRIVATE ${common_precompiled})