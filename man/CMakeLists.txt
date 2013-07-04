set (PACKAGE_VERSION G3JAmin_VERSION)

configure_file ("${CMAKE_CURRENT_SOURCE_DIR}/g3jamin.1.in"
                "${CMAKE_BINARY_DIR}/docs/g3jamin.1")

install (FILES "${CMAKE_BINARY_DIR}/docs/g3jamin.1" DESTINATION share/man/man1)
