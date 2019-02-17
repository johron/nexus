add_library(code-coverage INTERFACE)

if (ENABLE_COVERAGE)
    if (MSVC)
        message(WARNING "Code coverage not supported for MSVC")
    else()
        target_compile_options(code-coverage INTERFACE --coverage -O0 -g)
        target_link_libraries(code-coverage INTERFACE --coverage)
    endif()
endif()