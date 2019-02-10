set(target_name "nexus-lib")

set(src_precompiled
    "src/precompiled.h")

set(src_sample
    "src/sample.cpp"
    "src/sample.h")


set(src_files
    ${src_precompiled}
    ${src_sample})

add_library(${target_name} STATIC ${src_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\sample" FILES ${src_sample})

target_link_libraries(${target_name} PRIVATE "compiler-warnings")
target_link_libraries(${target_name} PRIVATE "sfml-main")

target_compile_features(${target_name} INTERFACE cxx_std_17)

set_target_properties(${target_name} PROPERTIES FOLDER "nexus")
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${target_name} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${target_name})