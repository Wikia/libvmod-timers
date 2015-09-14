AM_CPPFLAGS = @VMOD_INCLUDES@

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_timers.la

libvmod_timers_la_LDFLAGS = -module -export-dynamic -avoid-version

libvmod_timers_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_timers.c

vcc_if.c vcc_if.h: @VMODTOOL@ $(top_srcdir)/$(DIR_PREFIX)src/vmod_timers.vcc
	@VMODTOOL@ $(top_srcdir)/$(DIR_PREFIX)src/vmod_timers.vcc

VMOD_TESTS = tests/*.vtc
.PHONY: $(VMOD_TESTS)

tests/*.vtc:
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_timers.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
