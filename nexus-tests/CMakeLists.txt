set(target_name "nexus-tests")

set(src_files "src/input_handler.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name} "nexus-lib")
target_link_libraries(${target_name} "gtest_main")

target_include_directories(${target_name} PRIVATE "../nexus-lib/include")
target_include_directories(${target_name} PRIVATE "../../")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")

gtest_discover_tests(${target_name})

cotire(${target_name})