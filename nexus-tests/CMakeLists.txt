set(target_name "nexus-tests")

set(res_files
	"res/default.png")

set(src_precompiled
	"src/precompiled.h")

set(src_math
	"src/math/vector.cpp")

set(src_module
	"src/module/module.cpp")

set(src_engine
	"src/engine/event_binding.cpp"
	"src/engine/resource_cache.cpp"
	"src/engine/keyboard.cpp"
	"src/engine/window.cpp")

set(src_events
	"src/events/event_broadcaster.cpp")

set(src_utils
	"src/utils/number_pool.cpp"
	"src/utils/type_id.cpp")

set(src_files 
	${src_precompiled}
	${src_engine}
	${src_events}
	${src_math}
	${src_module}
	${src_utils})

add_executable(${target_name} ${src_files} ${res_files})

source_group("src\\engine" FILES ${src_engine})
source_group("src\\events" FILES ${src_events})
source_group("src\\math" FILES ${src_math})
source_group("src\\module" FILES ${src_module})
source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\utils" FILES ${src_utils})
source_group("res" FILES ${res_files})

target_link_libraries(${target_name} "nexus-lib")
target_link_libraries(${target_name} "gtest_main")

target_include_directories(${target_name} PRIVATE "../nexus-lib/include")
target_include_directories(${target_name} PRIVATE "../../")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

foreach(file ${res_files})
	add_custom_command(TARGET ${target_name} 
		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_SOURCE_DIR}/${file}
		${CMAKE_CURRENT_BINARY_DIR}/${file})
endforeach(file ${res_files})

gtest_discover_tests(${target_name})
cotire(${target_name})