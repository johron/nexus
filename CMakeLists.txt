cmake_minimum_required(VERSION 3.11)
project("nexus" C CXX)

include("cmake/compiler_warnings.cmake")
include("cmake/compiler_features.cmake")
include("cmake/fetch_content.cmake")
include("cmake/code_coverage.cmake")
include("cmake/googletest.cmake")
include("cmake/cotire.cmake")
include("cmake/sfml.cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "predefined")
set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("nexus-lib")
add_subdirectory("nexus-tests")
add_subdirectory("nexus-sample")
add_subdirectory("nexus-game")

