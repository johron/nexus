cmake_minimum_required(VERSION 3.11)
project("nexus" C CXX)

include("cmake/default_settings.cmake")
include("cmake/common_precompiled.cmake")
include("cmake/compiler_warnings.cmake")
include("cmake/compiler_features.cmake")
include("cmake/sanitizers.cmake")
include("cmake/conan.cmake")

option(IMGUI_SFML_BUILD_EXAMPLES "Build ImGui_SFML examples" ON)

add_conan_package("gtest/1.8.1@bincrafters/stable")
add_conan_package("rapidjson/1.1.0@bincrafters/stable")
add_conan_package("imgui-sfml/2.1@bincrafters/stable")

run_conan()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "predefined")
set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory("nexus-core")
add_subdirectory("nexus-core-tests")
add_subdirectory("nexus-gfx")
add_subdirectory("samples")
