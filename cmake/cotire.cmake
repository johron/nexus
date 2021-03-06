message("-- External Project: cotire")
FetchContent_Declare(
    cotire
    GIT_REPOSITORY https://github.com/sakra/cotire.git
    GIT_TAG cotire-1.8.0
)

FetchContent_Populate(cotire)
FetchContent_GetProperties(cotire)

if (DEFINED cotire_SOURCE_DIR)
    include("${cotire_SOURCE_DIR}/CMake/cotire.cmake")
    set(COTIRE_TARGETS_FOLDER "third_party//cotire")
else()
    message(FATAL_ERROR "-- ERROR: Failed to configure cotire")
endif()
