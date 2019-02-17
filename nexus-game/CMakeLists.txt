set(target_name "nexus-game")

include("resources/pac_man.cmake")

set(res_files
	${res_player}
	${res_avoid}
	${res_blinky})

set(src_precompiled "src/precompiled.h")

set(src_game
	"src/pac_man/maze.h"
	"src/pac_man/player.h"
	"src/pac_man/ghost.h")

set(src_files 
	${src_precompiled}
	${src_game}
	"src/main.cpp")

add_executable(${target_name} WIN32 ${src_files} ${res_files})

source_group("src\\pac_man" FILES ${src_game})

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