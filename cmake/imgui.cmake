set(external_project "imgui")
message("-- External Project: ${external_project}")
set(EXTERNAL_PROJECT_FILE "cmake/imgui.cmake.in")

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

message("-- External Project: imgui-sfml")
set(BINDINGS_PROJECT_FILE "cmake/imgui-sfml.cmake.in")
set(BINDINGS_PROJECT_DIR ${PROJECT_BINARY_DIR}/third_party/imgui-sfml/download)
configure_file(${BINDINGS_PROJECT_FILE} ${BINDINGS_PROJECT_DIR}/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${BINDINGS_PROJECT_DIR}
        OUTPUT_FILE ${BINDINGS_PROJECT_DIR}/download-log.txt)
if(result)
    message(FATAL_ERROR "$imgui-sfml download failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${BINDINGS_PROJECT_DIR}
    OUTPUT_FILE ${BINDINGS_PROJECT_DIR}/build-log.txt)
if(result)
    message(FATAL_ERROR "Build step for ${external_project} failed: ${result}")
endif()

configure_file(
    ${PROJECT_BINARY_DIR}/third_party/imgui-sfml/src/imgui-SFML.h
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imgui-SFML.h
    COPYONLY)

configure_file(
    ${PROJECT_BINARY_DIR}/third_party/imgui-sfml/src/imgui-SFML.cpp
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imgui-SFML.cpp
    COPYONLY)

configure_file(
    ${PROJECT_BINARY_DIR}/third_party/imgui-sfml/src/imconfig-SFML.h
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imconfig-SFML.h
    COPYONLY)

file(
    APPEND 
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imconfig.h
    "#include \"imconfig-SFML.h\" // this line was added from CMake")

set(IMGUI_COMPILATION_UNITS
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imgui.cpp
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imgui_draw.cpp
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imgui_widgets.cpp
    ${PROJECT_BINARY_DIR}/third_party/imgui/src/imgui-SFML.cpp)

set(IMGUI_INCLUDE_DIR ${PROJECT_BINARY_DIR}/third_party/${external_project}/src)