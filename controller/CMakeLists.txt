include_directories (
    "${CMAKE_SOURCE_DIR}/src"
    ${CMAKE_BINARY_DIR})

add_library (jamincont_1912 SHARED
    jamincont_1912.c)


# install
install (TARGETS jamincont_1912 DESTINATION lib/ladspa)
