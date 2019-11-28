set(target_name "nexus-game")

set(src_precompiled "src/precompiled.h")

set(src_shared
	"src/shared/game.h")

set(src_model
	"src/game/model/board.h"
	"src/game/model/item.h")

set(src_view
	"src/game/view/board.h"
	"src/game/view/item.h")

set(src_game
	"src/game/game.h")

set(src_main
	"src/main.cpp")

set(src_files 
	${src_precompiled}
	${src_model}
	${src_view}
	${src_game}
	${src_shared}
	${src_main})

add_executable(${target_name} WIN32 ${src_files} ${res_files})

source_group("src\\game" FILES ${src_game})
source_group("src\\game\\model" FILES ${src_model})
source_group("src\\game\\view" FILES ${src_view})
source_group("src\\main" FILES ${src_main})
source_group("src\\shared" FILES ${src_shared})

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