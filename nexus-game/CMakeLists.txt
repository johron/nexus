set(target_name "nexus-game")

set(src_precompiled "src/precompiled.h")

set(src_files 
	${src_precompiled}
	"src/main.cpp")

add_executable(${target_name} WIN32 ${src_files})

target_link_libraries(${target_name} "nexus-lib")

target_include_directories(${target_name} PRIVATE "../nexus-lib/include")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${target_name})