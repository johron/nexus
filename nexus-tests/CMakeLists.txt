set(target_name "nexus-tests")

set(src_precompiled
	"src/precompiled.h")

set(src_math
	"src/math/vector.cpp")

set(src_files 
	${src_math})

add_executable(${target_name} ${src_files})

source_group("src\\math" FILES ${src_math})

target_link_libraries(${target_name} "nexus-lib")
target_link_libraries(${target_name} "gtest_main")

target_include_directories(${target_name} PRIVATE "../nexus-lib/include")
target_include_directories(${target_name} PRIVATE "../../")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")

set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

gtest_discover_tests(${target_name})

cotire(${target_name})