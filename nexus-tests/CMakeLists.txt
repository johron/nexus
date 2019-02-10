set(target_name "nexus-tests")

set(src_files "src/empty.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name} "nexus-lib")
target_link_libraries(${target_name} "gtest_main")


set_target_properties(${target_name} PROPERTIES FOLDER "nexus")