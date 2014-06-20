noinst_LTLIBRARIES = libajami.la

libajami_la_CFLAGS =                           \
                     $(GTK_CFLAGS)             \
                     -I$(top_builddir)/src
libajami_la_LIBADD = $(GTK_LIBS)
libajami_la_SOURCES =                        \
                      ajami-app.c            \
                      ajami-app.h            \
                      ajami-appwindow.c      \
                      ajami-appwindow.h      \
                      ajami-scenes.c         \
                      ajami-scenes.h         \
                      gtkmeter.c             \
                      gtkmeter.h
                        

bin_PROGRAMS = ajami

ajami_CFLAGS = $(GTK_CFLAGS)
ajami_LDADD = libajami.la $(GTK_LIBS)
ajami_SOURCES = ajami.c ajami-resources.c


BUILT_SOURCES = ajami-resources.c

ajami-resources.c: $(top_builddir)/data/ajami.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir="$(top_srcdir)/data" --generate-dependencies "$(top_builddir)/data/ajami.gresource.xml")
	$(GLIB_COMPILE_RESOURCES) --target="$@" --sourcedir="$(top_srcdir)/data" --generate-source "$(top_builddir)/data/ajami.gresource.xml"
