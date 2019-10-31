message("-- External Project: cotire")
FetchContent_Declare(
    cotire
    GIT_REPOSITORY https://github.com/sakra/cotire.git
    GIT_TAG cotire-1.8.0
)

FetchContent_Populate(cotire)
FetchContent_GetProperties(cotire)

function()
    
endfunction()


if (DEFINED cotire_SOURCE_DIR)
    message("dir: ${cotire_SOURCE_DIR}")
    file(GLOB_RECURSE found_files "*.*")
    message("files: ${found_files}")
    include("${cotire_SOURCE_DIR}/cmake/cotire.cmake")
    set(COTIRE_TARGETS_FOLDER "third_party//cotire")
else()
    message(FATAL_ERROR "-- ERROR: Failed to configure cotire")
endif()
