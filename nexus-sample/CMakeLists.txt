set(target_name "nexus-sample")

set(src_files "src/main.cpp")

add_executable(${target_name} WIN32 ${src_files})

target_link_libraries(${target_name} "nexus-lib")

target_include_directories(${target_name} PRIVATE "../nexus-lib/include")

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")

cotire(${target_name})