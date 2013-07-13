cmake_minimum_required (VERSION 2.6)

# cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# gettext module
set (GettextTranslate_ALL ON)
include (GettextTranslate)

project (G3JAMin)

# version
set (VERSION 0.98.9)

subdirs (po src man data) #controller)
