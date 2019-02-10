set(external_project "sfml")
message("-- External Project: ${external_project}")
set(EXTERNAL_PROJECT_FILE "cmake/${external_project}.cmake.in")

set(EXTERNAL_PROJECT_DIR ${PROJECT_BINARY_DIR}/third_party/${external_project}/download)
configure_file(${EXTERNAL_PROJECT_FILE} ${EXTERNAL_PROJECT_DIR}/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${EXTERNAL_PROJECT_DIR}
        OUTPUT_FILE ${EXTERNAL_PROJECT_DIR}/download-log.txt)
if(result)
    message(FATAL_ERROR "${external_project} download failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${EXTERNAL_PROJECT_DIR}
    OUTPUT_FILE ${EXTERNAL_PROJECT_DIR}/build-log.txt)
if(result)
    message(FATAL_ERROR "Build step for ${external_project} failed: ${result}")
endif()

set(SFML_BUILD_AUDIO OFF CACHE BOOL "TRUE to build SFML's Audio module." FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "TRUE to build SFML libs ass DLL's" FORCE)

add_subdirectory(${PROJECT_BINARY_DIR}/third_party/${external_project}/src)

set(used-libs
    #"sfml-audio",
    "sfml-graphics"
    "sfml-main"
    "sfml-network"
    "sfml-system"
    "sfml-window")

foreach(sfml-lib ${used-libs})
    set_target_properties(${sfml-lib} PROPERTIES FOLDER "third_party/sfml")
    message("dir: ${PROJECT_BINARY_DIR}/third_party/sfml/${sfml-lib}")
    #add_custom_command(TARGET ${sfml-lib} POST_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/"
    #)
endforeach()
