cmake_minimum_required (VERSION 2.6)

# project settings
project (G3JAMin)
set (VERSION 0.98.9)

# cmake module path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


set (DIRECTORIES src man data)


# Native Language Support (NLS); gettext
option (ENABLE_NLS
    "Enable Native Language Support (gettext)" OFF)

find_library (GETTEXT_LIB gettext)

if (ENABLE_NLS AND DEFINED GETTEXT_LIB-NOTFOUND)
    message (FATAL_ERROR "Explicitly enabled NLS but gettext is NOTFOUND")
elseif (NOT ENABLE_NLS} AND NOT DEFINED GETTEXT_LIB-NOTFOUND)
    set (ENABLE_NLS ON)
endif (ENABLE_NLS AND DEFINED GETTEXT_LIB-NOTFOUND)

if (ENABLE_NLS)
    set (GettextTranslate_ALL ON)
    include (GettextTranslate)
    set (DIRECTORIES ${DIRECTORIES} po)
endif (ENABLE_NLS)


subdirs (${DIRECTORIES})
