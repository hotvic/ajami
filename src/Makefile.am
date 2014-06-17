noinst_LTLIBRARIES = libg3jamin.la

libg3jamin_la_CFLAGS =                          \
                      $(GTK_CFLAGS)             \
                      -I$(top_builddir)/src
libg3jamin_la_LIBADD = $(GTK_LIBS)
libg3jamin_la_SOURCES =                        \
                        g3jaminapp.c           \
                        g3jaminapp.h           \
                        g3jaminappwindow.c     \
                        g3jaminappwindow.h     \
                        g3jaminscenes.c        \
                        g3jaminscenes.h        \
                        gtkmeter.c             \
                        gtkmeter.h
                        

bin_PROGRAMS = g3jamin

g3jamin_CFLAGS = $(GTK_CFLAGS)
g3jamin_LDADD = libg3jamin.la $(GTK_LIBS)
g3jamin_SOURCES = g3jamin.c g3jamin-resources.c


BUILT_SOURCES = g3jamin-resources.c

g3jamin-resources.c: $(top_builddir)/data/g3jamin.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir="$(top_srcdir)/data" --generate-dependencies "$(top_builddir)/data/g3jamin.gresource.xml")
	$(GLIB_COMPILE_RESOURCES) --target="$@" --sourcedir="$(top_srcdir)/data" --generate-source "$(top_builddir)/data/g3jamin.gresource.xml"
