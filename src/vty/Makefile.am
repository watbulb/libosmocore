# This is _NOT_ the library release version, it's an API version.
# Please read chapter "Library interface versions" of the libtool documentation
# before making any modifications: https://www.gnu.org/software/libtool/manual/html_node/Versioning.html
LIBVERSION=10:0:1

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include
AM_CFLAGS = -Wall $(TALLOC_CFLAGS)

if ENABLE_VTY
lib_LTLIBRARIES = libosmovty.la

libosmovty_la_SOURCES = buffer.c command.c vty.c vector.c utils.c \
			telnet_interface.c logging_vty.c stats_vty.c \
			fsm_vty.c talloc_ctx_vty.c \
			cpu_sched_vty.c tdef_vty.c
libosmovty_la_LDFLAGS = -version-info $(LIBVERSION) -no-undefined
libosmovty_la_LIBADD = $(top_builddir)/src/libosmocore.la $(TALLOC_LIBS)
endif
