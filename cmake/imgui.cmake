set(external_project "imgui")
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

set(IMGUI_INCLUDE_DIR ${PROJECT_BINARY_DIR}/third_party/${external_project}/src)