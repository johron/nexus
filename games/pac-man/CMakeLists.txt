set(target_name "pac-man")

set(src_precompiled "src/precompiled.h")

set(src_game
	"src/game.h")

set(src_model
	"src/model/world.h")

set(src_view
	"src/view/world.h")

set(src_main
	"src/main.cpp")

set(src_files 
	${src_precompiled}
	${src_model}
	${src_view}
	${src_game}
	${src_main})

add_executable(${target_name} WIN32 ${src_files} ${res_files})

source_group("src\\pac_man" FILES ${src_game})
source_group("src\\pac_man\\model" FILES ${src_model})
source_group("src\\pac_man\\view" FILES ${src_view})
source_group("src\\main" FILES ${src_main})


target_link_libraries(${target_name} "nexus-lib")

target_include_directories(${target_name} PRIVATE "../../nexus-lib/include")

set_target_properties(${target_name} PROPERTIES FOLDER "games")
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

foreach(file ${res_files})
	add_custom_command(TARGET ${target_name} 
		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_SOURCE_DIR}/${file}
		${CMAKE_CURRENT_BINARY_DIR}/${file})
endforeach(file ${res_files})

cotire(${target_name})