set(target_name "nexus-sample")

set(src_precompiled "src/precompiled.h")

set(res_files
	"resources/sprite_sheet.png")

set(src_files 
	${src_precompiled}
	"src/main.cpp")

add_executable(${target_name} WIN32 ${src_files})

target_link_libraries(${target_name} "nexus-lib")

target_include_directories(${target_name} PRIVATE "../nexus-lib/include")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

foreach(file ${res_files})
	add_custom_command(TARGET ${target_name} 
		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_SOURCE_DIR}/${file}
		${CMAKE_CURRENT_BINARY_DIR}/${file})
endforeach(file ${res_files})

				   
cotire(${target_name})