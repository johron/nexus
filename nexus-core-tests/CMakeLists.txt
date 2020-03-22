set(target_name "nexus-core-tests")

set(src_precompiled
	"src/precompiled.h")

set(src_math
	"src/math/rect.cpp"
	"src/math/vector.cpp")

set(src_core
	"src/core/module_manager.cpp"
	"src/core/number_pool.cpp"
	"src/core/event_binding.cpp"
	"src/core/event_broker.cpp")

set(src_util
	"src/util/observer_ptr.cpp")

set(src_files 
	${src_precompiled}
	${src_core}
	${src_math}
	${src_util})

add_executable(${target_name} ${src_files} ${res_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\core" FILES ${src_core})
source_group("src\\math" FILES ${src_math})
source_group("src\\util" FILES ${src_util})
source_group("res" FILES ${res_files})

target_link_libraries(${target_name} "nexus-core")
target_link_libraries(${target_name} CONAN_PKG::gtest)

target_include_directories(${target_name} PRIVATE "../nexus-core/include")
target_include_directories(${target_name} PRIVATE "../../")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")

target_precompile_headers(${target_name} PUBLIC ${src_precompiled} PRIVATE ${common_precompiled})

#foreach(file ${res_files})
#	add_custom_command(TARGET ${target_name} 
#		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
#		${CMAKE_CURRENT_SOURCE_DIR}/${file}
#		${CMAKE_CURRENT_BINARY_DIR}/${file})
#endforeach(file ${res_files})

include(GoogleTest)
gtest_discover_tests(${target_name})
