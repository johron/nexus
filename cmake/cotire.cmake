message("-- External Project: cotire")
FetchContent_Declare(
    cotire
    URL https://github.com/sakra/cotire/archive/cotire-1.8.0.zip
)

FetchContent_Populate(cotire)
FetchContent_GetProperties(cotire)

include("${cotire_SOURCE_DIR}/cmake/cotire.cmake")
set(COTIRE_TARGETS_FOLDER "third_party//cotire")