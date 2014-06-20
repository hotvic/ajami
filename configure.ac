#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([AJAMI], [0.1b], [https://github.com/hotvic/ajami/issues])
AC_CONFIG_SRCDIR([src/ajami.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC

dnl ================================================================
dnl Automake
dnl ================================================================
AM_INIT_AUTOMAKE([-Wall foreign subdir-objects])

dnl ================================================================
dnl Libtool
dnl ================================================================
LT_INIT

PKG_CHECK_MODULES([GTK], [gtk+-3.0 >= 3.10])

dnl ================================================================
dnl Misc
dnl ================================================================
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, glib-compile-resources)


AC_CONFIG_FILES([
  data/ajami.gresource.xml
  src/Makefile
  Makefile
])
AC_OUTPUT
