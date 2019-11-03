message("-- External Project: sfml")
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "TRUE to build SFML's Audio module." FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "TRUE to build SFML libs ass DLL's" FORCE)

FetchContent_MakeAvailable(sfml)

set(sfml_libraries "sfml-graphics" "sfml-network" "sfml-system" "sfml-window")

if (WIN32)
    list(APPEND sfml_libraries "sfml-main")
endif(WIN32)

foreach(library ${sfml_libraries})
    set_target_properties(${library} PROPERTIES FOLDER "third_party/sfml")
endforeach(library)