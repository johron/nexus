message("-- External Project: cotire")
include(FetchContent)
FetchContent_Declare(
    cotire
    GIT_REPOSITORY https://github.com/sakra/cotire.git
    GIT_TAG cotire-1.8.0
)

FetchContent_Populate(cotire)
FetchContent_GetProperties(cotire)

include(${cotire_SOURCE_DIR}/cmake/cotire.cmake)
set(COTIRE_TARGETS_FOLDER "third_party//cotire")