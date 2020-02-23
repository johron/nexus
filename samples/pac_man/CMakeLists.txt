set(target_name "pac_man")

set(src_precompiled
    "src/precompiled.h")

set(src_root
	"src/main.cpp")

set(src_game
	"src/game/entity.h"
	"src/game/entity_factory.h"
    "src/game/game.h"
	"src/game/game.cpp"
	"src/game/game_data.h"
	"src/game/player.h")

set(src_util
	"src/util/animation.h")

set(res_textures
	"res/textures/pac_man.png"
	"res/textures/sprite_sheet.png")

set(res_files
	${res_textures})

set(src_files
    ${src_precompiled}
	${src_root}
	${src_game}
	${src_util}
	${res_textures})

add_executable(${target_name} WIN32 ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src" FILES ${src_root})
source_group("src\\game" FILES ${src_game})
source_group("src\\util" FILES ${src_util})
source_group("res\\textures" FILES ${res_textures})

target_link_libraries(${target_name} PUBLIC "compiler-warnings")
target_link_libraries(${target_name} PUBLIC "code-coverage")
target_link_libraries(${target_name} PUBLIC "nexus-core")
target_link_libraries(${target_name} PUBLIC "nexus-gfx")

target_compile_features(${target_name} INTERFACE cxx_std_17)

target_include_directories(${target_name} PRIVATE "../../nexus-core/include")
target_include_directories(${target_name} PRIVATE "../../nexus-gfx/include")

set_target_properties(${target_name} PROPERTIES FOLDER "sample")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

foreach(file ${res_files})
	add_custom_command(TARGET ${target_name} 
		POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_SOURCE_DIR}/${file}
		${CMAKE_CURRENT_BINARY_DIR}/${file})
endforeach(file ${res_files})

cotire(${target_name})